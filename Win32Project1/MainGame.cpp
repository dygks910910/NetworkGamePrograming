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
	m_vObj.reserve(100);
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);
	CObj* ball;
	for (int i = 0; i < 100; ++i)
	{
		ball = new CObj;
		ball->Initialize();
		m_vObj.push_back(ball);
	}
	//m_pBall = new CObj();
	//m_pBall->Initialize();
	m_doubleBuffering.Initialize(m_hdc, clientrect);
	
}

// process
void CMainGame::Progress()
{
	for (auto p : m_vObj)
	{
		p->Progress();
	}
}

// 그리기
void CMainGame::Render()
{
	for (auto p : m_vObj)
	{
		m_doubleBuffering.WriteToBackBuffer(p);

	}
	m_doubleBuffering.Present(m_hdc);
}

void CMainGame::MouseInputProcessing(const MSG& msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		cout << CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam));// 마우스 입력 테스트.
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

// 해제
void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hdc);

	for (int i = 0; i < m_vObj.size(); ++i)
	{
		delete m_vObj[i];
	}

}