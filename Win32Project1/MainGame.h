#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"Ball.h"
#include"DoubleBuffering.h"
class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;
	CBall m_Ball1;
	CBall m_Ball2;

public:
	CMainGame();
	~CMainGame();
	void Initialize();
	void Progress();
	void Render();
	void Release();

/* 
[2016/09/02 18��57�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:MouseInputMessage()���콺 �Է�ó���Լ�.
*/
	void MouseInputProcessing(const MSG& msg);
	void KeyboardInputProcessing(const MSG	& msg);
	void GameTimer(const MSG& msg);
};