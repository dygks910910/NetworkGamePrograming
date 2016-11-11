#pragma once
#include "Vector2.h"
class CMessage
{
public:
	CMessage();
	~CMessage();
};

class CMessageForPlayerInfo : public CMessage
{
public:
	CMessageForPlayerInfo() {};
	~CMessageForPlayerInfo() {};
	CVector2 pos;
	CVector2 dir;
	float speed;
};
#pragma pack

class CMessageForReady : public CMessage
{
public:
	CMessageForReady() {};
	~CMessageForReady() {};
	int playerNum;
	bool bReady;
};
#pragma pack

class CMessageForRestart : public CMessage
{
public:
	CMessageForRestart() {};
	~CMessageForRestart() {};
	bool bRestart;
};

class CMessageForBallNum : public CMessage
{
public:
	CMessageForBallNum() {};
	~CMessageForBallNum() {};
	int iBallNum;
};
