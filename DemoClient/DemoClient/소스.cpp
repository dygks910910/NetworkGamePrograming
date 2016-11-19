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
#define LOCAL_LOOP "127.0.0.1"
#define PORT 9000
SOCKADDR_IN InitSockAddrIPv4(const char* ipAddr, const int& port);
static DWORD frameDelta = 0;
static DWORD lastTime = timeGetTime();
CPlayer p1;
void main()
{
	CTimer timer;
	CSendAndMessageType sendAndMsgType;
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


	SOCKADDR_IN serverAddr = InitSockAddrIPv4(LOCAL_LOOP,PORT);
	DWORD currTime;
	DWORD FPS;

	retval = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	CMyFunc::IsSocketError(retval, "connect()");
	std::cout << "접속성공" << std::endl;
	timer.startTimer();

	while(1)
	{
		if (timer.getElapsedTime() >= 1000/30 )
		{
			p1.m_vPos.x += 1;
			p1.m_vPos.y += 1;
			p1.m_vDirection = p1.m_vDirection + CVector2(1, 1);
			p1.speed++;
			retval = sendAndMsgType(clientSocket, (char*)&p1, sizeof(p1), 0, e_MSG_TYPE::MSG_PLAYERINFO);
			std::cout << retval << "전송" << std::endl;
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
