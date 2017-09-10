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
	//
	//m_pMapObject = cMapObject::Create();
	//m_pMapObject->Setup(256, 256);

	//�׽�Ʈ��
	m_pGrid = new cGrid;
	m_pGrid->AddRef();
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
}

void cMapToolScene::Render(void)
{
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

