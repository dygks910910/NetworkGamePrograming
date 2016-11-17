#pragma once
#include "RecvnAndMessageType.h"

CRecvnAndMessageType::CRecvnAndMessageType()
{
}


CRecvnAndMessageType::~CRecvnAndMessageType()
{
}

const int& CRecvnAndMessageType::operator()(const SOCKET& s, char *buff, const int& len, const int& flag)
{
	int typeOfMessage = 0;
	int retval = 0;
	//메시지 타입을 받기.
		CMyFunc::recvn(s, (char*)typeOfMessage, sizeof(typeOfMessage), 0);
	//메시지 본문을 받기.
	switch (typeOfMessage)
	{
	case e_MSG_TYPE::MSG_BALLNUM:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForBallNum), flag);
		break;
	case e_MSG_TYPE::MSG_PLAYERINFO:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageBallInfo), flag);
		break;
	case e_MSG_TYPE::MSG_READY:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForReady), flag);
		break;
	case e_MSG_TYPE::MSG_RESTART:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForRestart), flag);
		break;
	}
	return retval;

}
