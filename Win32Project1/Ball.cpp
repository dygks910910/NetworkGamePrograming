#include "stdafx.h"
#include "Ball.h"


void CBall::Initialize(const CVector2 & pos, const float & size, const float & speed)
{
	m_vBallPos = pos;
	m_vMoveDirection = CVector2(0, 0);
	m_fBallSize = size;
	m_fBallSpeed = speed;
}

void CBall::Progress()
{
}
/*
2016 / 10 / 27 / 16:24
작성자:박요한(dygks910910@daum.net)
설명:펜의 색상과 채워지는 색상을 결정해줄수 있게 추가.
*/
void CBall::Render(HDC hdc)
{
	//펜과 브러시의 오브젝트를 생성한다
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//펜을 생성한다. 
	myPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//펜을 선택하고 과거에 dc가 가지고 있는 펜의 모양은 old펜에 넣어준다.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Ellipse(hdc, m_vBallPos.x - m_fBallSize, m_vBallPos.y - m_fBallSize,
		m_vBallPos.x + m_fBallSize, m_vBallPos.y + m_fBallSize);

	//예전의 펜값을 다시 dc에 지정해준다. 
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	//쓰고난 펜을 삭제해준다.
	DeleteObject(myPen);
	DeleteObject(myBrush);
}

void CBall::Release()
{

}

void CBall::SetDirection(const CVector2 & dir)
{
	m_vMoveDirection = dir;
}



void CBall::move()
{
	if (m_vBallPos.x <= WINDOW_WIDTH - PLAYER_SIZE)
	{

	}
	m_vBallPos = m_vBallPos + (m_vMoveDirection*m_fBallSpeed);
}

CBall::CBall()
{
}


CBall::~CBall()
{
}
