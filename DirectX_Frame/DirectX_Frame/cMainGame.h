#pragma once

class cMainGame
{
private:
	LPDIRECT3D9 mpD3D;
	LPDIRECT3DDEVICE9 mpD3DD;

public:

	void Setup();
	void Update();
	void Render();

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	cMainGame();
	~cMainGame();
};

