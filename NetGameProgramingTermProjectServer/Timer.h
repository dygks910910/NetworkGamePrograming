#pragma once
#include<chrono>
#include<iostream>

class CTimer
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
public:
	CTimer::CTimer();
	int restTime;//남은시간(countDown전용).

	~CTimer();

	typedef std::chrono::duration<std::chrono::milliseconds> milsec;

	double getElapsedTime(); //지금까지 흐른 시간 리턴millisec
	int getElapsedTimeSec();
	void startTimer();
	const int& countDown(const int& countSec);
};