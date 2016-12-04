#include "stdafx.h"
#include "DoubleBuffering.h"
#include"MyHeader.h"

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
	static HBITMAP backBitmap = NULL;
	m_clientRect =  clientRect;
	backMemDC = CreateCompatibleDC(hdc);
	backBitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	hOldBitmap = (HBITMAP)SelectObject(backMemDC, backBitmap); //도화지 세팅
	FillRect(backMemDC, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경

	SelectObject(MemDC, hMyBitmap);
	HBITMAP oldbitmap = CreateCompatibleBitmap(backMemDC, clientRect.right, clientRect.bottom);

	
}

void CDoubleBuffering::Present(HDC hdc)
{
		BitBlt(hdc, 0, 0, m_clientRect.right, m_clientRect.bottom, backMemDC, 0, 0, SRCCOPY);
		Release();
		Initialize(hdc,m_clientRect);
}

void CDoubleBuffering::Release()
{
	DeleteObject(SelectObject(backMemDC, hOldBitmap)); //끝으로 메모리와 오브젝트을 해지해준다.
	DeleteObject(hMyBitmap);
	DeleteDC(backMemDC);
	DeleteDC(MemDC);
}
