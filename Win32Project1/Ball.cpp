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

void CBall::Render(HDC hdc)
{
	Ellipse(hdc, m_vBallPos.x - m_fBallSize, m_vBallPos.y - m_fBallSize,
		m_vBallPos.x + m_fBallSize, m_vBallPos.y + m_fBallSize);
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
