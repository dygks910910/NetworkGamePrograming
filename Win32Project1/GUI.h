#pragma once
#include"Obj.h"
class CGUI : public CObj
{
public:
	CGUI();
	~CGUI();
	virtual void Initialize();
	virtual void Progress();
	virtual void Render(HDC);
	virtual void Release();
	int countSec;
	int p1Score;
	int p2Score;
};

