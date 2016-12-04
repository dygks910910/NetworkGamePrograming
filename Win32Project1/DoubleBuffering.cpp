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
[2016/09/02 3��36�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:�ʱ�ȭ�ܰ�
*/
void CDoubleBuffering::Initialize(HDC hdc, RECT clientRect)
{
	static HBITMAP backBitmap = NULL;
	m_clientRect =  clientRect;
	backMemDC = CreateCompatibleDC(hdc);
	backBitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	hOldBitmap = (HBITMAP)SelectObject(backMemDC, backBitmap); //��ȭ�� ����
	FillRect(backMemDC, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH)); //��ȭ�� �� ����

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
	DeleteObject(SelectObject(backMemDC, hOldBitmap)); //������ �޸𸮿� ������Ʈ�� �������ش�.
	DeleteObject(hMyBitmap);
	DeleteDC(backMemDC);
	DeleteDC(MemDC);
}
