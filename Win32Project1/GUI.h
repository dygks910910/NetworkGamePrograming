#pragma once
#include <windows.h>
#include "MyHeader.h"
#include "Obj.h"

//����ۿ� �׸������� CObj�� �����
class GUI : public CObj{
private:
	//null

public :
	GUI();
	~GUI();
	virtual void Initialize();
	virtual void Progress();
	virtual void Render(HDC);
	virtual void Release();
};