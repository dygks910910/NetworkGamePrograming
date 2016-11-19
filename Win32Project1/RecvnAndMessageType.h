#pragma once

#include <WinSock2.h>
#include "stdafx.h"
#include "Message.h"
#include "enum.h"
#include "CMyFunc.h"

class CRecvnAndMessageType
{
public:
	CRecvnAndMessageType();
	~CRecvnAndMessageType();
	const int& operator()(const SOCKET& s, char *buff, const int& len, const int& flag);
};

