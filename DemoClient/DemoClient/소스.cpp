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
#define LOCAL_LOOP "127.0.0.1"
#define PORT 9000
SOCKADDR_IN InitSockAddrIPv4(const char* ipAddr, const int& port);
static DWORD frameDelta = 0;
static DWORD lastTime = timeGetTime();

CBall g_ball;
CPlayer p1;
void main()
{
	CPlayer	 p2;
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
	clientAddr.sin_addr.s_addr = inet_addr(LOCAL_LOOP);
	clientAddr.sin_port = htons(PORT);
	clientAddr.sin_family = AF_INET;

	char tempBuff[10];
	SOCKADDR_IN serverAddr = InitSockAddrIPv4(LOCAL_LOOP,PORT);
	
	retval = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	CMyFunc::IsSocketError(retval, "connect()");
	std::cout << "접속성공" << std::endl;
	retval = CMyFunc::recvn(clientSocket, tempBuff, sizeof(tempBuff), 0);
	CMyFunc::IsSocketError(retval, "recvn");
	std::cout << "당신은" << tempBuff << std::endl;
	timer.startTimer();

	while(1)
	{
		if (timer.getElapsedTime() >= 1000/FPS )//프레임 안에 들어오면 수행할 작업.
		{
			p1.m_vPos.x += 1;
			p1.m_vPos.y += 1;
			p1.m_vDirection = p1.m_vDirection + CVector2(1, 1);
			p1.speed++;
			retval = sendAndMsgType(clientSocket, (char*)&p1, sizeof(p1), 0, e_MSG_TYPE::MSG_PLAYERINFO);
			//std::cout << retval << "전송" << std::endl;
			//p2의 정보를 받기.
			retval = recvAndMsgType(clientSocket, (char*)&p2, sizeof(p2), 0);
			CMyFunc::IsSocketError(retval, "recv()P2");
			//ball의 정보를 받기.
			retval = recvAndMsgType(clientSocket, (char*)&tempBallInfo, sizeof(tempBallInfo), 0);
			CMyFunc::IsSocketError(retval, "recv() Ball");
			
			if (strcmp(tempBuff, "p1"))
			{
				std::cout << "p2"<< " 의 정보:위치" << p2.m_vPos << "	 방향" << p2.m_vDirection << std::endl;
			}
			else 
			{
				std::cout << "p1" << "	 의 정보:위치" << p1.m_vPos << " 방향" << p1.m_vDirection << std::endl;
			}
			g_ball.SetPosition(tempBallInfo.m_vPos);
			g_ball.SetBallSpeed(tempBallInfo.speed);
			g_ball.SetDirection(tempBallInfo.m_vDirection);
			std::cout << "볼 포지션" << g_ball.GetPosition() <<std::endl;

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
