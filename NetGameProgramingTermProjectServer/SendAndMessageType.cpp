#include "SendAndMessageType.h"
#include "enum.h"


CSendAndMessageType::CSendAndMessageType()
{
}


CSendAndMessageType::~CSendAndMessageType()
{
}

const int& CSendAndMessageType::operator()(CMessage* msg, const SOCKET& s, char *buff, const int& len, const int& flag, const int& msgType)
{
	int typeSave=0;
	int retval = 0;
	switch (msgType)
	{
	case e_MSG_TYPE::MSG_PLAYERINFO:
		typeSave = e_MSG_TYPE::MSG_PLAYERINFO;
		//몇바이트를 보낼건지 알려주는 4바이트를 먼저 보냄.
		retval = send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg에 담긴 메시지를 보내줌.
		retval += send(s, (char*)reinterpret_cast<CMessageBallInfo*>(msg), sizeof(CMessageBallInfo), 0);

		break;
	case e_MSG_TYPE::MSG_READY:
		typeSave = e_MSG_TYPE::MSG_READY;
		//몇바이트를 보낼건지 알려주는 4바이트를 먼저 보냄.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg에 담긴 메시지를 보내줌.
		retval += send(s, (char*)reinterpret_cast<CMessageForReady*>(msg), sizeof(CMessageForReady), 0);

		break;
	case e_MSG_TYPE::MSG_RESTART:
		typeSave = e_MSG_TYPE::MSG_RESTART;
		//몇바이트를 보낼건지 알려주는 4바이트를 먼저 보냄.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg에 담긴 메시지를 보내줌.
		retval += send(s, (char*)reinterpret_cast<CMessageForRestart*>(msg), sizeof(CMessageForRestart), 0);
		break;
	case e_MSG_TYPE::MSG_BALLNUM:
		typeSave = e_MSG_TYPE::MSG_BALLNUM;
		//몇바이트를 보낼건지 알려주는 4바이트를 먼저 보냄.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg에 담긴 메시지를 보내줌.
		retval += send(s, (char*)reinterpret_cast<CMessageForBallNum*>(msg), sizeof(CMessageForBallNum), 0);
		break;
	case e_MSG_TYPE::MSG_PLAYERANDBALL1:
		break;
	case e_MSG_TYPE::MSG_PLAYERANDBALL2:
		break;
	case e_MSG_TYPE::MSG_PLAYERANDBALL3:
		break;
	default:
		break;
	}
	return retval;
}

