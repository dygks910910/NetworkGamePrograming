//
// Win32Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING]  ;					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING] ;			// 기본 창 클래스 이름입니다.

HWND g_hWnd;

CMainGame MainGame;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

 	// TODO: 여기에 코드를 입력합니다.
	CTimer timer;

	MSG msg;
	msg.message = WM_NULL;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//SEND 객체 선언
	CSendAndMessageType sendAndMsgType;
	
	int retval;
	
	//윈속 초기화
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
	
	printf("접속성공 \n");

	MainGame.Initialize();	
	timer.startTimer();
	// 기본 메시지 루프입니다.
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
				
				//send (초당 30번 player 객체 정보를 모두 보냄)
				retval = sendAndMsgType(sock, (char*)&MainGame.GetP_data(), sizeof(MainGame.GetP_data()), 0, e_MSG_TYPE::MSG_PLAYERINFO);
				std::cout << "[TCP 클라이언트]" << retval << "바이트 전송" << std::endl;

				timer.startTimer();
			}

			else {
				// 딜레이를 주는 부분
			}
		}

		
	}

	MainGame.Release();
	closesocket(sock);
	WSACleanup();

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
	RECT rc = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//

/*
2016 / 10 / 30 / 19:31
작성자:박요한(dygks910910@daum.net)
설명:마우스 커서를 감춤.	ShowCursor(false);
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
		// 메뉴 선택을 구문 분석합니다.
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
		// TODO: 여기에 그리기 코드를 추가합니다.
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
