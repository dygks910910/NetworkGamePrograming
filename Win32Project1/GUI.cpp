#include "stdafx.h"
#include "GUI.h"

GUI::GUI() {
	//to do this!
}

GUI::~GUI() {
	//to do this!
}

void GUI::Initialize(){ }

void GUI::Progress(){ }

void GUI::Render(HDC hdc)
{
	//게임 테두리
	Rectangle(hdc, 1, 0, WINDOW_WIDTH - 1 , WINDOW_HEIGHT - 1);

	//펜과 브러시의 오브젝트를 생성한다
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//펜을 생성한다. 
	myPen = CreatePen(PS_DASHDOTDOT, 2, RGB(255, 100, 0));
	//펜을 선택하고 과거에 dc가 가지고 있는 펜의 모양은 old펜에 넣어준다.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 100, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	//
	// to do draw !!!!!!!!!!
	//

	//중앙선
	MoveToEx(hdc, WINDOW_WIDTH / 2, 0, NULL);
	LineTo(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	//좌측 골대
	Rectangle(hdc, 0, WINDOW_HEIGHT/3,
					GOAL_SIZE, WINDOW_HEIGHT/3*2);

	//우측 골대
	Rectangle(hdc, WINDOW_WIDTH - GOAL_SIZE, WINDOW_HEIGHT / 3,
		WINDOW_WIDTH, WINDOW_HEIGHT / 3 * 2);

	//
	//
	//

	//예전의 펜값을 다시 dc에 지정해준다. 
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	//쓰고난 펜을 삭제해준다.
	DeleteObject(myPen);
	DeleteObject(myBrush);
}

void GUI::Release(){ }



