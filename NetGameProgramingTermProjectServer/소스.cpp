#include "stdafx.h"
#include "RecvnAndMessageType.h"
#include "Message.h"
#include "Timer.h"
#include"SendAndMessageType.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#include "Ball.h"
#include<math.h>
#include "Collision.h"
#include "Timer.h"
#define PORT 9000
void  InitServerSockAddrIPv4(SOCKADDR_IN& serverAddr);
void P1Thread(const SOCKET& clientSocket, CPlayer& player);
void P2Thread(const SOCKET& clientSocket, CPlayer& player);

//zzzzz
CPlayer g_P1;
CPlayer g_P2;
CBall g_Ball;
CRecvnAndMessageType g_RecvMessageType;
CSendAndMessageType g_SendMessageType;
std::mutex writeMutex;

std::mutex p1readyMutex;
std::mutex p2readyMutex;
std::mutex ballMutex;
std::condition_variable p1readyCondvar;
std::condition_variable p2readyCondvar;

bool bP1ReadyFlag = false;
bool bP2ReadyFlag = false;

Collision g_Colision;
void main()
{
	CTimer	timer;
	bool bP1Ready = false, bP2Ready = false;
	int retval;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		CMyFunc::err_quit("WSAStartup()");
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	CMyFunc::errCheckAndErrQuit(listenSocket, "socket()");
	SOCKADDR_IN serverAddr;
	InitServerSockAddrIPv4(serverAddr);
	retval = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	CMyFunc::IsSocketError(retval, "bind()");
	////-------송신버퍼 크기 변경.---------------------------------------------------------------------
	//int optval,optlen;
	//optlen = sizeof(optval);
	//retval = getsockopt(listenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&optval, &optlen);
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "송신버퍼크기:" << optval << std::endl;
	//optval *= 10;
	//retval = setsockopt(listenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&optval, sizeof(optval));
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "송신버퍼크기:" << optval << std::endl;
	////수신버퍼 크기설정.--------------------------------------------------------------------------------
	//optlen = sizeof(optval);
	//retval = getsockopt(listenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&optval, &optlen);
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "수신버퍼크기:" << optval << std::endl;
	//optval *= 10;
	//retval = setsockopt(listenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&optval, sizeof(optval));
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "수신버퍼크기:" << optval << std::endl;


	
	
	retval = listen(listenSocket, SOMAXCONN);
	CMyFunc::IsSocketError(retval, "listen()");
	SOCKET p1Socket, p2Socket;
	SOCKADDR_IN p1Addr, p2Addr;
	int p1AddrSize = sizeof(p1Addr);
	int p2AddrSize = sizeof(p2Addr);

	char tempP1[10] = "p1";
	char tempP2[10] = "p2";

	//-----------------------------------------p1접속
	int recvCount = 0;
	p1Socket = accept(listenSocket, (SOCKADDR*)&p1Addr, &p1AddrSize);
	CMyFunc::errCheckAndErrQuit(p1Socket, "p1socket accept()");
	std::cout << "p1접속";
	retval = send(p1Socket, tempP1, sizeof(tempP1), 0);
	CMyFunc::IsSocketError(retval, "send tempP1");
	bP1Ready = true;
	

	p2Socket = accept(listenSocket, (SOCKADDR*)&p2Addr, &p2AddrSize);
	CMyFunc::errCheckAndErrQuit(p2Socket, "p2socket accept()");
	std::cout << "p2접속";
	retval = send(p2Socket, tempP2, sizeof(tempP2), 0);
	CMyFunc::IsSocketError(retval, "send tempP2");
	bP2Ready = true;
	
	std::thread p1Thread(P1Thread, p1Socket,std::ref(g_P1));
	std::thread p2Thread(P2Thread, p2Socket,std::ref(g_P2));
	g_Ball.Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
		BALL_SIZE, PLAYER_SPEED);
	timer.startTimer();

	while (1)
	{
		if (timer.getElapsedTime() >= 1000 / FPS)//프레임 안에 들어오면 수행할 작업.
		{
			writeMutex.lock();
			g_Ball.Progress();
			writeMutex.unlock();
			//std::cout << g_Ball.GetPosition() << std::endl;
			timer.startTimer();
		}
		else
		{
			// 딜레이를 주는 부분
		}
	}


	p1Thread.join();
	p2Thread.join();


	closesocket(p1Socket);
	closesocket(p2Socket);
	closesocket(listenSocket);
	WSACleanup();
}

void  InitServerSockAddrIPv4(SOCKADDR_IN& serverAddr)
{
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

}

