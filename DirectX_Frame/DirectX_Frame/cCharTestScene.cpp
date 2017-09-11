#include "stdafx.h"
#include "cCharTestScene.h"
#include "cSkinnedMesh.h"


#include "cCamera.h"
//�׽�Ʈ��
#include "cGrid.h"


cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
{
}

cCharTestScene::~cCharTestScene(void)
{
}

HRESULT cCharTestScene::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();

	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();

	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zealot/", "Zealot.X");
	pSkinnedMesh->setPosition(D3DXVECTOR3(0, 0, 0));
	pSkinnedMesh->SetRandomTrackPosition();

	m_vecSkinnedMesh.push_back(pSkinnedMesh);
	return S_OK;

}

void cCharTestScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//�׽�Ʈ��
	SAFE_RELEASE(m_pGrid);
}

void cCharTestScene::Update(void)
{

	//�׽�Ʈ��
	m_pCamera->TestController();

	m_pCamera->Update();


}

void cCharTestScene::Render(void)
{
	SAFE_RENDER(m_pGrid);

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

