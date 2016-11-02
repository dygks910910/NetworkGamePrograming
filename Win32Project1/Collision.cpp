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
	
	//두 원 사이의 거리를 구하여 그 거리가 두원의 반지름의 합보다 작을경우 충돌로 판단
	double nDist;
	double nRadius;



	nDist = Distance(player.GetPosition(), ball.GetPosition()); //두 원 사이의 거리
	nRadius = player.GetBallSize() + ball.GetBallSize(); //두 원의 반지름의 합

	if (nDist <= nRadius) {
		beCollision = true;
		ComputeCollision(player, ball);
		return beCollision;
	}

	else
		return beCollision;
	
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
void Collision::ComputeCollision(CPlayer &player, CBall &ball) {

	std::cout << "충돌 처리함수 실행" << std::endl;

	CVector2 Dir;

	/*
	2016 / 11 / 2 / 17:27
	작성자:박요한(dygks910910@daum.net)
	설명:아직 방향은 정하지 못함.
	*/	
	// 방향벡터 ->AB = B - A 
	//player.SetDirection(ball.GetDirection() - player.GetDirection());

	// 부딪힌 Ball 의 방향을 방향벡터로 변환하기.
	ball.SetDirection(Dir);
};
