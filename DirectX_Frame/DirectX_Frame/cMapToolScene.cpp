#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"
#include "cBuilding.h"
#include "cSkybox.h"
#include "cFont.h"

cMapToolScene::cMapToolScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pBuild(NULL)
	, m_pTexture(NULL)
	, m_pGrid(NULL)
	, m_pSkybox(nullptr)
	, currentMode(E_MODE::M_NONE)
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
	g_pSoundManager->Play("mapToolBGM");
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();
	m_pCamera->SetCameraType(cCamera::E_AIRCRAFT);
	m_pCamera->UpdateProjection(0.1f);


	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = g_pMapTerrain->GetMapTerrain("테스트용");
	SAFE_ADDREF(m_pMapTerrain);
	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
//	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");
	


	//m_pBuild = new cBuilding();
	//m_pBuild->Setup();
	//m_pBuild->LoadModel("inn.X);
	//m_pBuild->SetPosition(&D3DXVECTOR3(-5, 0, -5));
	//m_pBuild = g_pMapObjectManager->GetMapObject(m_vecObjectList[0]);
	//m_pBuild->SetPosition(&D3DXVECTOR3(0, 0, 0));
	//g_pMapObjectManager->AppendBuilding(m_pBuild);

	//m_pBuild = g_pMapObjectManager->GetMapObject(m_vecObjectList[1]);
	//m_pBuild->SetPosition(&D3DXVECTOR3(5, 0, -5));
	//g_pMapObjectManager->AppendBuilding(m_pBuild);

	//g_pMapObjectManager->AppendBuilding(g_pMapObjectManager->GetMapObject("church"));

	m_pSkybox = cSkybox::Create();
	m_pSkybox->Setup(".\\skyboxMap\\vanilla_sky_frost_up.jpg", ".\\skyboxMap\\vanilla_sky_frost_dn.jpg",
		".\\skyboxMap\\vanilla_sky_frost_lf.jpg", ".\\skyboxMap\\vanilla_sky_frost_rt.jpg",
		".\\skyboxMap\\vanilla_sky_frost_ft.jpg", ".\\skyboxMap\\vanilla_sky_frost_bk.jpg");
	g_pObjectManager->SetTerrain(m_pMapTerrain);
	g_pMapObjectManager->SetMapTerrain(m_pMapTerrain);
	m_pText = cFont::Create();
	m_pText->Setup();
	return S_OK;
}

void cMapToolScene::Reset(void)
{
	g_pSoundManager->Stop("mapToolBGM");

	SAFE_RELEASE(m_pCamera);
	//테스트용
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pSkybox);
	DeselectObjects();

	g_pObjectManager->DestroyMonster();
	g_pObjectManager->DestroyNPC();

	g_pMapObjectManager->DestroyBuilding();
	SAFE_RELEASE(m_pText);

	//g_pMapObjectManager->Destroy();


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
	//static bool g_TestToggle = false;

	if (m_pMapTerrain)
	{
		g_pMapObjectManager->Update(m_pMapTerrain);
		g_pObjectManager->SelectUpdate(m_pMapTerrain);
		m_pMapTerrain->Update();
	}

	//L버튼을 누르면 마지막으로 생성된 건물이 클릭한 위치로 이동
	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
	{
		if (currentMode == E_MODE::M_BUILD)
			g_pMapObjectManager->SetupBuilding();
		else if (currentMode == E_MODE::M_MOB)
		{
			//if(g_pObjectManager->GetMonster())
			g_pObjectManager->SetupMonster();
		}
	}
