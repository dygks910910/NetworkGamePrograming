#include "stdafx.h"
#include "DoubleBuffering.h"


CDoubleBuffering::CDoubleBuffering()
{
}


CDoubleBuffering::~CDoubleBuffering()
{
}
/* 
[2016/09/02 3시36분 
작성자 : 박요한(dygks910910@daum.net)]
설명:초기화단계
*/
void CDoubleBuffering::Initialize(HDC hdc, RECT clientRect)
{
	m_clientRect =  clientRect;
	m_memDC = CreateCompatibleDC(hdc);
	HBITMAP oldbitmap = CreateCompatibleBitmap(m_memDC, clientRect.right, clientRect.bottom);
	m_hPreBit = (HBITMAP)SelectObject(m_memDC, oldbitmap);
	FillRect(m_memDC, &clientRect, GetSysColorBrush(COLOR_WINDOW));

}
