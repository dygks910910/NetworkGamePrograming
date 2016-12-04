#pragma once
/* 
[2016/09/02 3��35�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
���泻��:������۸�
��������:
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
	[2016/09/02 3��35�� 
	�ۼ��� : �ڿ���(dygks910910@daum.net)]
	����:������۷� present���� ������� �ʱ�ȭ������� �Ѵ�.
	*/
	void Present(HDC hdc);
	void Release();
};
//obj��ӵȰ͵鸸 ������ ����.
template<class obj>
inline void CDoubleBuffering::WriteToBackBuffer(obj * pBbject)
{
	pBbject->Render(backMemDC);
}
