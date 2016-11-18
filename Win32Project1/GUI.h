#pragma once
#include <windows.h>
#include "MyHeader.h"
#include "Obj.h"

//백버퍼에 그리기위해 CObj를 상속함
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