#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}



// �ʱ�ȭ
void CMainGame::Initialize()
{
	int retval;
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa))
	{
		CMyFunc::err_quit("wsaStartup");
	}
	m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	CMyFunc::IsSocketError(retval, "socket()");
	std::cout << "socket()" << std::endl;
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	m_server_Addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	m_server_Addr.sin_family = AF_INET;
	m_server_Addr.sin_port = htons(PORT);

	retval = connect(m_clientSocket, (SOCKADDR*)&m_server_Addr, sizeof(m_server_Addr));
	CMyFunc::IsSocketError(retval, "connect");
	std::cout << "connect()" << std::endl;

	////////////////////////////ready?//////////////////////////////////////////////
	char tempBuff[10];
	CMessageForReady msg_ready;
	retval = CMyFunc::recvn(m_clientSocket, tempBuff, sizeof(tempBuff), 0);
	CMyFunc::IsSocketError(retval, "recvn");

	if (strcmp(tempBuff, "p1"))
	{
		m_playerType = 1;
	}
	else if (strcmp(tempBuff, "p2"))
	{
		m_playerType = 2;
	}
	std::cout << "�����p" << m_playerType << std::endl;
	//_getch();
	msg_ready.bReady = true;
	msg_ready.playerNum = m_playerType;
	retval = send(m_clientSocket, (char*)&msg_ready, sizeof(msg_ready), 0);
	std::cout << "�غ�Ϸ�޽����� ������ ���ۿϷ�" << std::endl;
	CMyFunc::IsSocketError(retval, "msg_ready");
	retval = send(m_clientSocket, (char*)&msg_ready, sizeof(msg_ready), 0);
	std::cout << "ready" << std::endl;

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////ball�� ����////////////////////////////////////////////
	if (m_playerType == 1) {
		std::cout << "����� ���� ������ �Է��ϼ���(1~3):";// std::cin >> m_ballNum;
	}
	retval = send(m_clientSocket, (char*)&m_ballNum, sizeof(m_ballNum), 0);
	CMyFunc::IsSocketError(retval, "send ballnum");
	//////////////////////////////////////////////////////////////////////////
	bool gameStart = false;
	
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);
	m_doubleBuffering.Initialize(m_hdc, clientrect);
	m_ball.Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE, PLAYER_SPEED);
	m_ball.SetDirection(CVector2(1, 1));
	m_p1.Initialize(CVector2(WINDOW_WIDTH - PLAYER_SIZE, WINDOW_HEIGHT / 2),
		PLAYER_SIZE, PLAYER_SPEED, m_playerType);
	m_p2.Initialize(CVector2(PLAYER_SIZE, WINDOW_HEIGHT / 2),
		PLAYER_SIZE, PLAYER_SPEED, m_playerType);

	//retval = recv(m_clientSocket, (char*)&gameStart, sizeof(gameStart), 0);
	//if (gameStart)
		m_threadForSendRecv = new std::thread(SendAndRecvThread, m_playerType, std::ref(m_p1),
			std::ref(m_p2), std::ref(m_ball), m_clientSocket);

}
// process
void CMainGame::Progress()
{
	//m_ball.move();
}

// �׸���
void CMainGame::Render()
{
	/*m_doubleBuffering.WriteToBackBuffer(&m_player1);
	m_doubleBuffering.WriteToBackBuffer(&m_player2);
	m_doubleBuffering.Present(m_hdc);*/

	m_doubleBuffering.WriteToBackBuffer(&m_p1);
	m_doubleBuffering.WriteToBackBuffer(&m_p2);
	m_doubleBuffering.WriteToBackBuffer(&m_ball);
	m_doubleBuffering.Present(m_hdc);

}
/*
[2016/09/02 19��23��
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:���콺 �Է�ó���Լ� ����.
*/
void CMainGame::MouseInputProcessing(const MSG& msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		if (m_playerType == 1)
			m_p1.MoveToMousePos(CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam)));
		else if (m_playerType == 2)
			m_p2.MoveToMousePos(CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam)));
		break;
	default:
		break;
	}
}

