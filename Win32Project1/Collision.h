#pragma once
#include "Vector2.h"
#include "Player.h"
#include "Ball.h"

class Collision : public CObj{
private:
	CVector2 CVplayerPos;
	CVector2 CVballPos;
	CVector2 CVplayerDir;
	CVector2 CVballDir;
	bool beCollision;

public:
	Collision();
	~Collision();
	bool ifCollision(CPlayer &player, CBall &ball); //const?
	double Distance(const CVector2& p1, const CVector2& p2);
	void ComputeCollision(CPlayer &player, CBall &ball);
};