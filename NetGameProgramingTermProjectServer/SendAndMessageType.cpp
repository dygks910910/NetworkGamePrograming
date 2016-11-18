#include "SendAndMessageType.h"
#include "enum.h"
#include "CMyFunc.h"

CSendAndMessageType::CSendAndMessageType()
{
}


CSendAndMessageType::~CSendAndMessageType()
{
}

const int& CSendAndMessageType::operator()( const SOCKET& s, char *buff, const int& len, const int& flag, const int& msgType)
{
	int typeSave=0;
	int retval = 0;
	switch (msgType)
	{
	case e_MSG_TYPE::MSG_PLAYERINFO:
		typeSave = e_MSG_TYPE::MSG_PLAYERINFO;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval = send(s, (char*)&typeSave, sizeof(typeSave), 0);
		CMyFunc::IsSocketError(retval, "send(e_MSG_TYPE::MSG_PLAYERINFO_typeSave)");
		//msg�� ��� �޽����� ������.
		retval = send(s, buff, sizeof(CMessageBallInfo), 0);
		CMyFunc::IsSocketError(retval, "send(e_MSG_TYPE::MSG_PLAYERINFO_CMessageBallInfo)");


		break;
	case e_MSG_TYPE::MSG_READY:
		typeSave = e_MSG_TYPE::MSG_READY;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval = send(s, (char*)&typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval = send(s, (char*)buff, sizeof(CMessageForReady), 0);

		break;
	case e_MSG_TYPE::MSG_RESTART:
		typeSave = e_MSG_TYPE::MSG_RESTART;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval = send(s, (char*)&typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval = send(s, (char*)buff, sizeof(CMessageForRestart), 0);
		break;
	case e_MSG_TYPE::MSG_BALLNUM:
		typeSave = e_MSG_TYPE::MSG_BALLNUM;
		//�����Ʈ�� �������� �˷��ִ� 4����Ʈ�� ���� ����.
		retval = send(s, (char*)&typeSave, sizeof(typeSave), 0);
		//msg�� ��� �޽����� ������.
		retval = send(s, (char*)buff, sizeof(CMessageForBallNum), 0);
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

