#include "WinAPI.h"
#include "WinAPI.h"
#include "GameNode.h"
#include "GameManager.h"

HINSTANCE g_hInstance;
HWND g_hWnd;
GameManager* _pGame;
POINT g_ptMouse;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{

	g_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);
	g_hWnd = CreateWindow(WINNAME, WINTITLE, WINSTYLE, WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, NULL, (HMENU)NULL, hInstance, NULL);
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(g_hWnd, cmdShow);

	MSG message;

	_pGame = GameManager::GetSingleton();
	if (FAILED(_pGame->Init())) return 0;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			_pGame->Update();
			_pGame->Render();
		}
	}
	_pGame->Release();

	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(g_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pGame->GameProc(hWnd, iMessage, wParam, lParam);
}

