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

CVector2 CVector2::operator*(const float & other)
{
	return CVector2(x*other, y*other);
}




std::ostream& operator<<(std::ostream & os, const CVector2& vec)
{
	os << "(" << vec.x << "," << vec.y << ")";
	return os;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

CVector2 operator-(const CVector2& v1, const CVector2& v2)
{
	return CVector2(v1.x - v2.x, v1.y - v2.y);

}

/*
2016 / 12 / 4 / 2:35
작성자:박요한(dygks910910@daum.net)
설명:선분ab의 거리를 구해줌.
*/
float distanceVector(const CVector2& a, const CVector2& b)
{
	return sqrt(((b.x-a.x)*(b.x - a.x) ) +((b.y-a.y) *(b.y - a.y)));
}


CVector2 normalize(const CVector2& vec)
{
	float temp = sqrt((vec.x * vec.x) + (vec.y*vec.y));
	return CVector2(vec.x / temp, vec.y / temp);
}

bool operator==(const CVector2& v1, const CVector2& v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
	{
		return true;
	}
	return false;
}
