#pragma once

extern HWND g_hWnd;
/* 
[2016/09/03 18시28분 
작성자 : 박요한(dygks910910@daum.net)]
변경내용:해상도 1024x400으로 변경 게임에 더욱 적합한것같음.
*/
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 300

#define PLAYER_SPEED 10
#define PLAYER_SIZE 10
#define PLAYER1_POSX WINDOW_WIDTH - PLAYER_SIZE
#define PLAYER1_POSY WINDOW_HEIGHT/2 
#define PLAYER2_POSX 0 + PLAYER_SIZE
#define PLAYER2_POSY WINDOW_HEIGHT/2
#define FPS 30
#define SERVERADDR "192.168.2.100"
#define PORT 9000