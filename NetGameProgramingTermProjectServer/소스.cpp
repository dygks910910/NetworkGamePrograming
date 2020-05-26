#include "myHeader.h"
#include "RecvnAndMessageType.h"
#include "Message.h"
#include "Timer.h"
#include"SendAndMessageType.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#include "Ball.h"
#include<math.h>
#include "Timer.h"
#include "RandomEngine.h"
#define PORT 9000
void  InitServerSockAddrIPv4(SOCKADDR_IN& serverAddr);
void P1Thread(const SOCKET& clientSocket, CPlayerMsg& player);
void P2Thread(const SOCKET& clientSocket, CPlayerMsg& player);
void CheckCollision();

CRandomEngine randomEngine;
//zzzzz
CPlayerMsg g_P1;
CPlayerMsg g_P2;
CBall g_Ball[MAX_BALLNUM];
std::mutex p1Mutex;
std::mutex p2Mutex;
std::mutex scoreMutex;
std::mutex ballMutex;
int g_ballnum;
std::mutex p1readyMutex;
std::mutex p2readyMutex;
std::condition_variable p1readyCondvar;
std::condition_variable p2readyCondvar;
CTimer	countTimer;

bool bP1ReadyFlag = false;
bool bP2ReadyFlag = false;
bool bp1Accepted = false;
bool bp2Accepted = false;

int g_p1Score=0;
int g_p2Score=0;
void main()
{
	CTimer	timer;
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
	////-------�۽Ź��� ũ�� ����.---------------------------------------------------------------------
	//int optval,optlen;
	//optlen = sizeof(optval);
	//retval = getsockopt(listenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&optval, &optlen);
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "�۽Ź���ũ��:" << optval << std::endl;
	//optval *= 10;
	//retval = setsockopt(listenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&optval, sizeof(optval));
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "�۽Ź���ũ��:" << optval << std::endl;
	////���Ź��� ũ�⼳��.
	//optlen = sizeof(optval);
	//retval = getsockopt(listenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&optval, &optlen);
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "���Ź���ũ��:" << optval << std::endl;
	//optval *= 10;
	//retval = setsockopt(listenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&optval, sizeof(optval));
	//CMyFunc::IsSocketError(retval, "getsockopt");
	//std::cout << "���Ź���ũ��:" << optval << std::endl;


	///////////////////�غ�Ϸ� ���¸� �˱����Ѻ���///////////////////////////////////////////////////////
	CMessageForReady msg_p1Ready;
	CMessageForReady msg_p2Ready;
	//////////////////////////////////////////////////////////////////////////
	
	retval = listen(listenSocket, SOMAXCONN);
	CMyFunc::IsSocketError(retval, "listen()");
	SOCKET p1Socket, p2Socket;
	SOCKADDR_IN p1Addr, p2Addr;
	int p1AddrSize = sizeof(p1Addr);
	int p2AddrSize = sizeof(p2Addr);
	char tempP1[10] = "p2";
	char tempP2[10] = "p1";
	
	//-----------------------------------------p1����
	int recvCount = 0;
	while (1)
	{
		if (bp1Accepted==false)
		{
			p1Socket = accept(listenSocket, (SOCKADDR*)&p1Addr, &p1AddrSize);
			CMyFunc::errCheckAndErrQuit(p1Socket, "p1socket accept()");
			retval = send(p1Socket, tempP1, sizeof(tempP1), 0);
			CMyFunc::IsSocketError(retval, "send tempP1");
			std::cout << "p1����" << std::endl;
			bp1Accepted = true;
		}
		if (bp2Accepted == false)
		{
			p2Socket = accept(listenSocket, (SOCKADDR*)&p2Addr, &p2AddrSize);
			CMyFunc::errCheckAndErrQuit(p2Socket, "p2socket accept()");
			retval = send(p2Socket, tempP2, sizeof(tempP2), 0);
			CMyFunc::IsSocketError(retval, "send tempP2");
			bp2Accepted = true;
			std::cout << "p2����" << std::endl;
		}
		////////////////////////////��������????//////////////////////////////////////////////
		retval = CMyFunc::recvn(p1Socket, (char*)&msg_p1Ready, sizeof(msg_p1Ready), 0);
		CMyFunc::IsSocketError(retval, "msg_p1ready");
		std::cout << "p1�غ�Ϸ�" << std::endl;
		retval = CMyFunc::recvn(p2Socket, (char*)&msg_p2Ready, sizeof(msg_p2Ready), 0);
		CMyFunc::IsSocketError(retval, "msg_p2ready");
		std::cout << "p2�غ�Ϸ�" << std::endl;
		//////////////////////////////////////////////////////////////////////////

		/////////////////////////���ǰ����� �Է�./////////////////////////////////////////////////
		while (1)
		{
			std::cout << "����� ���� ����(1~ " << MAX_BALLNUM << "):";
			std::cin >> g_ballnum;
			if (g_ballnum >= 1 && g_ballnum <= MAX_BALLNUM)
			{
				break;
			}
			std::cin.clear();
		}
		retval = send(p1Socket, (char*)&g_ballnum, sizeof(g_ballnum), 0);
		CMyFunc::IsSocketError(retval, "recvn ballnum");
		retval = send(p2Socket, (char*)&g_ballnum, sizeof(g_ballnum), 0);
		CMyFunc::IsSocketError(retval, "recvn ballnum");
		
		//////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < g_ballnum; ++i) {
			g_Ball[i].Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
				BALL_SIZE, BALL_SPEED);
			g_Ball[i].SetDirection(CVector2(randomEngine.GetRandomNumFloat(-1,1),
				randomEngine.GetRandomNumFloat(-1,1)));
		}
		std::cout << "������ ��������" << std::endl;
		countTimer.startTimer();
		std::thread p1Thread(P1Thread, p1Socket, std::ref(g_P1));
		std::thread p2Thread(P2Thread, p2Socket, std::ref(g_P2));
		timer.startTimer();
		while (1)
		{
			if (timer.getElapsedTime() >= 1000 / FPS)//������ �ȿ� ������ ������ �۾�.
			{
				ballMutex.lock();
				for(int i = 0 ; i < g_ballnum;++i)
				g_Ball[i].Progress();
				CheckCollision();
				ballMutex.unlock();
				timer.startTimer();
				if (bp1Accepted ==false ||  bp2Accepted == false)
					break;
			}
			else
			{
				CheckCollision();
				/*Sleep(1000 / FPS - timer.getElapsedTime());*/
			}
		}
		p1Thread.join();
		p2Thread.join();
		closesocket(p1Socket);
		closesocket(p2Socket);
		ZeroMemory(&msg_p1Ready, sizeof(msg_p1Ready));
		ZeroMemory(&msg_p2Ready, sizeof(msg_p2Ready));

		bp1Accepted = false;
		bp2Accepted = false;
	}
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

