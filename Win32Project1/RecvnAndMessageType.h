#pragma once
#include "stdafx.h"
#include "enum.h"
#include "CMyFunc.h"
#include "Message.h"
#include <WinSock2.h>

class CRecvnAndMessageType
{
public:
	CRecvnAndMessageType();
	~CRecvnAndMessageType();
	const int& operator()(const SOCKET& s, char *buff, const int& len, const int& flag);
};

