#include "stdafx.h"
#include "Collision.h"
#include <math.h>
#include <iostream>

Collision::Collision() 
{
	//to do this;
};

Collision::~Collision() {
	//to do this;
};


bool Collision::ifCollision(const CPlayer &player, CBall &ball) {
	
	//�� �� ������ �Ÿ��� ���Ͽ� �� �Ÿ��� �ο��� �������� �պ��� ������� �浹�� �Ǵ�
	double nDist;
	double nRadius;


	nDist = Distance(player.m_vPos, ball.GetPosition()); //�� �� ������ �Ÿ�
	nRadius = PLAYER_SIZE + ball.GetBallSize(); //�� ���� �������� ��

	if (nDist <= nRadius) {
		ComputeCollision(player, ball);
		return true;
	}

	else
		return false;
	
};

//�� �� ������ �Ÿ� �����ִ� �Լ�
double Collision::Distance(const CVector2& p1, const CVector2& p2) {
	double distance;

	//��Ÿ����� ����
	//pow(x,2) --> x�� 2��, sqrt() ������
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
};


//�浹ó�� �Լ�
void Collision::ComputeCollision(const CPlayer &player, CBall &ball) {

	/*std::cout << "�浹 ó���Լ� ����" << std::endl;

	std::cout << "player ���⺤�� : " << player.GetDirection() << "\t--��ġ : " << player.GetPosition() << std::endl;
	std::cout << "ball ���⺤�� : " << ball.GetDirection() << "\t--��ġ : " << ball.GetPosition() << std::endl;
*/
	CVector2 Dir;

	//���⺤�� ->AB = B - A 
	//player.SetDirection(ball.GetDirection() - player.GetDirection());
	Dir = player.m_vDirection - ball.GetDirection();


	//�ε��� Ball �� ������ ���⺤�ͷ� ��ȯ�ϱ�.
	ball.SetDirection(Dir);
};