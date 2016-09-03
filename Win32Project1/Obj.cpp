#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

/* 
[2016/09/02 3��37�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:������۸� �׽�Ʈ��.
*/
void CObj::Initialize()
{
	m_vtBallPos.x = rand() % 800;
	m_vtBallPos.y = rand() % 600;

	m_nBallSize = rand() % 50;
	m_nBallSpeed = rand() % 10;
}

void CObj::Progress()
{
	m_vtBallPos.x += m_nBallSpeed;

	if ((m_vtBallPos.x >= WINDOW_WIDTH - m_nBallSize) || (m_vtBallPos.x <= m_nBallSize))
		m_nBallSpeed *= -1;
}

void CObj::Render(HDC hdc)
{
	Ellipse(hdc, m_vtBallPos.x - m_nBallSize, m_vtBallPos.y - m_nBallSize,
		m_vtBallPos.x + m_nBallSize, m_vtBallPos.y + m_nBallSize);
}

void CObj::Release()
{

}