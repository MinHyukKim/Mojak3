#include "stdafx.h"
#include "cMainGame.h"

//�� ����Ʈ
#include "cMapToolScene.h"
#include "cUiTestScene.h"
#include "cCharTestScene.h"
#include "cChareterCustomScene.h"
#include "cUiCustomizingScene.h"
#include "cLodingScene.h"

cMainGame::cMainGame(void)
{
	
}


cMainGame::~cMainGame(void)
{
	DEBUG_END();
	g_pSceneManager->Destroy();
	g_pObjectManager->Destroy();
	g_pAnimationManager->Destroy();
	g_pFrustum->Destroy();
	g_pTexture->Destroy();
	g_pFontManager->Destroy();
	g_pSkinnedMeshManager->Destroy();

	g_pAutoRelasePool->Destroy();
	g_pDeviceManager->Destroy();
}


void cMainGame::Setup(void)
{
	DEBUG_START("Debug.txt");
	//���� ����
	SetDirectional(0, D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	//���� ����
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	//�� �Ŵ���
	g_pSceneManager->AddScene("cMapToolScene", cMapToolScene::Create());
	g_pSceneManager->AddScene("cUiTestScene", cUiTestScene::Create());
	g_pSceneManager->AddScene("cCharTestScene", cCharTestScene::Create());
	g_pSceneManager->AddScene("cChareterCustomScene", cChareterCustomScene::Create());
	g_pSceneManager->AddScene("cUiCustomizingScene", cUiCustomizingScene::Create());
	g_pSceneManager->AddScene("cLodingScene", cLodingScene::Create());

	g_pSceneManager->ChangeScene("cUiTestScene");


	//Ÿ�̸�
	g_pTimeManager->Setup();
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	// ���Ű� �ʿ��� ��ü ������
	g_pFrustum->Update();					// �ø� ��Ʈ���� �غ�
	g_pTimeManager->Update();
	g_pSceneManager->Update();
}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//�׸��� �׸���
	g_pSceneManager->Render();
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pSceneManager->MsgProc(hWnd, message, wParam, lParam);
}

