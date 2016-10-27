#pragma once
#include"Obj.h"
/*
2016 / 10 / 27 / 15:53
작성자:박요한(dygks910910@daum.net)
설명: 삭제후 CBall 객체가 더적당할듯 싶어 CBall로 이름바꿈.
*/
class CBall:
	public CObj 
{
	CVector2 m_vBallPos;
	CVector2	m_vMoveDirection;
	float m_fBallSize;
	float m_fBallSpeed;
public:
	virtual void Initialize(const CVector2& pos, const float& size, const float& speed);
	virtual void Progress();
	virtual void Render(HDC);
	virtual void Release();
	/*
	[2016/09/04 18시18분
	작성자 : 박요한(dygks910910@daum.net)]
	설명:이 함수로 player를 컨트롤.
	*/
	void SetDirection(const CVector2& dir);
	void move();
	/*
	2016 / 10 / 27 / 16:16
	작성자:박요한(dygks910910@daum.net)
	설명:충돌체크 함수를 작성해야함.(윈도우창에 충돌 및 객체와 객체끼리의 충돌.)
	*/
	void CheckCollision() {};
public:
	CBall();
	~CBall();
};

