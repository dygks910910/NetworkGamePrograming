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


/*
2016 / 10 / 30 / 19:44
작성자:박요한(dygks910910@daum.net)
설명:윈도우 창에 대한 기본적인 충돌체크.
*/
void CBall::move()
{
	//오른쪽윈도우에 대한 충돌체크
	if (m_vBallPos.x <= WINDOW_WIDTH - PLAYER_SIZE)
	{
		m_vMoveDirection.x *= -1;
	}
	//왼쪽윈도우에 대한 충돌체크
	if (m_vBallPos.x >= 0 + PLAYER_SIZE)
	{
		m_vMoveDirection.x *= -1;
	}
	//아래쪽윈도우에 대한 충돌체크
	if (m_vBallPos.y <= WINDOW_HEIGHT - PLAYER_SIZE )
	{
		m_vMoveDirection.y *= -1;
	}
	//윗쪽윈도우에 대한 충돌체크
	if (m_vBallPos.y >= 0 + PLAYER_SIZE)
	{
		m_vMoveDirection.y *= -1;
	}

	

	//볼 이동
	m_vBallPos = m_vBallPos + (m_vMoveDirection*m_fBallSpeed);
}

//골대에 충돌시 플레이어는 1포인트 득점.
void CBall::GoalCheck() 
{
	/*골대 코드 참고****
	//좌측 골대
	Rectangle(hdc, 
	0, 
	WINDOW_HEIGHT/3,
	GOAL_SIZE, 
	WINDOW_HEIGHT/3 * 2
	);

	//우측 골대
	Rectangle(hdc, 
	WINDOW_WIDTH - GOAL_SIZE, 
	WINDOW_HEIGHT / 3,
	WINDOW_WIDTH, 
	WINDOW_HEIGHT / 3 * 2
	);
	*/

	//좌측골대 골체크
	if (m_vBallPos.x >= 0 && m_vBallPos.x <= GOAL_SIZE
		&& m_vBallPos.y >= WINDOW_HEIGHT / 3 && m_vBallPos.y <= WINDOW_HEIGHT / 3 * 2)
	{
		printf("좌측골대에 골이 들어갔습니다!! [2P 1점획득]\n");
	}

	//우측골대 골체크
	if (m_vBallPos.x >= WINDOW_WIDTH - GOAL_SIZE && m_vBallPos.x <= WINDOW_WIDTH
		&& m_vBallPos.y >= WINDOW_HEIGHT / 3 && m_vBallPos.y <= WINDOW_HEIGHT / 3 * 2)
	{
		printf("우측골대에 골이 들어갔습니다!! [1P 1점획득]\n");
	}

}
CBall::CBall()
{
}


CBall::~CBall()
{
}
