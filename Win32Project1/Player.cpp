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
	//��� �귯���� ������Ʈ�� �����Ѵ�
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//���� �����Ѵ�. 
	myPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//���� �����ϰ� ���ſ� dc�� ������ �ִ� ���� ����� old�濡 �־��ش�.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 0, 255));
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

void CPlayer::Release()
{
	
}
/*
2016 / 10 / 29 / 0:16
�ۼ���:�ڿ���(dygks910910@daum.net)
����:���콺�� �����ǿ� ���� �÷��̾��� ��ġ�� �ٲ�.�÷��̾��� ��ġ�� ���� �Ѿ�� ����.���� 1p�� ��ݺθ�,2p�� �¹ݺθ� �����.
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



