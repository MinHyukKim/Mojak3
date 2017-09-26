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
	g_pMapObjectManager->RegisterMapObject("", "farm_appletree_01.x", "farm_appletree_01");
	g_pMapObjectManager->RegisterMapObject("", "farm_level02_se_tree_01.x", "farm_level02_se_tree_01");
	g_pMapObjectManager->RegisterMapObject("", "scene_building_tirchonaill_chiefhouse.x", "scene_building_tirchonaill_chiefhouse");
	g_pMapObjectManager->RegisterMapObject("", "scene_building_tirchonaill_church.x", "scene_building_tirchonaill_church");

	m_pBuild = new cBuilding();
	m_pBuild->Setup();
	m_pBuild->LoadModel("inn.X");
	m_pBuild->SetPosition(&D3DXVECTOR3(-5, 0, -5));

	g_pMapObjectManager->AppendBuilding(m_pBuild);

	m_pBuild = new cBuilding();
	m_pBuild->Setup();
	m_pBuild->LoadModel("inn.X");
	m_pBuild->SetPosition(&D3DXVECTOR3(5, 0, -5));

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
	
	//테스트용 전역변수 필히 삭제
	static bool g_TestToggle = false;


	//L버튼을 누르면 마지막으로 생성된 건물이 클릭한 위치로 이동
	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
	{
		g_TestToggle = false;
		D3DXVECTOR3 vTo, vOrg, vDir;
		g_pRay->RayAtWorldSpace(&vOrg, &vDir);
		if (m_pMapTerrain->IsCollision(&vTo, &vOrg, &vDir))
		{
			//건물위치 테스트용
			g_pMapObjectManager->GetLastMapObject()->SetPosZ(vTo.z);
			g_pMapObjectManager->GetLastMapObject()->SetPosX(vTo.x);
		}
	}
	//마지막으로 생성된 건물의 좌우 방향 변환
	if (g_pInputManager->IsStayKeyDown('J'))
	{
		g_pMapObjectManager->GetLastMapObject()->SetAngleY(g_pTimeManager->GetElapsedTime());

	}

	if (g_pInputManager->IsStayKeyDown('L'))
	{
		g_pMapObjectManager->GetLastMapObject()->SetAngleY(-g_pTimeManager->GetElapsedTime());

	}
	//상하이동
	if (g_pInputManager->IsStayKeyDown('I'))
	{
		//g_pMapObjectManager->GetLastMapObject()->SetPosY(
		//	g_pMapObjectManager->GetLastMapObject()->GetPosY()+ 1.f);
		g_pMapObjectManager->GetLastMapObject()->SetOffsetY(
			g_pMapObjectManager->GetLastMapObject()->GetOffsetY()+g_pTimeManager->GetElapsedTime());
	}

	if (g_pInputManager->IsStayKeyDown('K'))
	{
		g_pMapObjectManager->GetLastMapObject()->SetPosY(
			g_pMapObjectManager->GetLastMapObject()->GetPosY() - g_pTimeManager->GetElapsedTime());
	}

	//static float scaleTest = 1.0f;
	//축소 확대기능
	if (g_pInputManager->IsStayKeyDown('U'))
	{
		g_pMapObjectManager->GetLastMapObject()->SetScale(0.9f);
	}
	if (g_pInputManager->IsStayKeyDown('O'))
	{
		g_pMapObjectManager->GetLastMapObject()->SetScale(1.1f);
	}


	//R버튼을 누르면 해당위치에 건물 생성하고 확정버튼을 누를때까지 모델을 계속 변환
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


	if (g_pInputManager->IsOnceKeyDown(VK_RBUTTON))
	{
		g_pMapObjectManager->PopMapObject();
	}


	if (g_pInputManager->IsStayKeyDown('1'))
	{
		g_TestToggle = true;
		m_pBuild = new cBuilding();
		m_pBuild->Setup();
		m_pBuild->LoadModel("inn.X");
		m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));
		g_pMapObjectManager->AppendBuilding(m_pBuild);


	}

	if (g_pInputManager->IsStayKeyDown('2'))
	{
		g_TestToggle = true;

		m_pBuild = new cBuilding();
		m_pBuild->Setup();
		m_pBuild->LoadModel("scene_building_tirchonaill_church.x");
		m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));
		g_pMapObjectManager->AppendBuilding(m_pBuild);

	}
	//변수가 토글되어있으면 마지막으로 추가된 맵오브젝트가 마우스를 따라온다
	if (g_TestToggle)
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

