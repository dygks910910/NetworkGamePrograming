#pragma once

#include "MyHeader.h"

class CObj
{
	POINT m_ptBall;
	int m_nBallSize;
	int m_nBallSpeed;

public:
	CObj();
	~CObj();

	void Initialize();
	void Progress();
	void Render(HDC);
	void Release();
};