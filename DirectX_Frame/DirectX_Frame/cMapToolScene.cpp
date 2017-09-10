#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapObject.h"
//�׽�Ʈ��
#include "cGrid.h"

cMapToolScene::cMapToolScene(void)
	: m_pCamera(NULL)
	, m_pMapObject(NULL)
{
}

cMapToolScene::~cMapToolScene(void)
{
}

HRESULT cMapToolScene::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();

	m_pMapObject = cMapObject::Create();
	m_pMapObject->Setup("./HeightMapData/HeightMap.raw");

	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();


	return S_OK;
}

void cMapToolScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapObject);
	//�׽�Ʈ��
	SAFE_RELEASE(m_pGrid);
}

void cMapToolScene::Update(void)
{
	m_pCamera->TestController();
	m_pCamera->Update();
}

void cMapToolScene::Render(void)
{
	//g_pD3DDevice->SetTexture(0, g_pTexture->GetTexture("./HeightMapData/terrain.jpg"));
	SAFE_RENDER(m_pMapObject);
	//�׽�Ʈ��
	SAFE_RENDER(m_pGrid);
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

