#pragma once

#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>

#define WINNAME (TEXT("APIWindow"))
#define WINTITLE (TEXT("APIWindow"))
#define WINSTARTX 20
#define WINSTARTY 10
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE (WS_CAPTION | WS_SYSMENU)

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release; (p) = NULL;}}

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern POINT g_ptMouse;

void setWindowSize(int, int, int, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


