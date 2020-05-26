#pragma once

#include"Vector2.h"

class CObj
{
public:
	CObj();
	~CObj();

	virtual void Initialize() {};
	virtual void Progress() {};
	virtual void Render(HDC) {};
	virtual void Release() {};

};