#pragma once
#include "Obj.h"
/* 
[2016/09/03 18��27�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:�� �÷��̾ �ۼ��Ұ���.������Ÿ������ �����д�.
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

