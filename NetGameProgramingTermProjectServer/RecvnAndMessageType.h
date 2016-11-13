#pragma once
#include "stdafx.h"
#include"enum.h"

class CRecvnAndMessageType
{
public:
	CRecvnAndMessageType();
	~CRecvnAndMessageType();
	const int& operator()(const SOCKET& s,char *buff,const int& len,const int& flag);
};