void P1Thread(const SOCKET& clientSocket, CPlayerMsg& player)
{
	/*
	2016 / 11 / 20 / 8:39
	�ۼ���:�ڿ���(dygks910910@daum.net)
	����:FPS����
	*/

	CTimer timer;
	//int recvCount = 0;
	//------------------------------------------------------------------------------------------------------------------------------------------------�ǵ帮�� ����.
	CMsg_PlayerAndBall msg_temp;
	CPlayerMsg	 tempBallMsg;
	int retval = 0;
	while (bp1Accepted && bp2Accepted)
	{
		{
			//�ڵ����.
			std::lock_guard<std::mutex> lg(p1Mutex);
			retval = recv(clientSocket, (char*)&player, sizeof(player), 0);
			bP1ReadyFlag = true;
		}
		if (CMyFunc::IsSocketError(retval, "recvn player")) {
			bp1Accepted = false;
			break;
		}
		//p2������ �����.
		p1readyCondvar.notify_one();
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvP1");
			bp1Accepted = false;
			break;
		}
		{
			//p2�� �غ�ɋ����� ���.
			std::unique_lock<std::mutex> ul(p2readyMutex);
			p2readyCondvar.wait(ul, [] {return bP2ReadyFlag; });
		}
		//-----------------------------------------------------------------------�ǵ帮�� ����.
		std::cout << "1";

		//p1���� ball,p1,p2������ ���� ����.

		ballMutex.lock();
		for (int i = 0; i < g_ballnum; ++i) 
		{
			tempBallMsg.m_vPos = g_Ball[i].GetPosition();
			msg_temp.ball[i] = tempBallMsg;
		}
		ballMutex.unlock();

		p1Mutex.lock();
		msg_temp.p1= g_P1;
		msg_temp.p2= g_P2;
		p1Mutex.unlock();
		scoreMutex.lock();
		msg_temp.p1Score = g_p1Score;
		msg_temp.p2Score = g_p2Score;
		scoreMutex.unlock();
		msg_temp.countTime = countTimer.countDown(COUNTDOWN_TIME);
		retval = send(clientSocket, (char*)&msg_temp, sizeof(msg_temp), 0);
		if (CMyFunc::IsSocketError(retval, "send msg_temp"))
		{
			bp1Accepted = false;
			break;
		}

		/*
		2016 / 11 / 20 / 4:28
		�ۼ���:�ڿ���(dygks910910@daum.net)
		����:FPS�� Ȯ���ϰ� ������ ���.
		*/
		//recvCount++;
		//if (timer.getElapsedTime() >= 1000)
		//{
		//	//std::cout << recvCount << std::endl;
		//	recvCount = 0;
		//	timer.startTimer();
		//}
	}
	//recvCount = 0;
}
void P2Thread(const SOCKET& clientSocket, CPlayerMsg& player)
{
	/*
	2016 / 11 / 20 / 8:39
	�ۼ���:�ڿ���(dygks910910@daum.net)
	����:FPS����
	*/
	CMsg_PlayerAndBall msg_temp;
	int retval = 0;
	CPlayerMsg tempBallMsg;
	//int recvCount = 0;
	CTimer timer;
	//--------------------------------------------------------------------------------�ǵ帮�� ����.
	{
		//p1�����尡 �غ�ɶ����� ���.
		std::unique_lock<std::mutex> ul(p1readyMutex);
		p1readyCondvar.wait(ul, [] {return bP1ReadyFlag; });
		//std::cout << "p2WakeUP" << std::endl;
	}
	while (bp1Accepted && bp2Accepted)
	{
		{
			std::lock_guard<std::mutex> lg(p1Mutex);
			retval = recv(clientSocket, (char*)&player, sizeof(player), 0);
			bP2ReadyFlag = true;
		}
		p2readyCondvar.notify_one();
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvP2");
			bp2Accepted = false;
			break;
		}
		//--------------------------------------------------------------------------------�ǵ帮�� ����.

		std::cout << "2" ;
		//----------------�浹üũ�� ó��

		//ball������ p1,p2 ������ p2���� send();


		ballMutex.lock();
		for(int i = 0 ; i <g_ballnum ; ++i)
		{
			tempBallMsg.m_vPos = g_Ball[i].GetPosition();
			msg_temp.ball[i] = tempBallMsg;
		}
		ballMutex.unlock();

		p1Mutex.lock();
		msg_temp.p1 = g_P1;
		msg_temp.p2 = g_P2;
		p1Mutex.unlock();
		scoreMutex.lock();
		msg_temp.p1Score = g_p1Score;
		msg_temp.p2Score = g_p2Score;
		scoreMutex.unlock();
		msg_temp.countTime = countTimer.countDown(COUNTDOWN_TIME);
		retval = send(clientSocket, (char*)&msg_temp, sizeof(msg_temp), 0);
		if (CMyFunc::IsSocketError(retval, "send msg_temp")) {
			bp2Accepted = false;
			break;
		}
	/*
		2016 / 11 / 20 / 4:28
		�ۼ���:�ڿ���(dygks910910@daum.net)
		����:FPS�� Ȯ���ϰ� ������ ���.
		*/
		//recvCount++;
		//if (timer.getElapsedTime() >= 1000)
		//{
		////std::cout << recvCount << std::endl;
		//recvCount = 0;
		//timer.startTimer();
		//}
		//std::cout << "2";
	}
	/*recvCount = 0;*/
}


