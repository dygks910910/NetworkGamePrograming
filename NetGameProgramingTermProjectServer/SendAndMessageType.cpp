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
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval = send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval += send(s, (char*)reinterpret_cast<CMessageBallInfo*>(msg), sizeof(CMessageBallInfo), 0);

		break;
	case e_MSG_TYPE::MSG_READY:
		typeSave = e_MSG_TYPE::MSG_READY;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval += send(s, (char*)reinterpret_cast<CMessageForReady*>(msg), sizeof(CMessageForReady), 0);

		break;
	case e_MSG_TYPE::MSG_RESTART:
		typeSave = e_MSG_TYPE::MSG_RESTART;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval += send(s, (char*)reinterpret_cast<CMessageForRestart*>(msg), sizeof(CMessageForRestart), 0);
		break;
	case e_MSG_TYPE::MSG_BALLNUM:
		typeSave = e_MSG_TYPE::MSG_BALLNUM;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval += send(s, (char*)typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
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

