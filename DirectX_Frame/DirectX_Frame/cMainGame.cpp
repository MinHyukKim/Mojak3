#include "stdafx.h"
#include "cMainGame.h"

//�� ����Ʈ
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
	//���� ����
	SetDirectional(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pSceneManager->AddScene("cMapToolScene", cMapToolScene::Create());
	g_pSceneManager->ChangScene("cMapToolScene");
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	//���Ű� �ʿ��� ��ü ������
	g_pSceneManager->Update();
}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//�׸��� �׸���
	g_pSceneManager->Render();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}