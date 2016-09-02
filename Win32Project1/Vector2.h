#pragma once
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
