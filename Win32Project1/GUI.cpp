#include "stdafx.h"
#include "GUI.h"
#include "MyHeader.h"

CGUI::CGUI()
{
	countSec = 0;
	p1Score = 0;
	p2Score = 0;
}


CGUI::~CGUI()
{
}

void CGUI::Initialize()
{
	countSec = 180;
}

void CGUI::Progress()
{

}

void CGUI::Render(HDC hdc)
{
	TCHAR temp[10];
	////////////////////////////중앙선 그리기//////////////////////////////////////////////
	MoveToEx(hdc, WINDOW_WIDTH / 2, 0,NULL);
	LineTo(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	////////////////////////////p1(오른쪽 골대 그리기)//////////////////////////////////////////////
	Rectangle(hdc,WINDOW_WIDTH - 10, WINDOW_HEIGHT / 2 + GOAL_SIZE,
		WINDOW_WIDTH, WINDOW_HEIGHT / 2 - GOAL_SIZE);

	///////////////////////////p2왼쪽 골대 그리기///////////////////////////////////////////////
	Rectangle(hdc, 0, WINDOW_HEIGHT / 2 + GOAL_SIZE, 10,WINDOW_HEIGHT / 2 - GOAL_SIZE);
	wsprintf(temp, "%d", countSec);
	TextOut(hdc, WINDOW_WIDTH / 2, 5, temp, strlen(temp));
	wsprintf(temp, "%d : %d", p1Score, p2Score);
	TextOut(hdc, WINDOW_WIDTH / 2 - 10, 20, temp, strlen(temp));
}

void CGUI::Release()
{

}
