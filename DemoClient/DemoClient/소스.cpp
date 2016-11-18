#pragma comment(lib,"ws2_32")
#pragma comment(lib,"winmm")
#include<iostream>
#include "CMyFunc.h"
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
	

	int StartTick;
	while (1)
	{
		StartTick = GetTickCount();

		while (GetTickCount() - StartTick >= 1000);      //1초마다 한번씩 들어가게끔
		{
			p1.m_vPos.x += 1;
			p1.m_vPos.y += 1;
			p1.m_vDirection = p1.m_vDirection + CVector2(1, 1);
			p1.speed++;
			retval = sendAndMsgType(clientSocket, (char*)&p1, sizeof(p1), 0, e_MSG_TYPE::MSG_PLAYERINFO);
			std::cout << retval << "전송" << std::endl;
		}
		// 딜레이를 주는 부분
	}
		//while (1)
		//{
		//	//무한 루프 
		//	currTime = timeGetTime();
		//	frameDelta = (currTime - lastTime) * 0.001f;
		//	FPS = 2;                     //15(FPS)라는 숫자가 fps를 결정한다.숫자가 작을수록 더 많은 프레임을 그린다..
		//										//컴퓨터 성능에 따라 테스트하여가장 느린 fps를 검출한 후 결정한다.
		//	if (frameDelta >= 1 / FPS)
		//	{
		//		//렌더링 하는 부분.
		//		p1.m_vPos.x+=1;
		//		p1.m_vPos.y+=1;
		//		p1.m_vDirection = p1.m_vDirection+CVector2(1, 1);
		//		p1.speed++;
		//		retval =  sendAndMsgType(clientSocket, (char*)&p1, sizeof(p1), 0, e_MSG_TYPE::MSG_PLAYERINFO);
		//		std::cout << retval << "전송" << std::endl;
		//		lastTime = currTime;
		//	}
		//	else {
		//		Sleep(frameDelta - 1 / FPS); //넣어줘도 되고 그냥 주석 처리해도 상관 없음니다.
		//	}
		//}

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
