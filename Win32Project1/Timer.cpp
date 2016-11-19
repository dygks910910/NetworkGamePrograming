#include "Timer.h"



CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

/*
2016 / 11 / 19 / 22:26
작성자:박요한(dygks910910@daum.net)
설명:시작시간기록하고 time_point를 반환.
*/

double CTimer::getElapsedTime()
{
	std::chrono::high_resolution_clock::time_point nowtime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(nowtime - startTime);
	return mill.count();
}

void CTimer::startTimer()
{
	startTime = std::chrono::high_resolution_clock::now();
}
