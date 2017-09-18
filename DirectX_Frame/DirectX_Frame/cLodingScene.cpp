#include "stdafx.h"
#include "cLodingScene.h"


HRESULT cLodingScene::Setup(void)
{
	return E_NOTIMPL;
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
