#pragma once
#include "Obj.h"
/* 
[2016/09/03 18시27분 
작성자 : 박요한(dygks910910@daum.net)]
설명:곧 플레이어를 작성할것임.프로토타입으로 만들어둔다.
*/
class CPlayer :
	public CObj
{
public:
	CPlayer();
	~CPlayer();

	virtual void Initialize() {};
	virtual void Progress() {};
	virtual void Render(HDC) {};
	virtual void Release() {};
};

