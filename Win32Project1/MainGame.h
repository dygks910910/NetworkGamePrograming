#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"Player.h"
#include"DoubleBuffering.h"
#include"CMyFunc.h"
#include"Timer.h"
#include<thread>
#include<mutex>
#include "GUI.h"
class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;
	
	
	std::thread* m_threadForSendRecv;
	
	WSADATA m_wsa;
	SOCKET m_clientSocket;
	SOCKADDR_IN m_server_Addr;
	std::mutex m_ballMutex;
	std::mutex m_playerMutex;
	CGUI	m_GUI;
public:
	CPlayer	 m_localPlayer;
	CPlayer	 m_otherPlayer;
	CBall m_ball;
	int m_playerType;
	int m_ballNum;

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
	
};

void SendAndRecvThread(const int& player_type,CPlayer& localPlayer,CPlayer& otherPlayer,CBall& ball,const SOCKET& sock);
static std::mutex ballMutex;
static std::mutex playerMutex;