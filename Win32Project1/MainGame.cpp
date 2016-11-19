
#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include <stdlib.h>
#include <time.h>

CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}



// 초기화
void CMainGame::Initialize()
{
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);
	m_doubleBuffering.Initialize(m_hdc, clientrect);
	int temp[2];
	 

	m_ball.Initialize(CVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), BALL_SIZE, PLAYER_SPEED);
	
	//볼 생성시 초기방향 랜덤지정

	srand((unsigned)time(NULL));
	for (int i = 0; i < 2; ++i)
	{
		temp[i] = (rand() % 3) - 1;
		if (temp[i] == 0)
			--i;
	}
	

	m_ball.SetDirection(CVector2(temp[0], temp[1]));
	printf("temp[1] = %d \t temp[2] = %d \n", temp[0], temp[1]);

	m_player.Initialize(CVector2(WINDOW_WIDTH - PLAYER_SIZE, WINDOW_HEIGHT / 2),
		PLAYER_SIZE, PLAYER_SPEED);

}
// process
void CMainGame::Progress()
{
	m_ball.move();
	m_ball.GoalCheck();
	m_collision.ifCollision(m_player, m_ball);
}

// 그리기
void CMainGame::Render()
{

	m_doubleBuffering.WriteToBackBuffer(&m_gameUI);
	m_doubleBuffering.WriteToBackBuffer(&m_player);
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
		PostQuitMessage(0);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		m_player.MoveToMousePos(CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam)),"p2");
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
/*
[2016/09/04 01:56
작성자 : 이주(qpwoei25@naver.com)]
설명 : 타이머 처리함수 본문.
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


// 해제
void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hdc);


}

