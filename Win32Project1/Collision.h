#pragma once
#include "Vector2.h"
#include "Player.h"
#include "Ball.h"

class Collision  
{
private:
	bool beCollision;

public:
	Collision();
	~Collision();
	bool ifCollision(CPlayer &player, CBall &ball); //const?
	double Distance(const CVector2& p1, const CVector2& p2);
	void ComputeCollision(CPlayer &player, CBall &ball);
};