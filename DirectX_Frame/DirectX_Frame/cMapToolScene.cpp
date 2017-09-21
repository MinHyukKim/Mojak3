#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"

cMapToolScene::cMapToolScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
{
	//테스트용
	//m_pMapObject = NULL;
	m_pTexture = NULL;
	m_pGrid = NULL;
}

cMapToolScene::~cMapToolScene(void)
{
	this->Reset();
}

HRESULT cMapToolScene::Setup(void)
{
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

void cMapToolScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//테스트용
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pGrid);
}

void cMapToolScene::Update(void)
{
	SAFE_UPDATE(g_pObjectManager->GetPlayer());
	
	//테스트용
	if (m_pCamera)
	{
		m_pCamera->TestController();
	}
	if (m_pMapTerrain)
	{
		if (g_pObjectManager->GetPlayer())
		{
			if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR3 vPos;
				D3DXVECTOR3 vOrg;
				D3DXVECTOR3 vDir;
				g_pRay->RayAtWorldSpace(&vOrg, &vDir);
				if (m_pMapTerrain->IsCollision(&vPos, &vOrg, &vDir))
				{
					g_pObjectManager->GetPlayer()->SetPosition(&vPos);
				}
			}
			cPlayer* pPlayer = g_pObjectManager->GetPlayer();
			float fHeight = pPlayer->GetPosY();
			m_pMapTerrain->GetHeight(&fHeight, pPlayer->GetPosX(), pPlayer->GetPosZ());
			pPlayer->SetPosY(fHeight);
		}
	}
	SAFE_UPDATE(m_pCamera);
}

void cMapToolScene::Render(void)
{
	//테스트용
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	//SAFE_RENDER(m_pMapObject);
	SAFE_RENDER(m_pMapTerrain);

	SAFE_RENDER(m_pGrid);
	SAFE_RENDER(g_pObjectManager->GetPlayer());
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

