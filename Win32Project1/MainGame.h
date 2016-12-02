#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"Player.h"
#include"DoubleBuffering.h"
#include"CMyFunc.h"
class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;
	CPlayer	 m_player	;
	CBall m_ball;
	WSADATA m_wsa;
	SOCKET m_clientSocket;
	SOCKADDR_IN m_server_Addr;
	
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
	void SendAndRecvThread();
	//나는야 바다의왕자.
	
};