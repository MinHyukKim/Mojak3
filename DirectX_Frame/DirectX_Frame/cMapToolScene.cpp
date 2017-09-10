#include "stdafx.h"
#include "cMapToolScene.h"

#include "cCamera.h"
#include "cMapObject.h"

cMapToolScene::cMapToolScene(void)
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
	m_pMapObject->Setup(256, 256);


	return S_OK;
}

void cMapToolScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMapObject);
}

void cMapToolScene::Update(void)
{
}

void cMapToolScene::Render(void)
{
	SAFE_RENDER(m_pMapObject);
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

