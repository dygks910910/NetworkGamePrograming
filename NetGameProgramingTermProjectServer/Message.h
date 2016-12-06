#pragma once
#include"Vector2.h"
#include<iostream>
#include "Message.h"
#include "myHeader.h"

class CMessageBallInfo
{
public:
	CVector2 m_vPos;
};
#pragma pack()

class CPlayerMsg : public CMessageBallInfo {};

class CMsg_PlayerAndBall 
{
public:
	CPlayerMsg	 p1;
	CPlayerMsg	 p2;
	CPlayerMsg ball[3];
};
#pragma pack()

//
//class CMsg_PlayerAndBall2 : public CMsg_PlayerAndBall
//{
//public:
//	CPlayerMsg ball2;
//};
//#pragma  pack()
//
//class CMsg_PlayerAndBall3 : public CMsg_PlayerAndBall2
//{
//public:
//	CPlayerMsg ball3;
//};
//#pragma  pack()

class CMessageForReady 
{
public:
	int playerNum;
	bool bReady;
};
#pragma pack()

class CMessageForRestart 
{
public:
	bool bRestart;
};
#pragma pack()
//class CMessageForBallNum 
//{
//public:
//	int iBallNum;
//};
//#pragma pack()
