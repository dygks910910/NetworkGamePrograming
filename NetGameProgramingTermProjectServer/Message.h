#pragma once

#include<WinSock2.h>
#include"Vector2.h"
#include<iostream>
#include "Message.h"
#include "Vector2.h"
class CMessage
{
};

class CMessageBallInfo : public CMessage
{
public:
	CVector2 m_vPos;
	CVector2 m_vDirection;
	float speed;

};
#pragma pack
class CPlayer : public CMessageBallInfo {  };

class CMessageForReady : public CMessage
{
public:
	int playerNum;
	bool bReady;
};
#pragma pack

class CMessageForRestart : public CMessage
{
public:
	bool bRestart;
};

class CMessageForBallNum : public CMessage
{
public:
	int iBallNum;
};

