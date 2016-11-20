#include "Vector2.h"


CVector2::CVector2() :
	x(0), y(0)
{
}

CVector2::CVector2(float x, float y) :
	x(x), y(y)
{
}


CVector2::~CVector2()
{
}

CVector2 CVector2::operator+(const CVector2& other)
{
	return CVector2(x + other.x, y + other.y);

}

CVector2 CVector2::operator-(const CVector2 & other)
{
	return CVector2(x - other.x, y - other.y);
}

CVector2 CVector2::operator*(const float & other)
{
	return CVector2(x*other,y*other);
}



CVector2 CVector2::normalize()
{
	float temp =  sqrt((x * x) + (y*y));
	return CVector2(x/ temp,y/ temp);
}

std::ostream& operator<<(std::ostream & os, const CVector2& vec)
{
	os << "(" << vec.x << "," << vec.y << ")";
	return os;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

CVector2 operator-(const CVector2& v1, const CVector2& v2)
{
	return v1 - v2;
}
