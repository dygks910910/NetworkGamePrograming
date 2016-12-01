#pragma comment(lib,"ws2_32")
#pragma comment(lib,"winmm")
#include<iostream>
#include "CMyFunc.h"
#include "Timer.h"
#include "RecvnAndMessageType.h"
#include "SendAndMessageType.h"
#include "Vector2.h""
#include<WinSock2.h>
#include<Windows.h>
#include "Message.h"
#include"enum.h"
#include "Ball.h"
#include<conio.h>
#define LOOP_BACK "127.0.0.1"
#define PORT 9000
SOCKADDR_IN InitSockAddrIPv4(const char* ipAddr, const int& port);
static DWORD frameDelta = 0;
static DWORD lastTime = timeGetTime();

CPlayer	 g_ball;
int PlayerType = 0;
CPlayer p1;
CPlayer	 p2;
MSG_GAMEINFO msgData;
void main()
{
	int ballNum = 1;
	ZeroMemory(&p1, sizeof(p1));
	ZeroMemory(&p2, sizeof(p2));
	CMessageForReady msg_ready;
	CTimer timer;
	CSendAndMessageType sendAndMsgType;
	CRecvnAndMessageType recvAndMsgType;
	CMessageBallInfo tempBallInfo;
	int retval;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		CMyFunc::err_quit("WSAStartup()");
	}
	SOCKET clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	CMyFunc::errCheckAndErrDisplay(clientSocket, "socket()");
	SOCKADDR_IN clientAddr;
	clientAddr.sin_addr.s_addr = inet_addr(LOOP_BACK);
	clientAddr.sin_port = htons(PORT);
	clientAddr.sin_family = AF_INET;

	char tempBuff[10];
	SOCKADDR_IN serverAddr = InitSockAddrIPv4(LOOP_BACK, PORT);

	retval = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	CMyFunc::IsSocketError(retval, "connect()");
	std::cout << "접속성공" << std::endl;
	retval = CMyFunc::recvn(clientSocket, tempBuff, sizeof(tempBuff), 0);
	CMyFunc::IsSocketError(retval, "recvn");

	if (strcmp(tempBuff, "p1"))
	{
		PlayerType = 1;
	}
	else if (strcmp(tempBuff, "p2"))
	{
		PlayerType = 2;
	}
	std::cout << "당신은p" << PlayerType << std::endl;
	std::cout << "준비가 완료되면 아무키나 누르세요" << std::endl;
	_getch();
	msg_ready.bReady = true;
	msg_ready.playerNum = PlayerType;
	retval = send(clientSocket, (char*)&msg_ready, sizeof(msg_ready), 0);
	std::cout << "준비완료메시지를 서버에 전송완료" << std::endl;
	CMyFunc::IsSocketError(retval, "msg_ready");
	
	///////////////////////볼의 갯수를 1p가 서버에 전송해줘야 한다.///////////////////////////////////////////////////
	if (PlayerType == 1) {
		std::cout << "사용할 볼의 갯수를 입력하세요(1~3):"; std::cin >> ballNum;
	}
	retval = send(clientSocket, (char*)&ballNum, sizeof(ballNum), 0);
	CMyFunc::IsSocketError(retval, "send ballnum");
	//////////////////////////////////////////////////////////////////////////
	timer.startTimer();

	while (1)
	{
		if (timer.getElapsedTime() >= 1000 / FPS)//프레임 안에 들어오면 수행할 작업.
		{
			//원래 마우스 좌표값을 받아와서 넣어주는 부분.
			if (PlayerType == 1)
			{
				p1.m_vPos.x += 1;
				p1.m_vPos.y += 1;
				p1.m_vDirection = p1.m_vDirection + CVector2(1, 1);
				p1.speed++;
			}
			else if (PlayerType == 2) {
				p2.m_vPos.x += 10;
				p2.m_vPos.y += 10;
				p2.m_vDirection = p2.m_vDirection + CVector2(10, 10);
				p2.speed += 10;
			}
			//--------------------------------------------------------------
			if (PlayerType == 1)
				retval = send(clientSocket, (char*)&p1, sizeof(p1), 0);
			else if (PlayerType == 2)
				retval = send(clientSocket, (char*)&p2, sizeof(p2), 0);

			CMyFunc::IsSocketError(retval, "send p1");

			//p1,p2,ball 의 정보를 다 받기.
			retval = CMyFunc::recvn(clientSocket, (char*)&msgData, sizeof(msgData), 0);
			CMyFunc::IsSocketError(retval, "recvn msgdata");

			g_ball = msgData.ball;
			if (PlayerType == 1)
			{
				p2 = msgData.p2;
				std::cout << "p2플레이어 위치정보" << p2.m_vPos << " 방향" << p2.m_vDirection << " 속도" << p2.speed << std::endl;
			}
			else if (PlayerType == 2)
			{
				p1 = msgData.p1;
				std::cout << "p1플레이어 위치정보" << p1.m_vPos << " 방향" << p1.m_vDirection << " 속도" << p1.speed << std::endl;
			}
			std::cout << "볼위치:" << msgData.ball.m_vPos << " 볼방향" << msgData.ball.m_vDirection << " 볼스피드" << msgData.ball.speed << std::endl;


			timer.startTimer();
		}
		else
		{
			// 딜레이를 주는 부분
		}
	}

	closesocket(clientSocket);
	WSACleanup();
}


SOCKADDR_IN InitSockAddrIPv4(const char* ipAddr, const int& port)
{
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_addr.s_addr = inet_addr(ipAddr);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	return serverAddr;
}
