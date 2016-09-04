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
	m_vtBallPos = pos;

	m_fBallSize = size;
	m_fBallSpeed = speed	;
}

void CPlayer::Progress()
{
	/*m_vtBallPos.x += m_nBallSpeed;

	if ((m_vtBallPos.x >= WINDOW_WIDTH - m_nBallSize) || (m_vtBallPos.x <= m_nBallSize))
		m_nBallSpeed *= -1;*/
}

void CPlayer::Render(HDC hdc)
{
	Ellipse(hdc, m_vtBallPos.x - m_fBallSize, m_vtBallPos.y - m_fBallSize,
		m_vtBallPos.x + m_fBallSize, m_vtBallPos.y + m_fBallSize);
}

void CPlayer::Release()
{
	
}

void CPlayer::moveUp()
{
	if (0 >= m_vtBallPos.y - m_fBallSize)
		return;

	m_vtBallPos.y -= m_fBallSpeed;
}
void CPlayer::moveDown()
{
	if (WINDOW_HEIGHT <= m_vtBallPos.y+m_fBallSize)
		return;
	std::cout << m_vtBallPos << endl;
	m_vtBallPos.y += m_fBallSpeed;
}
