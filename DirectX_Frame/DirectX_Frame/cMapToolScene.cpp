#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

//�׽�Ʈ��
#include "cMapObject.h"
#include "cGrid.h"
#include "cBuilding.h"
#include "cSkybox.h"

cMapToolScene::cMapToolScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pBuild(NULL)
	, m_pTexture(NULL)
	, m_pGrid(NULL)
	, m_pSkybox(nullptr)
	, currentMode(E_MODE::M_BUILD)
{
	//�׽�Ʈ��
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
	m_pCamera->SetCameraType(cCamera::E_AIRCRAFT);
	m_pCamera->UpdateProjection(0.1f);


	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = g_pMapTerrain->GetMapTerrain("�׽�Ʈ��");
	SAFE_ADDREF(m_pMapTerrain);
	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();
//	m_pTexture = g_pTexture->GetTexture("./HeightMapData/terrain.jpg");
	
	m_vecObjectList.push_back("scene_building_tirchonaill_chiefhouse.x");
	m_vecObjectList.push_back("inn.x");
	m_vecObjectList.push_back("farm_appletree_01.x");
	m_vecObjectList.push_back("farm_level02_se_tree_01.x");
	m_vecObjectList.push_back("scene_building_tirchonaill_church.x");
	m_vecObjectList.push_back("smooth_appleTree.x");
	
	//�ǹ� ���
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[0], m_vecObjectList[0]);
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[1], m_vecObjectList[1]);
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[2], m_vecObjectList[2]);
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[3], m_vecObjectList[3]);
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[4], m_vecObjectList[4]);
	g_pMapObjectManager->RegisterMapObject("", m_vecObjectList[5], m_vecObjectList[5]);

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
	return S_OK;
}

void cMapToolScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//�׽�Ʈ��
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pSkybox);

	//g_pMapObjectManager->Destroy();


}

void cMapToolScene::Update(void)
{
	m_pCamera->Update();
	m_pCamera->TestController();
	//�ǹ� �ٴ� ���� ����
	//float test_build_height = m_pBuild->GetPosY();
	//m_pMapTerrain->GetHeight(&test_build_height, m_pBuild->GetPosX(), m_pBuild->GetPosZ());
	//m_pBuild->SetPosY(test_build_height);
	
	if (m_pSkybox) m_pSkybox->Update(*m_pCamera->GetPosition());

	//�׽�Ʈ�� �������� ���� ����
	//static bool g_TestToggle = false;

	if (m_pMapTerrain)
	{
		g_pMapObjectManager->Update(m_pMapTerrain);
		g_pObjectManager->SelectUpdate(m_pMapTerrain);
		m_pMapTerrain->Update();
	}

	//L��ư�� ������ ���������� ������ �ǹ��� Ŭ���� ��ġ�� �̵�
	if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
	{
		if (currentMode == E_MODE::M_BUILD)
			g_pMapObjectManager->SetupBuilding();
		else if (currentMode == E_MODE::M_MOB)
		{
			g_pObjectManager->SetupMonster();
		}
	}
//
//	//���������� ������ �ǹ��� �¿� ���� ��ȯ
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
	//�����̵�
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
	//��� Ȯ����
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

	//�ʿ�����Ʈ ��ġ
	if (g_pInputManager->IsOnceKeyDown('1'))
	{
		if (currentMode != E_MODE::M_BUILD)
		{
			//������ ���õ� �κ��� ������ �����ϰ� ��� ����
			DeselectObjects();
			
			//���� ���� ����
			currentMode = E_MODE::M_BUILD;
		}
		g_pMapObjectManager->getMapObjectRotation();
		g_pMapObjectManager->SetCursorIncrease();
	}
	//��������Ʈ ��ġ
	if (g_pInputManager->IsOnceKeyDown('2'))
	{
		if (currentMode != E_MODE::M_MOB)
		{
			//������ ���õ� �κ��� ������ �����ϰ� ��� ����
			DeselectObjects();
			//������ ���� ����
			currentMode = E_MODE::M_MOB;
			g_pObjectManager->GetMonsterRotation();
		}
		else
		{
			g_pObjectManager->SetCursorIncrease();
			g_pObjectManager->GetMonsterRotation();
		}
	}


	//�ʿ�����Ʈ ���̺� �ε� �׽�Ʈ
	if (g_pInputManager->IsOnceKeyDown('5'))
	{
		DeselectObjects();

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


	if (g_pInputManager->IsOnceKeyDown('6'))
	{
		DeselectObjects();

		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "�ʿ�����Ʈ �����ϱ�";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "��� ����(*.*)\0*.*\0�� ������Ʈ ����\0*.obj;\0";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 256;
		OFN.Flags = OFN_OVERWRITEPROMPT;
		//OFN.lpstrInitialDir = "c:\\";
		if (GetSaveFileName(&OFN) != 0) 
			g_pMapObjectManager->SaveCurrentObjectsState(OFN.lpstrFile);
	}


	//�� ���̺� �ε� �׽�Ʈ
	if (g_pInputManager->IsOnceKeyDown('7'))
	{
		DeselectObjects();

		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "�� ��ġ �����ϱ�";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "��� ����(*.*)\0*.*\0�� ��ġ ����\0*.enm;\0";
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
}
     
void cMapToolScene::Render(void)
{
	//�׽�Ʈ��
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	SAFE_RENDER(m_pSkybox);
	SAFE_RENDER(m_pMapTerrain);
	SAFE_RENDER(m_pGrid);

	//SAFE_RENDER(m_pBuild);
	g_pMapObjectManager->Render();
	g_pObjectManager->monsterRender();

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

}

