#pragma once
#include "Obj.h"
/* 
[2016/09/03 18시27분 
작성자 : 박요한(dygks910910@daum.net)]
설명:곧 플레이어를 작성할것임.프로토타입으로 만들어둔다.
*/
/* 
[2016/09/04 18시11분 
작성자 : 박요한(dygks910910@daum.net)]
설명:CObj에 있는 함수들을 배껴왔다. 원을그리기 위해.MoveUp,Down함수를 추가해 MainGame에서 컨트롤할것임.
*/
class CPlayer :
	public CObj
{
	CVector2 m_vtBallPos;
	float m_fBallSize;
	float m_fBallSpeed;
public:
	CPlayer();
	~CPlayer();

	virtual void Initialize(const CVector2& pos, const float& size, const float& speed) ;
	virtual void Progress() ;
	virtual void Render(HDC) ;
	virtual void Release() ;

	/* 
	[2016/09/04 18시18분 
	작성자 : 박요한(dygks910910@daum.net)]
	설명:이 함수로 player를 컨트롤.
	*/
	void moveUp();
	void moveDown();

};

