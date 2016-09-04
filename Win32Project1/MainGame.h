#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"DoubleBuffering.h"
#include"Player.h"
class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;
	CPlayer	 m_player1;
	CPlayer	 m_player2;


public:
	CMainGame();
	~CMainGame();
	void Initialize();
	void Progress();
	void Render();
	void Release();

/* 
[2016/09/02 18시57분 
작성자 : 박요한(dygks910910@daum.net)]
설명:MouseInputMessage()마우스 입력처리함수.
*/
	void MouseInputProcessing(const MSG& msg);
	void KeyboardInputProcessing(const MSG	& msg);
	void GameTimer(const MSG& msg);
};