#include "stdafx.h"
#include "cMainGame.h"

//�� ����Ʈ
#include "cMapToolScene.h"
#include "cUiTestScene.h"
#include "cCharTestScene.h"

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	g_pTexture->Destroy();
	g_pSceneManager->Destroy();
	g_pFontManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
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
	
	//�� �Ŵ���
	g_pSceneManager->AddScene("cMapToolScene", cMapToolScene::Create());
	g_pSceneManager->AddScene("cUiTestScene", cUiTestScene::Create());
	g_pSceneManager->AddScene("cCharTestScene", cCharTestScene::Create());

	//g_pSceneManager->ChangScene("cUiTestScene");
	g_pSceneManager->ChangScene("cCharTestScene");


	//Ÿ�̸�
	g_pTimeManager->Setup();
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	//���Ű� �ʿ��� ��ü ������
	g_pTimeManager->Update();
	g_pSceneManager->Update();
}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//�׸��� �׸���
	g_pSceneManager->Render();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}