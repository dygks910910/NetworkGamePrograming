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



// 초기화
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
	std::cout << "당신은p" << m_playerType << std::endl;
	//_getch();
	msg_ready.bReady = true;
	msg_ready.playerNum = m_playerType;
	retval = send(m_clientSocket, (char*)&msg_ready, sizeof(msg_ready), 0);
	std::cout << "준비완료메시지를 서버에 전송완료" << std::endl;
	CMyFunc::IsSocketError(retval, "msg_ready");
	retval = send(m_clientSocket, (char*)&msg_ready, sizeof(msg_ready), 0);
	std::cout << "ready" << std::endl;
	//////////////////////////////ball의 갯수////////////////////////////////////////////
	if (m_playerType == 1) {
		std::cout << "사용할 볼의 갯수를 입력하세요(1~3):";// std::cin >> m_ballNum;
	}
	retval = send(m_clientSocket, (char*)&m_ballNum, sizeof(m_ballNum), 0);
	CMyFunc::IsSocketError(retval, "send ballnum");
	//////////////////////////////////////////////////////////////////////////
	
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);
	m_doubleBuffering.Initialize(m_hdc, clientrect);
	m_ball.Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE, PLAYER_SPEED);
	m_ball.SetDirection(CVector2(1, 1));
	if (m_playerType == 1) {
		m_localPlayer.Initialize(CVector2(WINDOW_WIDTH - PLAYER_SIZE, WINDOW_HEIGHT / 2),
			PLAYER_SIZE, PLAYER_SPEED, m_playerType);
		m_otherPlayer.Initialize(CVector2(PLAYER_SIZE, WINDOW_HEIGHT / 2),
			PLAYER_SIZE, PLAYER_SPEED, 2);
	}
	else if (m_playerType == 2)
	{
		m_localPlayer.Initialize(CVector2(PLAYER_SIZE, WINDOW_HEIGHT / 2),
			PLAYER_SIZE, PLAYER_SPEED, m_playerType);
		m_otherPlayer.Initialize(CVector2(WINDOW_WIDTH - PLAYER_SIZE, WINDOW_HEIGHT / 2),
			PLAYER_SIZE, PLAYER_SPEED, 1);
	}

	//retval = recv(m_clientSocket, (char*)&gameStart, sizeof(gameStart), 0);
	//if (gameStart)
		m_threadForSendRecv = new std::thread(SendAndRecvThread, m_playerType, std::ref(m_localPlayer),
			std::ref(m_otherPlayer), std::ref(m_ball),m_clientSocket);

}
// process
void CMainGame::Progress()
{
	//m_ball.move();
}

// 그리기
void CMainGame::Render()
{
	/*m_doubleBuffering.WriteToBackBuffer(&m_player1);
	m_doubleBuffering.WriteToBackBuffer(&m_player2);
	m_doubleBuffering.Present(m_hdc);*/

	m_doubleBuffering.WriteToBackBuffer(&m_localPlayer);
	m_doubleBuffering.WriteToBackBuffer(&m_otherPlayer);
	m_doubleBuffering.WriteToBackBuffer(&m_ball);
	m_doubleBuffering.Present(m_hdc);

}
/*
[2016/09/02 19시23분
작성자 : 박요한(dygks910910@daum.net)]
설명:마우스 입력처리함수 본문.
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
		playerMutex.lock();
			m_localPlayer.MoveToMousePos(CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam)));
			playerMutex.unlock();
		break;
	default:
		break;
	}
}

/*
[2016/09/04 01:54
작성자 : 이주(qpwoei25@naver.com)]
설명 : 키보드 입력처리함수 본문.
*/
/*
[2016/09/04 18시35분
작성자 : 박요한(dygks910910@daum.net)]
변경내용:VK_UP과 DOWN으로 player1컨트롤.
				F2,F3키로 플레이어2 컨트롤
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


// 해제
void CMainGame::Release()
{
	WSACleanup();
	m_threadForSendRecv->join();
	delete m_threadForSendRecv;
	closesocket(m_clientSocket);
	ReleaseDC(g_hWnd, m_hdc);


}

void SendAndRecvThread(const int& player_type, CPlayer& localPlayer, CPlayer& otherPlayer, CBall& ball, const SOCKET& sock)
{
	
	int retval;
	CTimer timer;
	CPlayerMsg tempLocalPlayerMsg;
	CMsg_PlayerAndBall msgData;
	ZeroMemory(&msgData, sizeof(msgData));
	
	////////////////////////////ready?//////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////

	
	bool gameStart = false;


	timer.startTimer();
	while (1)
	{
		if (timer.getElapsedTime() >= 1000 / FPS)
		{
			//////////////////////////////////////////////////////////////////////////
			//local 플레이어의 위치방향정보를 보내기.
			//if (player_type == 1) {
				playerMutex.lock();
				tempLocalPlayerMsg.m_vPos = localPlayer.GetPosition();
				tempLocalPlayerMsg.m_vDirection = localPlayer.GetDirection();
				tempLocalPlayerMsg.speed = localPlayer.GetBallSpeed();
				playerMutex.unlock();
		//	}
			/*else if (player_type == 2)
			{
				playerMutex.lock();
				tempLocalPlayerMsg.m_vPos = otherPlayer.GetPosition();
				tempLocalPlayerMsg.m_vDirection = otherPlayer.GetDirection();
				tempLocalPlayerMsg.speed = otherPlayer.GetBallSpeed();
				playerMutex.unlock();
			}*/

			retval = send(sock, (char*)&tempLocalPlayerMsg, sizeof(tempLocalPlayerMsg), 0);//CplayerMsg로 전송해야함.
			if (CMyFunc::IsSocketError(retval, "sendTEmpLocalPlayerMsg"))break;
			//////////////////////////////////////////////////////////////////////////
			retval = CMyFunc::recvn(sock, (char*)&msgData, sizeof(msgData), 0);
			if (CMyFunc::IsSocketError(retval, "recvn msgdata")) {
				std::cout << "서버에 접속할수 없습니다" << std::endl;
				break;
			}
			
			if (player_type == 1)
			{
				playerMutex.lock();
				/*
				2016 / 12 / 3 / 4:35
				작성자:박요한(dygks910910@daum.net)
				설명:포지션값이 m_vDirection 값으로 들어가는 문제발생//////////////////////////////////////////////////////////////////////////
				*/
				otherPlayer.SetPosition(msgData.p2.m_vPos);
				otherPlayer.SetDirection(msgData.p2.m_vDirection);
				otherPlayer.SetBallSpeed(msgData.p2.speed);
				std::cout << msgData.p2.m_vPos << std::endl;
				playerMutex.unlock();
			}
			else if (player_type == 2)
			{
				playerMutex.lock();
				otherPlayer.SetPosition(msgData.p1.m_vPos);
				otherPlayer.SetDirection(msgData.p1.m_vDirection);
				otherPlayer.SetBallSpeed(msgData.p1.speed);
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
