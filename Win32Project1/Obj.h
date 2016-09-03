#pragma once

#include "MyHeader.h"
#include"Vector2.h"

class CObj
{
	CVector2 m_vtBallPos;
	float m_nBallSize;
	float m_nBallSpeed;

public:
	CObj();
	~CObj();

	virtual void Initialize();
	virtual void Progress();
	virtual void Render(HDC);
	virtual void Release();

};