#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(const CVector2& pos, const float& size, const float& speed, const int& playerType)
{
	CBall::Initialize(pos, size, speed);
	m_playerType = playerType;
}

void CPlayer::Progress()
{
	/*m_vPlayerPos.x += m_nBallSpeed;

	if ((m_vPlayerPos.x >= WINDOW_WIDTH - m_nBallSize) || (m_vPlayerPos.x <= m_nBallSize))
		m_nBallSpeed *= -1;*/
}

void CPlayer::Render(HDC hdc)
{
	//펜과 브러시의 오브젝트를 생성한다
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//펜을 생성한다. 
	myPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//펜을 선택하고 과거에 dc가 가지고 있는 펜의 모양은 old펜에 넣어준다.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 0, 255));
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

void CPlayer::Release()
{
	
}
/*
2016 / 10 / 29 / 0:16
작성자:박요한(dygks910910@daum.net)
설명:마우스의 포지션에 따라서 플레이어의 위치가 바뀜.플레이어의 위치가 반을 넘어갈순 없음.따라서 1p면 우반부를,2p면 좌반부를 사용함.
*/
void CPlayer::MoveToMousePos(const CVector2& MousePos)
{

		if (m_playerType == 1)
		{
			if (MousePos.x <= WINDOW_WIDTH / 2)
			{
				SetPosition(CVector2((float)WINDOW_WIDTH / 2,MousePos.y));
				return;
			}
		}
		if (m_playerType == 2)
		{
			if (MousePos.x >= WINDOW_WIDTH / 2)
			{
				SetPosition(CVector2((float)WINDOW_WIDTH / 2, MousePos.y));
				return;

			}
		}
			SetPosition(MousePos);
}



