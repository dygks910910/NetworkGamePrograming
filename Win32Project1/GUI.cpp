#include "stdafx.h"
#include "GUI.h"
#include "MyHeader.h"

CGUI::CGUI()
{
}


CGUI::~CGUI()
{
}

void CGUI::Initialize()
{

}

void CGUI::Progress()
{

}

void CGUI::Render(HDC hdc)
{
	////////////////////////////중앙선 그리기//////////////////////////////////////////////
	MoveToEx(hdc, WINDOW_WIDTH / 2, 0,NULL);
	LineTo(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	////////////////////////////p1(오른쪽 골대 그리기)//////////////////////////////////////////////
	Rectangle(hdc, WINDOW_WIDTH - GOAL_SIZE, WINDOW_HEIGHT / 2 + GOAL_SIZE,
		WINDOW_WIDTH, WINDOW_HEIGHT / 2 - GOAL_SIZE);

	///////////////////////////p2왼쪽 골대 그리기///////////////////////////////////////////////
	Rectangle(hdc, 0, WINDOW_HEIGHT / 2 + GOAL_SIZE, GOAL_SIZE, WINDOW_HEIGHT / 2 - GOAL_SIZE);
}

void CGUI::Release()
{

}
