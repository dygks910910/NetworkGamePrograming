#pragma once
#include"Obj.h"
/*
2016 / 10 / 27 / 15:53
�ۼ���:�ڿ���(dygks910910@daum.net)
����: ������ CBall ��ü�� �������ҵ� �;� CBall�� �̸��ٲ�.
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
	[2016/09/04 18��18��
	�ۼ��� : �ڿ���(dygks910910@daum.net)]
	����:�� �Լ��� player�� ��Ʈ��.
	*/
	void SetDirection(const CVector2& dir);
	void move();
	/*
	2016 / 10 / 27 / 16:16
	�ۼ���:�ڿ���(dygks910910@daum.net)
	����:�浹üũ �Լ��� �ۼ��ؾ���.(������â�� �浹 �� ��ü�� ��ü������ �浹.)
	*/
	void CheckCollision() {};
public:
	CBall();
	~CBall();
};

