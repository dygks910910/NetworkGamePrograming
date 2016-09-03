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
	m_hdc = GetDC(g_hWnd);
	RECT clientrect;
	GetClientRect(g_hWnd, &clientrect);

	m_doubleBuffering.Initialize(m_hdc, clientrect);
	
}

// process
void CMainGame::Progress()
{
}

// �׸���
void CMainGame::Render()
{

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
		cout << CVector2(LOWORD(msg.lParam), HIWORD(msg.lParam));// ���콺 �Է� �׽�Ʈ.
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

// ����
void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hdc);


}