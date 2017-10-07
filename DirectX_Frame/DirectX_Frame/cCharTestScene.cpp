#include "stdafx.h"
#include "cCharTestScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"
#include "cSkybox.h"

//테스트용
#include "cMapObject.h"
#include "cGrid.h"
//Ui 연동 테스트
#include "cUiTestScene.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pUi(NULL)
	, m_pNPC(nullptr)
	, m_pSkybox(nullptr)
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

	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(-2.0f, 0.0f, 5.0f), &FOX_BROWN);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(0.0f, 0.0f, 4.0f), &FOX_GRAY);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_FOX, &D3DXVECTOR3(2.0f, 0.0f, 5.0f), &FOX_RED);
	g_pObjectManager->CreateMonster(cObjectManager::MONSTER_BEAR, &D3DXVECTOR3(0.0f, 0.0f, 7.0f), &BEAR_BLACK);

	//npc태스트
	g_pObjectManager->CreateNPC(cObjectManager::NPC_NAO, &D3DXVECTOR3(-1.0f, 0.0f, 1.0f));

	//로딩속도 저하 원인
	m_pSkybox = cSkybox::Create();
	m_pSkybox->Setup(".\\skyboxMap\\vanilla_sky_frost_up.jpg", ".\\skyboxMap\\vanilla_sky_frost_dn.jpg",
		".\\skyboxMap\\vanilla_sky_frost_lf.jpg", ".\\skyboxMap\\vanilla_sky_frost_rt.jpg",
		".\\skyboxMap\\vanilla_sky_frost_ft.jpg", ".\\skyboxMap\\vanilla_sky_frost_bk.jpg");

	return S_OK;
}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pNPC);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapTerrain);

	//테스트용
	//SAFE_RELEASE(m_pMapObject);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pUi);
	SAFE_RELEASE(m_pSkybox);

}

void cCharTestScene::Update(void)
{
	//테스트용
//	if (m_pCamera) m_pCamera->TestController();
	if (m_pCamera) m_pCamera->WheelController();

	if (this->GetSelectNPC())
	{
		//NPC가 선택됬음
		cPlayer* pPlayer = g_pObjectManager->GetPlayer();
		if (pPlayer)
		{
			//Player가 있을때
			float fDist = 0.0f;
			if (pPlayer->DistSqTarget(&fDist, this->GetSelectNPC()))
			{
				//타겟이 있으면 fDist에 거리를 반환
				if (fDist < 0.3f)
				{
					//플레이어와의 거리가 0.3이하일때
					//음직이지 않는다
					pPlayer->OrderIden();
					//대화 띄우기
					pPlayer->GetAbilityParamter()->SetDialogOpen(true);
					//선택해제
					this->SetSelectNPC(nullptr);
				}
				else
				{
					//플레이어와의 거리가 0.3 초과일때

					//NPC쪽으로 이동
					pPlayer->OrderMove(&this->GetSelectNPC()->GetPosition());
				}
			}
		}
		else
		{
			//Player가 없을때
		}
	}
	else
	{
		//NPC가 선택되지 않았음
	}

	//if (m_pUi->GetMoveingOK() || true)
	SAFE_UPDATE(m_pUi);
	if (m_pUi->GetMoveingOK())
	{
		if (m_pCamera) m_pCamera->MouseController();
		if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
		{
			this->SetSelectNPC(nullptr);
			cPlayer* pUnit = nullptr;	//
			D3DXVECTOR3 vTo, vRay, vDir;
			g_pRay->RayAtWorldSpace(&vRay, &vDir);
			if (g_pObjectManager->GetMonster(&pUnit, &vRay, &vDir))	//몬스터가 피킹되면 pMonster 에 저장 후 True;
			{
				g_pObjectManager->GetPlayer()->OrderAttack(pUnit);
			}

			//NPC
			if (g_pObjectManager->GetNPC(&pUnit, &vRay, &vDir))
			{
				this->SetSelectNPC(pUnit);
			}
			else if (m_pMapTerrain->IsCollision(&vTo, &vRay, &vDir))	//바닥이 피킹되면 vTo 에 위치 저장후 True;
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
	if (g_pInputManager->IsOnceKeyDown(VK_ESCAPE))
	{
		if (g_pObjectManager->GetPlayer()->CheckState(PATTERN_SMASH))
		{
			g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_SMASH);
		}
		if (g_pObjectManager->GetPlayer()->CheckState(PATTERN_COUNTER))
		{
			g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_RUN | PATTERN_WALK);
			g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_COUNTER);
		}
	}
	if (g_pInputManager->IsOnceKeyDown('1'))
	{
		if (g_pObjectManager->GetPlayer()->CheckState(PATTERN_COUNTER))
		{
			g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_RUN | PATTERN_WALK);
			g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_COUNTER);
		}
		g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_SMASH);
	}
	if (g_pInputManager->IsOnceKeyDown('2'))
	{
		if (g_pObjectManager->GetPlayer()->CheckState(PATTERN_SMASH))
		{
			g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_SMASH);
		}
		g_pObjectManager->GetPlayer()->SetStateTrue(PATTERN_COUNTER);
		g_pObjectManager->GetPlayer()->SetStateFalse(PATTERN_RUN | PATTERN_WALK);
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
	if (g_pInputManager->IsOnceKeyDown('T'))
	{
		g_pMeshFontManager->AddFont("텍스쳐", &(g_pObjectManager->GetPlayer()->GetPosition() + D3DXVECTOR3(0.0f, g_pObjectManager->GetPlayer()->GetRadius(), 0.0f)));
	}



	//맵오브젝트 세이브 로드 테스트
	if (g_pInputManager->IsOnceKeyDown('0'))
	{
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


	if (g_pInputManager->IsOnceKeyDown('9'))
	{
		OPENFILENAME OFN;
		char filename[255];
		char lpstrFile[MAX_PATH] = "";
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lpstrTitle = "몬스터 배치 로드하기";
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = g_hWnd;
		OFN.lpstrFilter = "모든 파일(*.*)\0*.*\0맵 오브젝트 파일\0*.obj;\0";
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
	if (m_pSkybox) m_pSkybox->Update(*m_pCamera->GetPosition());


}

void cCharTestScene::Render(void)
{
	//테스트용
//	g_pD3DDevice->SetTexture(0, m_pTexture);
//	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);
	//SAFE_RENDER(m_pMapObject);
	SAFE_RENDER(m_pSkybox);

	SAFE_RENDER(m_pMapTerrain);

	SAFE_RENDER(m_pGrid);

	SAFE_RENDER(g_pObjectManager);
	SAFE_RENDER(g_pMapObjectManager);
	SAFE_RENDER(m_pUi);

}

void cCharTestScene::SetSelectNPC(cPlayer* pNPC)
{
	SAFE_RELEASE(m_pNPC);
	m_pNPC = pNPC;
	SAFE_ADDREF(m_pNPC);
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

