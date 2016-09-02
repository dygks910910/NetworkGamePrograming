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
	HDC m_memDC;
	HBITMAP m_hPreBit;
	RECT m_clientRect;
public:
	CDoubleBuffering();
	~CDoubleBuffering();
public:
	HDC GetmemDC() { return m_memDC; }
	void Initialize(HDC hdc,RECT clientRect);
	template<class obj>
	void WriteToBackBuffer(obj* object);
	/* 
	[2016/09/02 3시35분 
	작성자 : 박요한(dygks910910@daum.net)]
	설명:전면버퍼로 present한후 멤버들을 초기화시켜줘야 한다.
	*/
	void Present(HDC hdc)
	{
		BitBlt(hdc, 0, 0, m_clientRect.right, m_clientRect.bottom,m_memDC, 0, 0, SRCCOPY);
		Initialize(hdc, m_clientRect);
	}
};
//obj상속된것들만 읽을수 있음.
template<class obj>
inline void CDoubleBuffering::WriteToBackBuffer(obj * object)
{
	object->Render(m_memDC);
}
