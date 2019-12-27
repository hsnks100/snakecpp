#ifndef WINMAIN_H_
#define WINMAIN_H_
#include "GlobalHeader.h"

#define NOSTART		0
#define START		1
#define FOODEAT		2
#define GAMEOVER	3

extern HDC GlobalDC;
extern int GAMEMODE;
extern HWND GlobalWnd;
extern BOOL KeyState[41];
extern CSnake* SnakeControl;
//CALLBACK ÇÔ¼ö.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#endif