void P1Thread(const SOCKET& clientSocket,CPlayer& player)
{
	/*
	2016 / 11 / 20 / 8:39
	작성자:박요한(dygks910910@daum.net)
	설명:FPS변수
	*/
	//CTimer timer;
	//int recvCount = 0;
	//------------------------------------------------------------------------------------------------------------------------------------------------건드리지 말것.
	CMessageBallInfo tempBallMsg;
	int retval = 0;
	while (1)
	{
		{
			//자동잠금.
			std::lock_guard<std::mutex> lg(writeMutex);
			retval = g_RecvMessageType(clientSocket, (char*)&player, sizeof(player), 0);
			bP1ReadyFlag = true;
		}
		//p2스레드 깨우기.
		p1readyCondvar.notify_one();
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvP1");
			break;
		}


		{
			//p2가 준비될떄까지 대기.
			std::unique_lock<std::mutex> ul(p2readyMutex);
			p2readyCondvar.wait(ul, [] {return bP2ReadyFlag; });
			//std::cout << "p1WakeUp" << std::endl;
		}

		//----------------------------------------------------------------------------------------------------------------------------------------------------------건드리지 말것.
		//std::cout << "1";
		//----------------충돌체크및 처리
		/*if (g_Colision.ifCollision(player, g_Ball))
		{
			ballMutex.lock();
			g_Colision.ComputeCollision(player, g_Ball);
			ballMutex.unlock();
		}*/

		//p1에게 send(ball정보와 p2정보) ;
		retval = g_SendMessageType(clientSocket, (char*)&g_P2, sizeof(g_P2), 0, e_MSG_TYPE::MSG_PLAYERINFO);
		CMyFunc::IsSocketError(retval, "sendmsg P1");
		tempBallMsg.m_vPos = g_Ball.GetPosition();
		tempBallMsg.m_vDirection= g_Ball.GetDirection();
		tempBallMsg.speed = g_Ball.GetBallSpeed();
		
		retval = g_SendMessageType(clientSocket, (char*)&tempBallMsg, sizeof(tempBallMsg), 0, e_MSG_TYPE::MSG_PLAYERINFO);
		CMyFunc::IsSocketError(retval, "sendmsg ball");
		//if (g_Colision.ifCollision(player, g_Ball))
		//{
		////	ballMutex.lock();
		//	g_Colision.ComputeCollision(player, g_Ball);
		//	//ballMutex.unlock();
		//}
		/*
		2016 / 11 / 22 / 0:02
		작성자:박요한(dygks910910@daum.net)
		설명:순서제어가 되면 두개의 정보가 일치해야 한다.이 값들을 클라이언트에게 전송한 값들과 비교해서
		값이 같다면 똑같은 데이터가 전송되어 온것으로 친다.
		*/
		/*std::cout << "P1" << "	  의 정보:위치" << g_P1.m_vPos << "  방향" << g_P1.m_vDirection << std::endl;
		std::cout << "P2" << "	  의 정보:위치" << g_P2.m_vPos << "  방향" << g_P2.m_vDirection << std::endl;
		std::cout << "BALL" << "의 정보:위치" << g_Ball.GetPosition()<< "  방향" << g_Ball.GetDirection()<< std::endl;*/




		/*
		2016 / 11 / 20 / 4:28
		작성자:박요한(dygks910910@daum.net)
		설명:FPS를 확인하고 싶을때 사용.
		*/
	/*	recvCount++;
		if (timer.getElapsedTime() >= 1000)
		{
			timer.startTimer();
			std::cout << "FPS: " << recvCount << std::endl;
			recvCount = 0;
		}*/
		bP2ReadyFlag = false;
	}
	/*recvCount = 0;*/
}
void P2Thread(const SOCKET& clientSocket, CPlayer& player)
{
	/*
	2016 / 11 / 20 / 8:39
	작성자:박요한(dygks910910@daum.net)
	설명:FPS변수
	*/
	int retval = 0;
	CMessageBallInfo tempBallMsg;
	int recvCount = 0;
	CTimer timer;
	//--------------------------------------------------------------------------------건드리지 말것.
	{
		//p1스레드가 준비될때까지 대기.
		std::unique_lock<std::mutex> ul(p1readyMutex);
		p1readyCondvar.wait(ul, [] {return bP1ReadyFlag; });
		//std::cout << "p2WakeUP" << std::endl;
	}
	
	while (1)
	{
		{
			std::lock_guard<std::mutex> lg(writeMutex);
			retval = g_RecvMessageType(clientSocket, (char*)&player, sizeof(player), 0);
			bP2ReadyFlag = true;
		}
		p2readyCondvar.notify_one();

		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvP1");
			break;
		}
		//--------------------------------------------------------------------------------건드리지 말것.

		//std::cout << "2" ;
		//----------------충돌체크및 처리
	/*	if (g_Colision.ifCollision(player, g_Ball))
		{
			ballMutex.lock();
			g_Colision.ComputeCollision(player, g_Ball);
			ballMutex.unlock();
		}*/
		//ball정보와 p1정보를 p2에게 send();
		retval = g_SendMessageType(clientSocket, (char*)&g_P1, sizeof(g_P1), 0, e_MSG_TYPE::MSG_PLAYERINFO);
		CMyFunc::IsSocketError(retval, "sendmsg P1");

		tempBallMsg.m_vPos = g_Ball.GetPosition();
		tempBallMsg.m_vDirection = g_Ball.GetDirection();
		tempBallMsg.speed = g_Ball.GetBallSpeed();

		retval = g_SendMessageType(clientSocket, (char*)&tempBallMsg, sizeof(tempBallMsg), 0, e_MSG_TYPE::MSG_PLAYERINFO);
		CMyFunc::IsSocketError(retval, "sendmsg ball");


		//std::cout << "P2플레이어 포지션" << player.m_vPos << std::endl;
		/*std::cout << "방향" << p1.m_vDirection << std::endl;
		std::cout << "스피드" << p1.speed << std::endl;*/

		/*
		2016 / 11 / 20 / 4:28
		작성자:박요한(dygks910910@daum.net)
		설명:FPS를 확인하고 싶을때 사용.
		*/
		recvCount++;
		if (timer.getElapsedTime() >= 1000)
		{
		timer.startTimer();
		std::cout << recvCount << std::endl;
		recvCount = 0;
		}
		bP1ReadyFlag = false;
	}
	recvCount = 0;
}
