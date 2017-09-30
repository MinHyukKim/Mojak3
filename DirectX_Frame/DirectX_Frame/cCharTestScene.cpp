#include "stdafx.h"
#include "cCharTestScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"
//Ui 연동 테스트
#include "cUiTestScene.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pUi(NULL)
{
	//테스트용
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
//	g_pMapTerrain->RegisterMap("테스트용", "./HeightMapData/HeightMap.raw", "./Texture/steppegrass01_only.dds", &D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	g_pObjectManager->SetTerrain(m_pMapTerrain);
	g_pObjectManager->SetTerrain(g_pMapTerrain->GetMapTerrain("테스트용"));
	m_pMapTerrain = g_pMapTerrain->GetMapTerrain("테스트용");
	m_pMapTerrain->AddRef();

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
//	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");

	//ui 태스트
	m_pUi = cUiTestScene::Create();
	m_pUi->Setup();

	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(-2.0f, 0.0f, 5.0f), &MONSTERCOLOR_BROWN);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(0.0f, 0.0f, 5.0f), &MONSTERCOLOR_GRAY);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(2.0f, 0.0f, 5.0f), &MONSTERCOLOR_RED);

	return S_OK;
}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapTerrain);

	//테스트용
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pUi);
}

void cCharTestScene::Update(void)
{
	//테스트용
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
		g_pObjectManager->GetPlayer()->GetTarget()->SetStateTrue(PATTERN_COUNTER);
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
	//테스트용
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

