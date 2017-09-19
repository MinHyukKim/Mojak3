#include "stdafx.h"
#include "cLodingScene.h"

#include "cDataLoder.h"

HRESULT cLodingScene::Setup(void)
{
	cDataLoder* pData = cDataLoder::Create();
	pData->RegisterData("./Data/SetupData.txt");
	SAFE_RELEASE(pData);
	return S_OK;
}

void cLodingScene::Reset(void)
{
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

cLodingScene::cLodingScene()
{
}


cLodingScene::~cLodingScene()
{
}
