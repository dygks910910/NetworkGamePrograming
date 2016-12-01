#pragma once

#pragma  comment(lib,"ws2_32")

#include<WinSock2.h>
#include"Vector2.h"
#include<iostream>
#include "Message.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 300

#define GOAL_SIZE 20
#define FPS 15

#define BALL_SIZE 10
#define PLAYER_SPEED 10
#define PLAYER_SIZE 12
#define PLAYER1_POSX WINDOW_WIDTH - PLAYER_SIZE
#define PLAYER1_POSY WINDOW_HEIGHT/2 
#define PLAYER2_POSX 0 + PLAYER_SIZE
#define PLAYER2_POSY WINDOW_HEIGHT/2