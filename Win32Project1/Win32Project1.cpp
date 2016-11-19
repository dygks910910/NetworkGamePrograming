//
// Win32Project1.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#include <windows.h>
#pragma comment(lib, "Winmm.lib")

#include "stdafx.h"
#include "Win32Project1.h"

#include "MyHeader.h"
#include "MainGame.h"

#include <WinSock2.h>
#include "CMyFunc.h"
#include "SendAndMessageType.h"
#include "RecvnAndMessageType.h"

#define MAX_LOADSTRING 100

#define LOCAL_IP "112.148.36.243"
#define SERVER_IP "220.120.220.127"
#define SERVER_PORT 9000

SOCKADDR_IN InitSockAddrIPv4(const char* ipAddr, const int& port);

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING]  ;					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING] ;			// �⺻ â Ŭ���� �̸��Դϴ�.

HWND g_hWnd;

CMainGame MainGame;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	CTimer timer;

	MSG msg;
	msg.message = WM_NULL;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//SEND ��ü ����
	CSendAndMessageType sendAndMsgType;
	
	int retval;
	
	//���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		CMyFunc::err_quit("WSAStartup()");
		return 1;
	}

	//socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	CMyFunc::errCheckAndErrDisplay(sock, "socket()");

	//connect()
	SOCKADDR_IN serverAddr = InitSockAddrIPv4(SERVER_IP, SERVER_PORT);
	retval = connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	CMyFunc::IsSocketError(retval, "connect()");
	
	printf("���Ӽ��� \n");

	MainGame.Initialize();	
	timer.startTimer();
	// �⺻ �޽��� �����Դϴ�.
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (timer.getElapsedTime() >= 1000 / FPS)
			{
				MainGame.Progress();
				MainGame.Render();
				MainGame.MouseInputProcessing(msg);
				MainGame.KeyboardInputProcessing(msg);
				
				//send (�ʴ� 30�� player ��ü ������ ��� ����)
				retval = sendAndMsgType(sock, (char*)&MainGame.GetP_data(), sizeof(MainGame.GetP_data()), 0, e_MSG_TYPE::MSG_PLAYERINFO);
				std::cout << "[TCP Ŭ���̾�Ʈ]" << retval << "����Ʈ ����" << std::endl;

				timer.startTimer();
			}

			else {
				// �����̸� �ִ� �κ�
			}
		}

		
	}

	MainGame.Release();
	closesocket(sock);
	WSACleanup();

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
	RECT rc = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      300, 50, rc.right - rc.left, rc.bottom - rc.top, 
	  NULL, NULL, hInstance, NULL);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

/*
2016 / 10 / 30 / 19:31
�ۼ���:�ڿ���(dygks910910@daum.net)
����:���콺 Ŀ���� ����.	ShowCursor(false);
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	ShowCursor(false);
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

SOCKADDR_IN InitSockAddrIPv4(const char* ServerIP, const int& ServerPort)
{
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ServerIP);
	serverAddr.sin_port = htons(ServerPort);

	return serverAddr;
}
