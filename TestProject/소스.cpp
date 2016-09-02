#include<iostream>
#include"Vector2.h"

using namespace std;

void main()
{
	CVector2 v1(1, 1);
	CVector2 v2(2, 2);
	CVector2 v3(3, 3);
	CVector2 v4(4, 4);

	cout << v1 + v2 << endl;
	cout << v1 * 3 << endl;
	cout << v3 - v1 << endl;
	cout << (v3 - v1).normalize() << endl;

}