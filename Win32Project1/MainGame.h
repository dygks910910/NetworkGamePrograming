#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"DoubleBuffering.h"
#include<vector>
class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;


public:
	CMainGame();
	~CMainGame();
	void Initialize();
	void Progress();
	void Render();
/* 
[2016/09/02 18시57분 
작성자 : 박요한(dygks910910@daum.net)]
설명:MouseInputMessage()마우스 입력처리함수.
*/
	void MouseInputProcessing(const MSG& msg);
	void Release();
};