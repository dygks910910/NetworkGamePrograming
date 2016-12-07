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
	char tempAddr[100];
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa))
	{
		CMyFunc::err_quit("wsaStartup");
	}
	m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	CMyFunc::IsSocketError(retval, "socket()");
	std::cout << "socket()" << std::endl;
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	std::cout << "ip주소 입력:"; std::cin >> tempAddr;
	m_server_Addr.sin_addr.s_addr = inet_addr(tempAddr);
	m_server_Addr.sin_family = AF_INET;
	m_server_Addr.sin_port = htons(PORT);

	retval = connect(m_clientSocket, (SOCKADDR*)&m_server_Addr, sizeof(m_server_Addr));
	CMyFunc::IsSocketError(retval, "connect");
	std::cout << "connect()" << std::endl;
	char tempBuff[10];
	CMessageForReady msg_ready;
	retval = recv(m_clientSocket, tempBuff, sizeof(tempBuff), 0);
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

	retval = recv(m_clientSocket, (char*)&m_ballNum, sizeof(m_ballNum), 0);
	CMyFunc::IsSocketError(retval, "send ballnum");
	//////////////////////////////////////////////////////////////////////////
	
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);
	m_doubleBuffering.Initialize(m_hdc, clientrect);
	for (int i = 0; i < m_ballNum; ++i) {
		m_ball[i].Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE, PLAYER_SPEED);
	}

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
	//m_countTimer.startTimer();
	//retval = recv(m_clientSocket, (char*)&gameStart, sizeof(gameStart), 0);
	//if (gameStart)
	m_threadForSendRecv = new std::thread([&]() {SendAndRecvThread(); });

}
// process
void CMainGame::Progress()
{
	//m_ball.move();
	/*m_GUI.countSec = m_countTimer.countDown(180);
	for (int i = 0; i < m_ballNum; ++i) 
	{
		if (m_ball[i].GetPosition().x >= WINDOW_WIDTH - PLAYER_SIZE &&
			m_ball[i].GetPosition().y < WINDOW_HEIGHT / 2 + GOAL_SIZE &&
			m_ball[i].GetPosition().y > WINDOW_HEIGHT / 2 - GOAL_SIZE)
		{
			m_GUI.p1Score += 1;
		}
		if (m_ball[i].GetPosition().x <= PLAYER_SIZE &&
			m_ball[i].GetPosition().y < WINDOW_HEIGHT / 2 + GOAL_SIZE &&
			m_ball[i].GetPosition().y > WINDOW_HEIGHT / 2 - GOAL_SIZE)
		{
			m_GUI.p2Score += 1;
		}
	}*/
}

// 그리기
void CMainGame::Render()
{
	/*m_doubleBuffering.WriteToBackBuffer(&m_player1);
	m_doubleBuffering.WriteToBackBuffer(&m_player2);
	m_doubleBuffering.Present(m_hdc);*/
	m_doubleBuffering.WriteToBackBuffer(&m_GUI);
	m_doubleBuffering.WriteToBackBuffer(&m_localPlayer);
	m_doubleBuffering.WriteToBackBuffer(&m_otherPlayer);
	for (int i = 0; i < m_ballNum; ++i)
	{
		m_doubleBuffering.WriteToBackBuffer(&m_ball[i]);
	}
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

void CMainGame::SendAndRecvThread()
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
				tempLocalPlayerMsg.m_vPos = m_localPlayer.GetPosition();
		//	}
			/*else if (player_type == 2)
			{
				playerMutex.lock();
				tempLocalPlayerMsg.m_vPos = otherPlayer.GetPosition();
				tempLocalPlayerMsg.m_vDirection = otherPlayer.GetDirection();
				tempLocalPlayerMsg.speed = otherPlayer.GetBallSpeed();
				playerMutex.unlock();
			}*/
			retval = send(m_clientSocket, (char*)&tempLocalPlayerMsg, sizeof(tempLocalPlayerMsg), 0);//CplayerMsg로 전송해야함.
			if (CMyFunc::IsSocketError(retval, "sendTEmpLocalPlayerMsg"))break;
			//////////////////////////////////////////////////////////////////////////
			retval = recv(m_clientSocket, (char*)&msgData, sizeof(msgData), 0);
			if (CMyFunc::IsSocketError(retval, "recvn msgdata")) {
				std::cout << "서버에 접속할수 없습니다" << std::endl;
				break;
			}
			m_GUI.p1Score = msgData.p1Score;
			m_GUI.p2Score = msgData.p2Score;

			if (m_playerType == 1)
			{
				playerMutex.lock();
				/*
				2016 / 12 / 3 / 4:35
				작성자:박요한(dygks910910@daum.net)
				설명:포지션값이 m_vDirection 값으로 들어가는 문제발생//////////////////////////////////////////////////////////////////////////
				*/
				m_otherPlayer.SetPosition(msgData.p2.m_vPos);
				//std::cout << msgData.p2.m_vPos << std::endl;
				playerMutex.unlock();
			}
			else if (m_playerType == 2)
			{
				playerMutex.lock();
				m_otherPlayer.SetPosition(msgData.p1.m_vPos);
				//std::cout << msgData.p1.m_vPos << std::endl;
				playerMutex.unlock();
			}
			ballMutex.lock();
			for (int i = 0; i < m_ballNum; ++i)
			{
				m_ball[i].SetPosition(msgData.ball[i].m_vPos);
			}
			ballMutex.unlock();
			m_GUI.countSec = msgData.countTime;
			timer.startTimer();
		}
		else
		{
			Sleep(1000 / FPS - timer.getElapsedTime());
		}
		/////////////////////종료조건/////////////////////////////////////////////////////
		if (/*m_countTimer.restTime <= 0 ||*/ m_GUI.p1Score >= 3 || m_GUI.p2Score >= 3)
		{
			if (msgData.p1Score >= 3)
			{
				MessageBox(g_hWnd, "승리", "p1승리", MB_OK);
			}
			else if (msgData.countTime <= 0)
			{
				MessageBox(g_hWnd, "무승부", "무승부", MB_OK);
			}
			else if (msgData.p2Score >= 3)
			{
				MessageBox(g_hWnd, "승리", "p2승리", MB_OK);
			}
			exit(1);
			return;
		}
	}
}
