#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	g_pDeviceManager->Destroy();

}


void cMainGame::Setup(void)
{

}

void cMainGame::Update(void)
{
}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//그림을 그린다


	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}