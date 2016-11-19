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
		retval = CMyFunc::recvn(s, (char*)buff, sizeof(typeOfMessage), 0);
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvn typeOfMessage");
		}
	//메시지 본문을 받기.
	switch (typeOfMessage)
	{
	case e_MSG_TYPE::MSG_BALLNUM:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForBallNum), flag);
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvn CMessageForBallNum");
		}
		break;
	case e_MSG_TYPE::MSG_PLAYERINFO:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageBallInfo), flag);
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvn CMessageBallInfo");
		}
		break;
	case e_MSG_TYPE::MSG_READY:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForReady), flag);
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvn CMessageForReady");
		}
		break;
	case e_MSG_TYPE::MSG_RESTART:
		retval = CMyFunc::recvn(s, buff, sizeof(CMessageForRestart), flag);
		if (retval == SOCKET_ERROR)
		{
			CMyFunc::err_display("recvn CMessageForRestart");
		}
		break;
	}
	return retval;

}
