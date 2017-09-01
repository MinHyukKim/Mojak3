#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	: mpD3D(NULL)
	, mpD3DD(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_RELEASE(mpD3D);
	SAFE_RELEASE(mpD3DD);
}


void cMainGame::Setup()
{
	mpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 stcaps;
	int nVertex;

	mpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stcaps);

	if (stcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertex = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertex = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3Dpp;
	ZeroMemory(&stD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
	stD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3Dpp.Windowed = TRUE;
	stD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3Dpp.EnableAutoDepthStencil = TRUE;
	stD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;

	mpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd,
		nVertex,
		&stD3Dpp,
		&mpD3DD);

}

void cMainGame::Update()
{
}

void cMainGame::Render()
{
	mpD3DD->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	mpD3DD->BeginScene();
	mpD3DD->EndScene();
	mpD3DD->Present(NULL, NULL, NULL, NULL);
}