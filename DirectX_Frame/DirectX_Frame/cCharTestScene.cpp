#include "stdafx.h"
#include "cCharTestScene.h"
#include "cSkinnedMesh.h"


#include "cCamera.h"
//테스트용
#include "cGrid.h"


cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
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

	//테스트용
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();

	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("", "Run3.X");
	pSkinnedMesh->setPosition(D3DXVECTOR3(0, 3, 0));
	pSkinnedMesh->SetRandomTrackPosition();

	cSkinnedMesh* pSkinnedMesh2 = new cSkinnedMesh("", "winnly_attack.X");
	pSkinnedMesh2->setPosition(D3DXVECTOR3(2, 3, 0));
	pSkinnedMesh2->SetRandomTrackPosition();


	m_vecSkinnedMesh.push_back(pSkinnedMesh);
	m_vecSkinnedMesh.push_back(pSkinnedMesh2);
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
}

void cCharTestScene::Update(void)
{

	//테스트용
	m_pCamera->TestController();

	m_pCamera->Update();


}

void cCharTestScene::Render(void)
{

		D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	SAFE_RENDER(m_pGrid);


	g_pD3DDevice->SetMaterial(&m_stMtl);


	for each (auto p in m_vecSkinnedMesh)
	{
		if (&p->getPosition())
			p->UpdateAndRender();
	}
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