/*
[2016/09/04 01:54
�ۼ��� : ����(qpwoei25@naver.com)]
���� : Ű���� �Է�ó���Լ� ����.
*/
/*
[2016/09/04 18��35��
�ۼ��� : �ڿ���(dygks910910@daum.net)]
���泻��:VK_UP�� DOWN���� player1��Ʈ��.
				F2,F3Ű�� �÷��̾�2 ��Ʈ��
*/
void CMainGame::KeyboardInputProcessing(const MSG& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		if (msg.wParam == VK_UP)
		{
		}
		if (msg.wParam == VK_DOWN)
		{

		}
		if (msg.wParam == VK_F3)
		{
		}
		if (msg.wParam == VK_F2)
		{
		}
		break;
	case WM_KEYUP:
		break;
	default:
		break;
	}
}
/*
[2016/09/04 01:56
�ۼ��� : ����(qpwoei25@naver.com)]
���� : Ÿ�̸� ó���Լ� ����.
*/
void CMainGame::GameTimer(const MSG & msg)
{
	switch (msg.message)
	{
	case WM_TIMER:
		//to do this;


		break;
	default:
		break;
	}
}

// ����
void CMainGame::Release()
{
	WSACleanup();
	closesocket(m_clientSocket);
	delete m_threadForSendRecv;
	ReleaseDC(g_hWnd, m_hdc);


}

void SendAndRecvThread(const int & player_type, CPlayer & p1, CPlayer & p2, CBall & ball, const SOCKET& sock)
{
	static std::mutex ballMutex;
	static std::mutex playerMutex;
	int retval;
	CMsg_PlayerAndBall msg_playerAndBall;
	CTimer timer;
	CPlayerMsg tempLocalPlayerMsg;
	CMsg_PlayerAndBall msgData;
	ZeroMemory(&msgData, sizeof(msgData));
	timer.startTimer();
	while (1)
	{
		if (timer.getElapsedTime() >= 1000 / FPS)
		{
			//////////////////////////////////////////////////////////////////////////
			//local �÷��̾��� ��ġ���������� ������.
			if (player_type == 1) {
				playerMutex.lock();
				tempLocalPlayerMsg.m_vPos = p1.GetPosition();
				tempLocalPlayerMsg.m_vDirection = p1.GetDirection();
				tempLocalPlayerMsg.speed = p1.GetBallSpeed();
				playerMutex.unlock();
			}
			else if (player_type == 2)
			{
				playerMutex.lock();
				tempLocalPlayerMsg.m_vPos = p2.GetPosition();
				tempLocalPlayerMsg.m_vDirection = p2.GetDirection();
				tempLocalPlayerMsg.speed = p2.GetBallSpeed();
				playerMutex.unlock();
			}
			retval = send(sock, (char*)&tempLocalPlayerMsg, sizeof(tempLocalPlayerMsg), 0);//CplayerMsg�� �����ؾ���.
			if (CMyFunc::IsSocketError(retval, "sendTEmpLocalPlayerMsg"))break;
			//////////////////////////////////////////////////////////////////////////
			retval = CMyFunc::recvn(sock, (char*)&msgData, sizeof(msgData), 0);
			if (CMyFunc::IsSocketError(retval, "recvn msgdata")) {
				std::cout << "������ �����Ҽ� �����ϴ�" << std::endl;
				break;
			}
			if (player_type == 1)
			{
				playerMutex.lock();
				/*
				2016 / 12 / 3 / 4:35
				�ۼ���:�ڿ���(dygks910910@daum.net)
				����:�����ǰ��� m_vDirection ������ ���� �����߻�//////////////////////////////////////////////////////////////////////////
				*/
				p2.SetPosition(msgData.p2.m_vDirection); 
				p2.SetDirection(msgData.p2.m_vDirection);
				p2.SetBallSpeed(msgData.p2.speed);
				std::cout << msgData.p2.m_vPos << std::endl;
				playerMutex.unlock();
			}
			else if (player_type == 2)
			{
				playerMutex.lock();
				p1.SetPosition(msgData.p1.m_vPos);
				p1.SetDirection(msgData.p1.m_vDirection);
				p1.SetBallSpeed(msgData.p1.speed);
				std::cout << msgData.p1.m_vPos << std::endl;
				playerMutex.unlock();
			}
			ballMutex.lock();
			ball.SetPosition(msgData.ball.m_vPos);
			ball.SetDirection(msgData.ball.m_vDirection);
			ball.SetBallSpeed(msgData.ball.speed);
			ballMutex.unlock();

			timer.startTimer();
		}
	}
}
