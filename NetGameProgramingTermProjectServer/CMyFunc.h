#pragma once
#include"stdafx.h"

class CMyFunc
{
public:
	CMyFunc() {};
	~CMyFunc() {};
	static const int& recvn(const SOCKET& s, char* buf, const int& len, const int& flag);
	static void err_quit(char *msg);
	static void err_display(char *msg);
};

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
		//printf("%d����Ʈ ����", received);
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
