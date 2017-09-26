#include "stdafx.h"
#include "cCharTestScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//�׽�Ʈ��
#include "cMapObject.h"
#include "cGrid.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
{
	//�׽�Ʈ��
	//m_pMapObject = NULL;
	m_pTexture = NULL;
	m_pGrid = NULL;
}

cCharTestScene::~cCharTestScene(void)
{
	this->Reset();
}

HRESULT cCharTestScene::Setup(void)
{
	g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetMoveSpeed(2.0f);

	m_pCamera = g_pObjectManager->GetPlayer()->GetCamera();
	m_pCamera->AddRef();

	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = cMapTerrain::Create();
	m_pMapTerrain->Setup("./HeightMapData/HeightMap.raw", &m_stMtl);
	g_pObjectManager->SetTerrain(m_pMapTerrain);

	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");

	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX01, &D3DXVECTOR3(0.0f, 0.0f, 5.0f));

	return S_OK;
}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapTerrain);

	//�׽�Ʈ��
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pGrid);
}

void cCharTestScene::Update(void)
{
	//�׽�Ʈ��
	if (m_pCamera) m_pCamera->TestController();

	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
	{
		D3DXVECTOR3 vTo, vRay, vDir;
		g_pRay->RayAtWorldSpace(&vRay, &vDir);
		if (m_pMapTerrain->IsCollision(&vTo, &vRay, &vDir))
		{
			g_pObjectManager->GetPlayer()->MoveToPlayer(&vTo, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMoveSpeed());
			g_pObjectManager->GetPlayer()->SetPatternState(cPlayer::PATTERN_RUN_FRIENDLY);
		}
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
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	//SAFE_RENDER(m_pMapObject);
	SAFE_RENDER(m_pMapTerrain);

	SAFE_RENDER(m_pGrid);

	SAFE_RENDER(g_pObjectManager);
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

