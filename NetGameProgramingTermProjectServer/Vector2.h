#pragma once
#include<iostream>
/* 
[2016/09/02 18시20분 
작성자 : 박요한(dygks910910@daum.net)]
설명:vector2클래스 구현
*/

class CVector2
{
public:
	float x;
	float y;
public:
	CVector2();
	CVector2(float x,float y);
	~CVector2();
	CVector2 operator+(const CVector2& other);
	CVector2 operator-(const CVector2& other);
	CVector2 operator*(const float& other);
	CVector2 normalize();


};
std::ostream& operator<<(std::ostream & os, const CVector2& vec);
CVector2 operator-(const CVector2& v1, const CVector2& v2);
