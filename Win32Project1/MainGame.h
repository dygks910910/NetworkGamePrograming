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
[2016/09/02 18��57�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:MouseInputMessage()���콺 �Է�ó���Լ�.
*/
	void MouseInputProcessing(const MSG& msg);
	void Release();
};