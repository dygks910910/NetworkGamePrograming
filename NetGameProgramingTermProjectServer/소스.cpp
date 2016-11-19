#include "stdafx.h"
#include "RecvnAndMessageType.h"
#include "Message.h"
#include "Timer.h"
#define PORT 9000
void  InitServerSockAddrIPv4(SOCKADDR_IN& serverAddr);
//zzzzz
CPlayer p1;
void main()
{
	CTimer timer;
	bool bP1Ready = false, bP2Ready = false;
	CRecvnAndMessageType recvMessageType;
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
	SOCKET p1socket,p2Socket;
	SOCKADDR_IN p1Addr,p2Addr;
	int p1AddrSize= sizeof(p1Addr);
	int p2AddrSize = sizeof(p2Addr);


	
	//--------------------------------------------------------------------------------------------------------------------------------
	int recvCount=0;
	while (1) 
	{
		p1socket = accept(listenSocket, (SOCKADDR*)&p1Addr, &p1AddrSize);
		CMyFunc::errCheckAndErrQuit(p1socket, "p1socket accept()");
		std::cout << "p1접속";
		bP1Ready = true;
		timer.startTimer();

		while (1)
		{

			retval = recvMessageType(p1socket, (char*)&p1, sizeof(p1), 0);
			if (retval == SOCKET_ERROR)
			{
				CMyFunc::err_display("recvP1");
				break;
			}
			recvCount++;

			/*std::cout << "플레이어 포지션" << p1.m_vPos << std::endl;
			std::cout << "방향" << p1.m_vDirection << std::endl;
			std::cout << "스피드" << p1.speed << std::endl;*/

			if (timer.getElapsedTime() >= 1000)
			{
				timer.startTimer();
				std::cout <<"FPS: " <<recvCount << std::endl;
				recvCount=0;
			}
		}
		recvCount = 0;
	}
	/*p2Socket = accept(p2Socket, (SOCKADDR*)&p2Addr, &p2AddrSize);
	CMyFunc::errCheckAndErrQuit(p2Socket, "p2Socket accept()");
	bP2Ready = true;
*/


	closesocket(p1socket);
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

