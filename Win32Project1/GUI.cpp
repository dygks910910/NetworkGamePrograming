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
	//���� �׵θ�
	Rectangle(hdc, 1, 0, WINDOW_WIDTH - 1 , WINDOW_HEIGHT - 1);

	//��� �귯���� ������Ʈ�� �����Ѵ�
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	//���� �����Ѵ�. 
	myPen = CreatePen(PS_DASHDOTDOT, 2, RGB(255, 100, 0));
	//���� �����ϰ� ���ſ� dc�� ������ �ִ� ���� ����� old�濡 �־��ش�.
	oldPen = (HPEN)SelectObject(hdc, myPen);
	myBrush = CreateSolidBrush(RGB(255, 100, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	//
	// to do draw !!!!!!!!!!
	//

	//�߾Ӽ�
	MoveToEx(hdc, WINDOW_WIDTH / 2, 0, NULL);
	LineTo(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	//���� ���
	Rectangle(hdc, 0, WINDOW_HEIGHT/3,
					GOAL_SIZE, WINDOW_HEIGHT/3*2);

	//���� ���
	Rectangle(hdc, WINDOW_WIDTH - GOAL_SIZE, WINDOW_HEIGHT / 3,
		WINDOW_WIDTH, WINDOW_HEIGHT / 3 * 2);

	//
	//
	//

	//������ �氪�� �ٽ� dc�� �������ش�. 
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	//���� ���� �������ش�.
	DeleteObject(myPen);
	DeleteObject(myBrush);
}

void GUI::Release(){ }