//
//	//마지막으로 생성된 건물의 좌우 방향 변환
	if (g_pInputManager->IsStayKeyDown('J'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->SetAngleY(g_pTimeManager->GetElapsedTime());

	}

	if (g_pInputManager->IsStayKeyDown('L'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->SetAngleY(-g_pTimeManager->GetElapsedTime());

	}
	//상하이동
	if (g_pInputManager->IsStayKeyDown('I'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->SetOffsetY(
			g_pMapObjectManager->GetSelectObject()->GetOffsetY()+0.1f);
	}

	if (g_pInputManager->IsStayKeyDown('K'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->SetOffsetY(
			g_pMapObjectManager->GetSelectObject()->GetOffsetY()-0.1f);
	}
//
//	//static float scaleTest = 1.0f;
	//축소 확대기능
	if (g_pInputManager->IsStayKeyDown('U'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->OffsetScale(-0.01f);
	}
	if (g_pInputManager->IsStayKeyDown('O'))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->GetSelectObject()->OffsetScale(0.01f);
	}

	if (g_pInputManager->IsOnceKeyDown(VK_RBUTTON))
	{
		if (g_pMapObjectManager->GetSelectObject() == NULL) return;
		g_pMapObjectManager->PopMapObject();
	}

	//맵오브젝트 배치
	if (g_pInputManager->IsOnceKeyDown('1'))
	{
		if (currentMode != E_MODE::M_BUILD)
		{
			//이전에 선택된 부분이 있으면 해제하고 모드 변경
			DeselectObjects();
			
			//빌드 모드로 변경
			currentMode = E_MODE::M_BUILD;
		}
		g_pMapObjectManager->getMapObjectRotation();
		g_pMapObjectManager->SetCursorIncrease();
	}
	//몹오브젝트 배치
	if (g_pInputManager->IsOnceKeyDown('2'))
	{
		if (currentMode != E_MODE::M_MOB)
		{
			//이전에 선택된 부분이 있으면 해제하고 모드 변경
			DeselectObjects();
			//몹선택 모드로 변경
			currentMode = E_MODE::M_MOB;
			g_pObjectManager->GetMonsterRotation();
		}
		else
		{
			g_pObjectManager->SetCursorIncrease();
			g_pObjectManager->GetMonsterRotation();
		}
	}


	//맵오브젝트 세이브 로드 테스트
	if (g_pInputManager->IsOnceKeyDown('5'))
	{
		DeselectObjects();

		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "맵오브젝트 로드하기";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "모든 파일(*.*)\0*.*\0맵 오브젝트 파일\0*.obj;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetOpenFileName(&OFN) != 0)
			g_pMapObjectManager->LoadCurrentObjectsState(OFN.lpstrFile);
	}


	if (g_pInputManager->IsOnceKeyDown('6'))
	{
		DeselectObjects();

		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "맵오브젝트 저장하기";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "모든 파일(*.*)\0*.*\0맵 오브젝트 파일\0*.obj;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		OFN.Flags = OFN_OVERWRITEPROMPT;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetSaveFileName(&OFN) != 0) 
			g_pMapObjectManager->SaveCurrentObjectsState(OFN.lpstrFile);
	}


	//몹 세이브 로드 테스트
	if (g_pInputManager->IsOnceKeyDown('7'))
	{
		DeselectObjects();

		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "적 배치 저장하기";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "모든 파일(*.*)\0*.*\0적 배치 파일\0*.enm;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		OFN.Flags = OFN_OVERWRITEPROMPT;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetSaveFileName(&OFN) != 0)
			g_pObjectManager->SaveMonsterObjectState(OFN.lpstrFile);
	}

	if (g_pInputManager->IsOnceKeyDown('8'))
	{
		DeselectObjects();
		g_pObjectManager->LoadMonsterObjectState("test.enm");
	}


	if (g_pInputManager->IsStayKeyDown(VK_ESCAPE))
	{
		DeselectObjects();
	}
	if (m_pSkybox) m_pSkybox->Update(*m_pCamera->GetPosition());


}
     
void cMapToolScene::Render(void)
{
	//테스트용
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	SAFE_RENDER(m_pSkybox);
	SAFE_RENDER(m_pMapTerrain);
	SAFE_RENDER(m_pGrid);



	//SAFE_RENDER(m_pBuild);
	g_pMapObjectManager->Render();
	g_pObjectManager->monsterRender();

	switch (currentMode)
	{
	case E_MODE::M_NONE:
	{
		m_pText->SetText("NONE");
		break;
	}
	case E_MODE::M_BUILD:
	{
		m_pText->SetText("빌딩 모드");
		break;
	}
	case E_MODE::M_MOB:
	{
		m_pText->SetText("몹 배치 모드");
		break;
	}
	}
	m_pText->SetColor(D3DCOLOR_XRGB(255,0,0));
	m_pText->SetRectangle(10, 10, 200, 30);
	m_pText->Render();
}


cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

void cMapToolScene::DeselectObjects()
{
	if (currentMode == E_MODE::M_BUILD)
		g_pMapObjectManager->ResetBuilding();
	else if (currentMode == E_MODE::M_MOB)
	{
		g_pObjectManager->ResetMobSelect();
	}
	currentMode = E_MODE::M_NONE;

}

