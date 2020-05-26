#pragma once
#include<chrono>
#include<iostream>

class CTimer
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
public:
	CTimer::CTimer();
	int restTime;//�����ð�(countDown����).

	~CTimer();

	typedef std::chrono::duration<std::chrono::milliseconds> milsec;

	double getElapsedTime(); //���ݱ��� �帥 �ð� ����millisec
	int getElapsedTimeSec();
	void startTimer();
	const int& countDown(const int& countSec);
};