void CheckCollision()
{
	CVector2 tempvector;
	for (int i = 0; i < g_ballnum; ++i) 
	{
		if (distanceVector(g_P1.m_vPos, g_Ball[i].GetPosition()) <= PLAYER_SIZE * 2)
		{
			//std::cout << "p1�� �浹" << std::endl;
			tempvector = g_Ball[i].GetPosition() - g_P1.m_vPos;
			g_Ball[i].SetDirection(normalize(tempvector) + normalize(g_Ball[i].GetDirection()));
			
		}
		else if (distanceVector(g_P2.m_vPos, g_Ball[i].GetPosition()) <= PLAYER_SIZE * 2)
		{
			//std::cout << "p2�� �浹" << std::endl;
			tempvector = g_Ball[i].GetPosition() - g_P2.m_vPos;
			g_Ball[i].SetDirection(normalize(tempvector) + normalize(g_Ball[i].GetDirection()));
		}
		if (g_Ball[i].GetPosition().x >= WINDOW_WIDTH - PLAYER_SIZE &&
			g_Ball[i].GetPosition().y < WINDOW_HEIGHT / 2 + GOAL_SIZE &&
			g_Ball[i].GetPosition().y > WINDOW_HEIGHT / 2 - GOAL_SIZE)
		{
			scoreMutex.lock();
			g_p1Score+= 1;
			scoreMutex.unlock();
			g_Ball[i].Initialize();
			g_Ball[i].SetDirection(CVector2(randomEngine.GetRandomNumFloat(-1, 1),
				randomEngine.GetRandomNumFloat(-1, 1)));
		}
		if (g_Ball[i].GetPosition().x <= PLAYER_SIZE &&
			g_Ball[i].GetPosition().y < WINDOW_HEIGHT / 2 + GOAL_SIZE &&
			g_Ball[i].GetPosition().y > WINDOW_HEIGHT / 2 - GOAL_SIZE)
		{
			scoreMutex.lock();
			g_p2Score+= 1;
			scoreMutex.unlock();
			g_Ball[i].Initialize();
			g_Ball[i].SetDirection(CVector2(randomEngine.GetRandomNumFloat(-1, 1), 
				randomEngine.GetRandomNumFloat(-1, 1)));
		}
	}
}
