#pragma once
/* 
[2016/09/02 3시35분 
작성자 : 박요한(dygks910910@daum.net)]
변경내용:더블버퍼링
삭제내용:
*/
class CDoubleBuffering
{
private:
	HBITMAP hMyBitmap;
	RECT m_clientRect;
	HBITMAP hOldBitmap;
	HDC backMemDC, MemDC;
public:
	CDoubleBuffering();
	~CDoubleBuffering();
public:
	HDC GetmemDC() { return backMemDC; }
	void Initialize(HDC hdc,RECT clientRect);
	template<class obj>
	void WriteToBackBuffer(obj* object);
	/* 
	[2016/09/02 3시35분 
	작성자 : 박요한(dygks910910@daum.net)]
	설명:전면버퍼로 present한후 멤버들을 초기화시켜줘야 한다.
	*/
	void Present(HDC hdc);
	void Release();
};
//obj상속된것들만 읽을수 있음.
template<class obj>
inline void CDoubleBuffering::WriteToBackBuffer(obj * pBbject)
{
	pBbject->Render(backMemDC);
}
