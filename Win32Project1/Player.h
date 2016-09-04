#pragma once
#include "Obj.h"
/* 
[2016/09/03 18��27�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:�� �÷��̾ �ۼ��Ұ���.������Ÿ������ �����д�.
*/
/* 
[2016/09/04 18��11�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:CObj�� �ִ� �Լ����� �貸�Դ�. �����׸��� ����.MoveUp,Down�Լ��� �߰��� MainGame���� ��Ʈ���Ұ���.
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
	[2016/09/04 18��18�� 
	�ۼ��� : �ڿ���(dygks910910@daum.net)]
	����:�� �Լ��� player�� ��Ʈ��.
	*/
	void moveUp();
	void moveDown();

};

