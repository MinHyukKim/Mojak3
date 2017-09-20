#include "stdafx.h"
#include "cLodingScene.h"

#include "cDataLoder.h"

cLodingScene::cLodingScene(void)
	: m_pData(nullptr)
{
}

cLodingScene::~cLodingScene(void)
{
}

HRESULT cLodingScene::Setup(void)
{
	SAFE_RELEASE(m_pData);
	m_pData = cDataLoder::Create();
	m_pData->RegisterData("./Data/SetupData.txt");
	return S_OK;
}

void cLodingScene::Reset(void)
{
	SAFE_RELEASE(m_pData);
}

void cLodingScene::Update(void)
{
}

void cLodingScene::Render(void)
{
}

cLodingScene* cLodingScene::Create(void)
{
	cLodingScene* newClass = new cLodingScene;
	newClass->AddRef();
	return newClass;
}

