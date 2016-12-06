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
	//CTimer m_countTimer;
public:
	CPlayer	 m_localPlayer;
	CPlayer	 m_otherPlayer;
	CBall m_ball[MAX_BALLNUM];
	int m_playerType;
	int m_ballNum;
	bool m_bGameOver;
	CMainGame();
	~CMainGame();
	void Initialize();
	void Progress();
	void Render();
	void Release();
	void SendAndRecvThread();

/* 
[2016/09/02 18��57�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:MouseInputMessage()���콺 �Է�ó���Լ�.
*/
	void MouseInputProcessing(const MSG& msg);
	void KeyboardInputProcessing(const MSG	& msg);
	
};
static std::mutex ballMutex;
static std::mutex playerMutex;