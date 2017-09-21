#include "stdafx.h"
#include "cCharTestScene.h"
#include "cSkinnedMesh.h"
#include "crtCtl.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
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
	cPlayer* pPlater = g_pObjectManager->GetPlayer();
	pPlater->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_기본02"));
	pPlater->RegisterAnimation(cPlayer::ANIMATION_WALK_PEACEFUL, g_pAnimationManager->GetAnimation("여성_걷기01"));
	pPlater->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_걷기02"));
	pPlater->RegisterAnimation(cPlayer::ANIMATION_RUN_PEACEFUL, g_pAnimationManager->GetAnimation("여성_달리기01"));
	pPlater->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_달리기02"));

	m_pCamera = g_pObjectManager->GetPlayer()->GetCamera();
	m_pCamera->AddRef();

	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = cMapTerrain::Create();
	m_pMapTerrain->Setup("./HeightMapData/HeightMap.raw", &m_stMtl);

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");

	return S_OK;
}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//테스트용
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pGrid);
}

void cCharTestScene::Update(void)
{
	//테스트용
	if (m_pCamera)
	{
		m_pCamera->TestController();
	}

	if (m_pMapTerrain)
	{
		if (g_pObjectManager->GetPlayer())
		{
			g_pObjectManager->GetPlayer()->Update();
			if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR3 vTo;
				D3DXVECTOR3 vOrg;
				D3DXVECTOR3 vDir;
				g_pRay->RayAtWorldSpace(&vOrg, &vDir);
				if (m_pMapTerrain->IsCollision(&vTo, &vOrg, &vDir))
				{
					g_pObjectManager->GetPlayer()->MoveToPlayer(&vTo, 1.0f);
					g_pObjectManager->GetPlayer()->SetPatternState(cPlayer::PATTERN_RUN_PEACEFUL);
				}
			}
			else
			{
				cPlayer* pPlayer = g_pObjectManager->GetPlayer();
				float fHeight = pPlayer->GetPosY();
				m_pMapTerrain->GetHeight(&fHeight, pPlayer->GetPosX(), pPlayer->GetPosZ());
				pPlayer->SetPosY(fHeight);
			}
		}
	}


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
	SAFE_RENDER(g_pObjectManager->GetPlayer());
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

