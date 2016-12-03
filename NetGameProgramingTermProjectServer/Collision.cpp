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


bool Collision::ifCollision(const CPlayerMsg &player, CBall &ball) {
	
	//두 원 사이의 거리를 구하여 그 거리가 두원의 반지름의 합보다 작을경우 충돌로 판단
	double nDist;
	double nRadius;


	nDist = Distance(player.m_vPos, ball.GetPosition()); //두 원 사이의 거리
	nRadius = PLAYER_SIZE + ball.GetBallSize(); //두 원의 반지름의 합

	if (nDist <= nRadius) {
		//ComputeCollision(player, ball);
		return true;
	}

	else
		return false;
	
};

//두 점 사이의 거리 구해주는 함수
double Collision::Distance(const CVector2& p1, const CVector2& p2) {
	double distance;

	//피타고라스의 정리
	//pow(x,2) --> x의 2승, sqrt() 제곱근
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
};


//충돌처리 함수
void Collision::ComputeCollision(const CPlayerMsg &player, CBall &ball)
{
	ball.SetDirection(player.m_vDirection - ball.GetDirection());
};