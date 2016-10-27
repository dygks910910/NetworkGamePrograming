#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(const CVector2& pos, const float& size,const float& speed)
{
	m_vPlayerPos = pos;
	m_vMoveDirection = CVector2(0, 0);
	m_fBallSize = size;
	m_fBallSpeed = speed	;
}

void CPlayer::Progress()
{
	/*m_vPlayerPos.x += m_nBallSpeed;

	if ((m_vPlayerPos.x >= WINDOW_WIDTH - m_nBallSize) || (m_vPlayerPos.x <= m_nBallSize))
		m_nBallSpeed *= -1;*/
}

void CPlayer::Render(HDC hdc)
{
	Ellipse(hdc, m_vPlayerPos.x - m_fBallSize, m_vPlayerPos.y - m_fBallSize,
		m_vPlayerPos.x + m_fBallSize, m_vPlayerPos.y + m_fBallSize);
}

void CPlayer::Release()
{
	
}

void CPlayer::SetDirection(const CVector2& dir)
{
	m_vMoveDirection = dir;
}

void CPlayer::move()
{
	if (m_vPlayerPos.x <= WINDOW_WIDTH - PLAYER_SIZE)
	{
			
	}
	m_vPlayerPos = m_vPlayerPos + (m_vMoveDirection*m_fBallSpeed);
}

