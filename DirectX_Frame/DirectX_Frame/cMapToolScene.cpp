#include "stdafx.h"
#include "cMapToolScene.h"

cMapToolScene::cMapToolScene(void)
{
}

cMapToolScene::~cMapToolScene(void)
{
}

HRESULT cMapToolScene::Setup(void)
{
	return S_OK;
}

void cMapToolScene::Reset(void)
{
}

void cMapToolScene::Update(void)
{
}

void cMapToolScene::Render(void)
{
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

