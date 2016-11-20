#pragma once
#include "Vector2.h"
#include "Message.h"
#include "Ball.h"

class Collision  
{
private:
public:
	Collision();
	~Collision();
	bool ifCollision(const CPlayer &player, CBall &ball); //const?
	double Distance(const CVector2& p1, const CVector2& p2);
	void ComputeCollision(const CPlayer &player, CBall &ball);
};