#include "CMyFunc.h"


void CMyFunc::errCheckAndErrQuit(const SOCKET& socket, char* msg)
{
	{
		if (socket == INVALID_SOCKET)
		{
			err_quit(msg);
		}
	}
}
const int& CMyFunc::recvn(const SOCKET& s, char* buf, const int& len, const int& flag)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flag);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	//printf("%d바이트 받음", received);
	return len - left;
}
void CMyFunc::err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
void CMyFunc::err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void CMyFunc::errCheckAndErrDisplay(const SOCKET& socket, char* msg)
{
	if (socket == INVALID_SOCKET)
	{
		err_display(msg);
	}
}

bool CMyFunc::IsSocketError(const int& retval, char* msg)
{
	if (retval == SOCKET_ERROR)
	{
		err_quit(msg);
		return true;
	}
	return false;
}

