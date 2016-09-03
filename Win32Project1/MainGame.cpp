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

	m_doubleBuffering.Initialize(m_hdc, clientrect);
	
}

// process
void CMainGame::Progress()
{
}

// 그리기
void CMainGame::Render()
{

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


}