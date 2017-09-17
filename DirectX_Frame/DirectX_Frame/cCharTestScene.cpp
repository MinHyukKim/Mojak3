#include "stdafx.h"
#include "cCharTestScene.h"
#include "cSkinnedMesh.h"
#include "crtCtl.h"

#include "cCamera.h"
//테스트용
#include "cGrid.h"
#include "cMapTerrain.h"

cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCrtCtrl(NULL)
	, m_pMapTerrain(NULL)
{
}

cCharTestScene::~cCharTestScene(void)
{
	this->Reset();
}

HRESULT cCharTestScene::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();
	m_pCamera->SetCameraType(cCamera::E_AIRCRAFT); // 뱅기모드

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();

	SetMatrial(&m_stMtl.MatD3D);
	m_stMtl.pTextureFilename = "./Texture/steppegrass01_only.dds";

	m_pMapTerrain = cMapTerrain::Create();
	m_pMapTerrain->Setup("./HeightMapData/HeightMap.raw", &m_stMtl);


	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Chareter/DefaultPlayer/", "hair_female_hair22_t22fbx.X");
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "bodymap01.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 1.0f));	//몸통
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "hair10.dds", &D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));		//머리
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "bodymap04.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 1.0f));	//얼굴
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "eye_0.dds", &D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//눈(블렌딩 필요)
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "mouth_0.dds", &D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//입(블렌딩 필요)
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "male_pumpkin_pants_c.dds", &D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));	//목걸이
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "uni_newbie03_c.dds", &D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));			// 하의
	cSkinnedMesh::SetTextureColor(pSkinnedMesh->GetRootFrame(), "uni_3rd_premium_c.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));		//상의
	pSkinnedMesh->setPosition(D3DXVECTOR3(0, 0, 0));
	pSkinnedMesh->SetRandomTrackPosition();

	//애니메이션
	cSkinnedMesh* pSkinnedMesh2 = new cSkinnedMesh("Chareter/DefaultPlayer/", "test_uni_natural_attack_01.X");

	//애니메이션 등록
	LPD3DXANIMATIONSET pAni;
	pSkinnedMesh2->GetAnimationController()->GetAnimationSet(0, &pAni);
	pSkinnedMesh->AddAnimationSet(pAni);
	
	//애니메이션 변경
	pSkinnedMesh->GetAnimationController()->SetTrackAnimationSet(0, pAni);
	pSkinnedMesh->GetAnimationController()->SetTrackSpeed(0, 1.00f);
	pSkinnedMesh->GetAnimationController()->SetTrackWeight(0, 1.00f);
	SAFE_RELEASE(pAni);
	SAFE_DELETE(pSkinnedMesh2);

	m_pCrtCtrl = new cCrtCtrl;

	m_vecSkinnedMesh.push_back(pSkinnedMesh);
	return S_OK;

}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//테스트용
	SAFE_RELEASE(m_pGrid);
	for each(auto it in m_vecSkinnedMesh)
	{
		SAFE_DELETE(it);
	}
	SAFE_RELEASE(m_pMapTerrain);
}

void cCharTestScene::Update(void)
{

	//테스트용
	m_pCamera->TestController();

	m_pCamera->Update();
	
	m_pMapTerrain->Update();
	//m_pCrtCtrl->Update(m_pMapTerrain);
}

void cCharTestScene::Render(void)
{

//		D3DLIGHT9 stLight;
//	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
//	stLight.Type = D3DLIGHT_DIRECTIONAL;
//	D3DXVECTOR3 vDir(1, -1, 1);
//	D3DXVec3Normalize(&vDir, &vDir);
//	stLight.Direction = vDir;
//	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
//	g_pD3DDevice->SetLight(0, &stLight);
//	g_pD3DDevice->LightEnable(0, true);
	SAFE_RENDER(m_pGrid);


	g_pD3DDevice->SetMaterial(&m_stMtl.MatD3D);


	for each (auto p in m_vecSkinnedMesh)
	{
		if (&p->getPosition())
			p->UpdateAndRender();
	}

	m_pMapTerrain->Render();
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

