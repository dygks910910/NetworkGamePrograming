#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

/* 
[2016/09/02 3시37분 
작성자 : 박요한(dygks910910@daum.net)]
설명:더블버퍼링 테스트용.
*/
void CObj::Initialize()
{
	m_ptBall.x = rand()%800;
	m_ptBall.y = rand()%600;

	m_nBallSize = rand()%50;
	m_nBallSpeed = rand()%10;
}

void CObj::Progress()
{
	m_ptBall.x += m_nBallSpeed;

	if ((m_ptBall.x >= WINDOW_WIDTH - m_nBallSize) || (m_ptBall.x <= m_nBallSize))
		m_nBallSpeed *= -1;
}

void CObj::Render(HDC hdc)
{
	Ellipse(hdc, m_ptBall.x - m_nBallSize, m_ptBall.y - m_nBallSize,
		m_ptBall.x + m_nBallSize, m_ptBall.y + m_nBallSize);
}

void CObj::Release()
{

}