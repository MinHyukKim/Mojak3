#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"
#include "cBuilding.h"

cMapToolScene::cMapToolScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pBuild(NULL)
	, m_pTexture(NULL)
	, m_pGrid(NULL)
{
	//테스트용
	//m_pMapObject = NULL;
}

cMapToolScene::~cMapToolScene(void)
{
	this->Reset();
}

HRESULT cMapToolScene::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();
	m_pCamera->SetCameraType(cCamera::E_LANDOBJECT);
	

	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = cMapTerrain::Create();
	m_pMapTerrain->Setup("./HeightMapData/HeightMap.raw", &m_stMtl);

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");
	
	//건물 등록
	g_pMapObjectManager->RegisterMapObject("", "scene_building_tirchonaill_church.x", "church");
	g_pMapObjectManager->RegisterMapObject("", "inn.x", "inn");

	m_pBuild = new cBuilding();
	m_pBuild->Setup();
	m_pBuild->LoadModel("inn.X");
	m_pBuild->SetPosition(&D3DXVECTOR3(-5, 0, -5));

	g_pMapObjectManager->AppendBuilding(m_pBuild);

	m_pBuild = new cBuilding();
	m_pBuild->Setup();
	m_pBuild->LoadModel("inn.X");
	m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));

	g_pMapObjectManager->AppendBuilding(m_pBuild);
	g_pMapObjectManager->AppendBuilding(g_pMapObjectManager->GetMapObject("church"));

	return S_OK;
}

void cMapToolScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//테스트용
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pGrid);
	//if (m_pBuild) m_pBuild->Destroy();
	//SAFE_DELETE(m_pBuild);
	g_pMapObjectManager->Destroy();


}

void cMapToolScene::Update(void)
{
	m_pCamera->Update();
	m_pCamera->TestController();
	//건물 바닥 높이 결정
	//float test_build_height = m_pBuild->GetPosY();
	//m_pMapTerrain->GetHeight(&test_build_height, m_pBuild->GetPosX(), m_pBuild->GetPosZ());
	//m_pBuild->SetPosY(test_build_height);

	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
	{
		D3DXVECTOR3 vTo, vOrg, vDir;
		g_pRay->RayAtWorldSpace(&vOrg, &vDir);
		if (m_pMapTerrain->IsCollision(&vTo, &vOrg, &vDir))
		{
			//건물위치 테스트용
			g_pMapObjectManager->GetLastMapObject()->SetPosZ(vTo.z);
			g_pMapObjectManager->GetLastMapObject()->SetPosX(vTo.x);
		}
	}
	
	if (g_pInputManager->IsStayKeyDown(VK_RBUTTON))
	{
		g_pMapObjectManager->GetLastMapObject()->SetAngleY(g_pTimeManager->GetElapsedTime());

	}

	if (g_pInputManager->IsStayKeyDown('1'))
	{
		m_pBuild = new cBuilding();
		m_pBuild->Setup();
		m_pBuild->LoadModel("inn.X");
		m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));
		g_pMapObjectManager->AppendBuilding(m_pBuild);

	}

	if (g_pInputManager->IsStayKeyDown('2'))
	{
		m_pBuild = new cBuilding();
		m_pBuild->Setup();
		m_pBuild->LoadModel("scene_building_tirchonaill_church.x");
		m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));
		g_pMapObjectManager->AppendBuilding(m_pBuild);

	}

	g_pMapObjectManager->Update(m_pMapTerrain);

}
     
void cMapToolScene::Render(void)
{
	//테스트용
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	SAFE_RENDER(m_pMapTerrain);
	SAFE_RENDER(m_pGrid);

	//SAFE_RENDER(m_pBuild);
	g_pMapObjectManager->Render();

}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

