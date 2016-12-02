#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"Player.h"
#include"DoubleBuffering.h"
#include"CMyFunc.h"
#include"Timer.h"
#include<thread>
#include<mutex>

class CMainGame
{
	HDC m_hdc;
	CDoubleBuffering m_doubleBuffering;
	
	WSADATA m_wsa;
	SOCKET m_clientSocket;
	SOCKADDR_IN m_server_Addr;
	std::thread* m_threadForSendRecv;
	int m_ballNum;
	int m_playerType;

	std::mutex m_ballMutex;
	std::mutex m_playerMutex;

public:
	CPlayer	 m_p1;
	CPlayer	 m_p2;
	CBall m_ball;

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

void SendAndRecvThread(const int& player_type,CPlayer& p1,CPlayer& p2,CBall& ball,const SOCKET& sock);