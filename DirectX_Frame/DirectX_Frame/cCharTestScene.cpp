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

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");

	//ui 태스트
	m_pUi = cUiTestScene::Create();
	m_pUi->Setup();

	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX01, &D3DXVECTOR3(0.0f, 0.0f, 5.0f));

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

	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON) && m_pUi->GetMoveingOK() == true)
	{
		D3DXVECTOR3 vTo, vOrg, vDir;
		g_pRay->RayAtWorldSpace(&vOrg, &vDir);
		if (m_pMapTerrain->IsCollision(&vTo, &vOrg, &vDir))
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
	//테스트용
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
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

