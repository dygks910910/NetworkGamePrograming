#include "stdafx.h"
#include "Collision.h"
#include <math.h>
#include <iostream>

Collision::Collision() : beCollision(false) {
	//to do this;
};

Collision::~Collision() {
	//to do this;
};


bool Collision::ifCollision(CPlayer &player, CBall &ball) {
	
	//�� �� ������ �Ÿ��� ���Ͽ� �� �Ÿ��� �ο��� �������� �պ��� ������� �浹�� �Ǵ�
	double nDist;
	double nRadius;


	nDist = Distance(player.GetPosition(), ball.GetPosition()); //�� �� ������ �Ÿ�
	nRadius = player.GetBallSize() + ball.GetBallSize(); //�� ���� �������� ��

	if (nDist <= nRadius) {
		beCollision = true;
		ComputeCollision(player, ball);
		return beCollision;
	}

	else
		return beCollision;
	
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
void Collision::ComputeCollision(CPlayer &player, CBall &ball) {

	player.SetDirection({ 0,0 });
	std::cout << "�浹 ó���Լ� ����" << std::endl;

	std::cout << "player ���⺤�� : " << player.GetDirection() << "\t--��ġ : " << player.GetPosition() << std::endl;
	std::cout << "ball ���⺤�� : " << ball.GetDirection() << "\t--��ġ : " << ball.GetPosition() << std::endl;

	CVector2 Dir;

	//���⺤�� ->AB = B - A 
	player.SetDirection(player.GetDirection() - ball.GetDirection());
	//player.SetDirection(ball.GetDirection() - player.GetDirection());
	Dir = player.GetDirection();


	//�ε��� Ball �� ������ ���⺤�ͷ� ��ȯ�ϱ�.
	ball.SetDirection(Dir);
};