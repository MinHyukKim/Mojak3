#include "stdafx.h"
#include "cCharTestScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//�׽�Ʈ��
#include "cMapObject.h"
#include "cGrid.h"
//Ui ���� �׽�Ʈ
#include "cUiTestScene.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pUi(NULL)
{
	//�׽�Ʈ��
	m_pGrid = NULL;
}

cCharTestScene::~cCharTestScene(void)
{
	this->Reset();
}

HRESULT cCharTestScene::Setup(void)
{

	m_pCamera = g_pObjectManager->GetPlayer()->GetCamera();
	m_pCamera->AddRef();

//	D3DXMATERIAL stMtl;
//	SetMatrial(&stMtl.MatD3D);
//	stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";
//
//	m_pMapTerrain = cMapTerrain::Create();
//	m_pMapTerrain->Setup("./HeightMapData/HeightMap.raw", &stMtl);
//	g_pMapTerrain->RegisterMap("�׽�Ʈ��", "./HeightMapData/HeightMap.raw", "./Texture/steppegrass01_only.dds", &D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	g_pObjectManager->SetTerrain(m_pMapTerrain);
	g_pObjectManager->SetTerrain(g_pMapTerrain->GetMapTerrain("�׽�Ʈ��"));
	m_pMapTerrain = g_pMapTerrain->GetMapTerrain("�׽�Ʈ��");
	m_pMapTerrain->AddRef();

	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
//	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");

	//ui �½�Ʈ
	m_pUi = cUiTestScene::Create();
	m_pUi->Setup();

	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(-2.0f, 0.0f, 5.0f), &FOX_BROWN);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(0.0f, 0.0f, 4.0f), &FOX_GRAY);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(2.0f, 0.0f, 5.0f), &FOX_RED);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_BEAR, &D3DXVECTOR3(0.0f, 0.0f, 7.0f), &BEAR_BLACK);

	//npc�½�Ʈ
	g_pObjectManager->CreateNPC(cObjectManager::NPC_NAO, &D3DXVECTOR3(-1.0f, 0.0f, 1.0f));

	return S_OK;
}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapTerrain);

	//�׽�Ʈ��
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pUi);
}

void cCharTestScene::Update(void)
{
	//�׽�Ʈ��
	if (m_pCamera) m_pCamera->TestController();

	SAFE_UPDATE(m_pUi);
	if (m_pUi->GetMoveingOK())
	{
		if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
		{
			cPlayer* pMonster = nullptr;
			D3DXVECTOR3 vTo, vRay, vDir;
			g_pRay->RayAtWorldSpace(&vRay, &vDir);
			if (g_pObjectManager->GetMonster(&pMonster, &vRay, &vDir))
			{
				g_pObjectManager->GetPlayer()->OrderAttack(pMonster);
			}
			else if (m_pMapTerrain->IsCollision(&vTo, &vRay, &vDir))
			{
				g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_TARGET);
				if (g_pInputManager->IsStayKeyDown(VK_SHIFT))
				{
					g_pObjectManager->GetPlayer()->OrderWalk(&vTo);
				}
				else
				{
					g_pObjectManager->GetPlayer()->OrderMove(&vTo);
				}
			}
		}
	}
	
	if (g_pInputManager->IsOnceKeyDown(VK_SPACE))
	{
		g_pObjectManager->GetPlayer()->OrderIdenChange();
	}
	if (g_pInputManager->IsOnceKeyDown('1'))
	{
		g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_SMASH);
	}
	if (g_pInputManager->IsOnceKeyDown('2'))
	{
		g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_COUNTER);
	}
	if (g_pInputManager->IsOnceKeyDown('3'))
	{
		g_pObjectManager->GetPlayer()->GetTarget()->OrderIdenChange();
	}
	if (g_pInputManager->IsOnceKeyDown('4'))
	{
		g_pObjectManager->GetPlayer()->GetTarget()->OrderAttack(g_pObjectManager->GetPlayer());
	}
	if (g_pInputManager->IsOnceKeyDown('5'))
	{
		g_pObjectManager->GetPlayer()->GetTarget()->SetStateTrue(PATTERN_SMASH);
	}
	if (g_pInputManager->IsOnceKeyDown('6'))
	{
		g_pObjectManager->GetPlayer()->GetTarget()->SetStateTrue(PATTERN_COUNTER);
	}



	//�ʿ�����Ʈ ���̺� �ε� �׽�Ʈ
	if (g_pInputManager->IsOnceKeyDown('0'))
	{
		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "�ʿ�����Ʈ �ε��ϱ�";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "��� ����(*.*)\0*.*\0�� ������Ʈ ����\0*.obj;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetOpenFileName(&OFN) != 0)
			g_pMapObjectManager->LoadCurrentObjectsState(OFN.lpstrFile);
	}


	if (g_pInputManager->IsOnceKeyDown('9'))
	{
		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "���� ��ġ �ε��ϱ�";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "��� ����(*.*)\0*.*\0�� ������Ʈ ����\0*.obj;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetOpenFileName(&OFN) != 0)
			g_pObjectManager->LoadMonsterObjectState(OFN.lpstrFile);
	}

	SAFE_UPDATE(g_pObjectManager);
	cPlayer* pPlayer = g_pObjectManager->GetPlayer();
	float fHeight = pPlayer->GetPosY();
	m_pMapTerrain->GetHeight(&fHeight, pPlayer->GetPosX(), pPlayer->GetPosZ());
	pPlayer->SetPosY(fHeight);

	SAFE_UPDATE(m_pCamera);

}

void cCharTestScene::Render(void)
{
	//�׽�Ʈ��
//	g_pD3DDevice->SetTexture(0, m_pTexture);
//	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	//SAFE_RENDER(m_pMapObject);
	SAFE_RENDER(m_pMapTerrain);

	SAFE_RENDER(m_pGrid);

	SAFE_RENDER(g_pObjectManager);
	SAFE_RENDER(m_pUi);
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

