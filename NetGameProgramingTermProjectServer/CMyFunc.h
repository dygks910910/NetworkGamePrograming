#pragma once
#include "myHeader.h"
class CMyFunc
{
public:
	CMyFunc() {};
	~CMyFunc() {};
	static const int& recvn(const SOCKET& s, char* buf, const int& len, const int& flag);
	static void err_quit(char *msg);
	static void err_display(char *msg);
	static void errCheckAndErrQuit(const SOCKET& socket, char* msg);
	
	static void errCheckAndErrDisplay(const SOCKET& socket, char* msg);
	static bool IsSocketError(const int& retval, char* msg);
};
