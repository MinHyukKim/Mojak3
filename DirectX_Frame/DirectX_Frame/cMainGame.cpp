#include "stdafx.h"
#include "cMainGame.h"

//씬 리스트
#include "cMapToolScene.h"

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	g_pSceneManager->Destroy();
	g_pAutoRelasePool->Destroy();
	g_pDeviceManager->Destroy();
}


void cMainGame::Setup(void)
{
	g_pSceneManager->AddScene("cMapToolScene", cMapToolScene::Create());
	g_pSceneManager->ChangScene("cMapToolScene");
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	//제거가 필요한 객체 릴리즈
	g_pSceneManager->Update();

}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//그림을 그린다
	g_pSceneManager->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}