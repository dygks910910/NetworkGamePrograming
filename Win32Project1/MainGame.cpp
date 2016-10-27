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
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	
	GetClientRect(g_hWnd, &clientrect);
	m_Ball1.Initialize(CVector2(WINDOW_WIDTH - PLAYER_SIZE,WINDOW_HEIGHT/2)
		, PLAYER_SIZE, 1);
	m_doubleBuffering.Initialize(m_hdc, clientrect);

}
// process
void CMainGame::Progress()
{

}

// 그리기
void CMainGame::Render()
{
	/*m_doubleBuffering.WriteToBackBuffer(&m_player1);
	m_doubleBuffering.WriteToBackBuffer(&m_player2);
	m_doubleBuffering.Present(m_hdc);*/

	m_doubleBuffering.WriteToBackBuffer(&m_Ball1);
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
		cout << CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam)) << endl;// 마우스 입력 테스트.
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
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

