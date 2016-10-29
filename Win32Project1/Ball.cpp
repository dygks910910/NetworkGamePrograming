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
�ۼ���:�ڿ���(dygks910910@daum.net)
����:���� ����� ä������ ������ �������ټ� �ְ� �߰�.
*/
void CBall::Render(HDC hdc)
{
	//��� �귯���� ������Ʈ�� �����Ѵ�
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//���� �����Ѵ�. 
	myPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//���� �����ϰ� ���ſ� dc�� ������ �ִ� ���� ����� old�濡 �־��ش�.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Ellipse(hdc, m_vBallPos.x - m_fBallSize, m_vBallPos.y - m_fBallSize,
		m_vBallPos.x + m_fBallSize, m_vBallPos.y + m_fBallSize);

	//������ �氪�� �ٽ� dc�� �������ش�. 
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	//���� ���� �������ش�.
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
