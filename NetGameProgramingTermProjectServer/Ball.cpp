#include "stdafx.h"
#include "Ball.h"

void CBall::Initialize(const CVector2 & pos, const float & size, const float & speed)
{
	m_vBallPos = pos;
	m_vMoveDirection = CVector2(1, 1);
	m_fBallSize = size;
	m_fBallSpeed = speed;
}

void CBall::Progress()
{
	move();
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


/*
2016 / 10 / 30 / 19:44
�ۼ���:�ڿ���(dygks910910@daum.net)
����:������ â�� ���� �⺻���� �浹üũ.
*/
void CBall::move()
{
	//�����������쿡 ���� �浹üũ
	if (m_vBallPos.x <= WINDOW_WIDTH - PLAYER_SIZE)
	{
		m_vMoveDirection.x *= -1;
	}
	//���������쿡 ���� �浹üũ
	if (m_vBallPos.x >= 0 + PLAYER_SIZE)
	{
		m_vMoveDirection.x *= -1;
	}
	//�Ʒ��������쿡 ���� �浹üũ
	if (m_vBallPos.y <= WINDOW_HEIGHT - PLAYER_SIZE )
	{
		m_vMoveDirection.y *= -1;
	}
	//���������쿡 ���� �浹üũ
	if (m_vBallPos.y >= 0 + PLAYER_SIZE)
	{
		m_vMoveDirection.y *= -1;
	}

	

	//�� �̵�
	m_vBallPos = m_vBallPos + (m_vMoveDirection*m_fBallSpeed);
}

//��뿡 �浹�� �÷��̾�� 1����Ʈ ����.
void CBall::GoalCheck() 
{
	/*��� �ڵ� ����****
	//���� ���
	Rectangle(hdc, 
	0, 
	WINDOW_HEIGHT/3,
	GOAL_SIZE, 
	WINDOW_HEIGHT/3 * 2
	);

	//���� ���
	Rectangle(hdc, 
	WINDOW_WIDTH - GOAL_SIZE, 
	WINDOW_HEIGHT / 3,
	WINDOW_WIDTH, 
	WINDOW_HEIGHT / 3 * 2
	);
	*/

	//������� ��üũ
	if (m_vBallPos.x >= 0 && m_vBallPos.x <= GOAL_SIZE
		&& m_vBallPos.y >= WINDOW_HEIGHT / 3 && m_vBallPos.y <= WINDOW_HEIGHT / 3 * 2)
	{
		printf("������뿡 ���� �����ϴ�!! [2P 1��ȹ��]\n");
	}

	//������� ��üũ
	if (m_vBallPos.x >= WINDOW_WIDTH - GOAL_SIZE && m_vBallPos.x <= WINDOW_WIDTH
		&& m_vBallPos.y >= WINDOW_HEIGHT / 3 && m_vBallPos.y <= WINDOW_HEIGHT / 3 * 2)
	{
		printf("������뿡 ���� �����ϴ�!! [1P 1��ȹ��]\n");
	}

}
CBall::CBall()
{
}


CBall::~CBall()
{
}
