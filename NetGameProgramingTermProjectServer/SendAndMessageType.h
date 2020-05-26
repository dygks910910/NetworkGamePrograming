#pragma once
#include<WinSock2.h>
#include "Message.h"
class CSendAndMessageType
{
public:
	CSendAndMessageType();
	~CSendAndMessageType();
	const int& operator()(const SOCKET& s,
		char *buff,
		const int& len,
		const int& flag,
		const int& msgType);
	

};

