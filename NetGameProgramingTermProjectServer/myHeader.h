#pragma once

#pragma  comment(lib,"ws2_32")

#include<WinSock2.h>
#include"Vector2.h"
#include<iostream>
#include "Message.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

#define COUNTDOWN_TIME 180
#define GOAL_SIZE 50
#define FPS 30
#define BALL_SIZE 10
#define BALL_SPEED 10
#define PLAYER1_POSX WINDOW_WIDTH - PLAYER_SIZE
#define PLAYER1_POSY WINDOW_HEIGHT/2 
#define PLAYER2_POSX 0 + PLAYER_SIZE
#define PLAYER2_POSY WINDOW_HEIGHT/2
#define PLAYER_SIZE 15
