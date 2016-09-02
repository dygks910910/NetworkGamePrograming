#pragma once
#include "MyHeader.h"
#include "Obj.h"
#include"DoubleBuffering.h"
#include<vector>
class CMainGame
{
	HDC m_hdc;
	//HDC m_memDC;
	vector<CObj*> m_vObj;
	//CObj* m_pBall;
	CDoubleBuffering m_doubleBuffering;

	//write to back DC
	//Present

public:
	CMainGame();
	~CMainGame();
	void Initialize();
	void Progress();
	void Render();
	void Release();
};