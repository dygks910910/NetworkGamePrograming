#include "stdafx.h"
#include "RecvnAndMessageType.h"
#include "Message.h"
#include "Timer.h"
#include"SendAndMessageType.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#define PORT 9000
void  InitServerSockAddrIPv4(SOCKADDR_IN& serverAddr);
void P1Thread(const SOCKET& clientSocket, CPlayer& player);
void P2Thread(const SOCKET& clientSocket, CPlayer& player);

//zzzzz
CPlayer p1;
CPlayer p2;
CRecvnAndMessageType g_RecvMessageType;
CSendAndMessageType g_SendMessageType;
std::mutex writeMutex;

std::mutex p1readyMutex;
std::mutex p2readyMutex;

std::condition_variable p1readyCondvar;
std::condition_variable p2readyCondvar;

bool bP1ReadyFlag = false;
bool bP2ReadyFlag = false;

void main()
{
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

	std::thread p1Thread(P1Thread, p1Socket,std::ref(p1));
	std::thread p2Thread(P2Thread, p2Socket,std::ref(p2));

	p1Thread.join();
	p2Thread.join();


	closesocket(p1Socket);
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
		//std::cout << "1" << std::endl;
		//std::cout << "P1플레이어 포지션" << player.m_vPos << std::endl;
		/*std::cout << "방향" << p1.m_vDirection << std::endl;
		std::cout << "스피드" << p1.speed << std::endl;*/

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
	int recvCount = 0;
	CTimer timer;
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

		//std::cout << "2" << std::endl;

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
		std::cout << "FPS: " << recvCount << std::endl;
		recvCount = 0;
		}
		bP1ReadyFlag = false;
	}
	recvCount = 0;
}