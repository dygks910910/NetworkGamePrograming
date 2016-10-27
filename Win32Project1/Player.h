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
/*
2016 / 10 / 27 / 15:36
작성자:박요한(dygks910910@daum.net)
설명:	moveup,moveDown 함수를 삭제하고 방향을 추가.방향을 추가하고 삭제한 함수를 하나로 합침.
*/
/*
2016 / 10 / 27 / 15:46
작성자:박요한(dygks910910@daum.net)
설명:삭제하고 상위 클래스 CBall 로 통합후 자식클래스로 Player를 둘것.
*/
class CPlayer :
	public CObj
{
	CVector2 m_vPlayerPos;
	CVector2	m_vMoveDirection;
	float m_fBallSize;
	float m_fBallSpeed;
public:
	CPlayer();
	~CPlayer();
	virtual void Initialize(const CVector2& pos, const float& size, const float& speed) ;
	virtual void Progress() ;
	virtual void Render(HDC) ;
	virtual void Release();
	/* 
	[2016/09/04 18시18분 
	작성자 : 박요한(dygks910910@daum.net)]
	설명:이 함수로 player를 컨트롤.
	*/
	void SetDirection(const CVector2& dir);
	void move();

};

