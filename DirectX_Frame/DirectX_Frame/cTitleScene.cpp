#include "stdafx.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene(void)
{
}

cTitleScene::~cTitleScene(void)
{
}

HRESULT cTitleScene::Setup(void)
{
	return E_NOTIMPL;
}

void cTitleScene::Reset(void)
{
}

void cTitleScene::Update(void)
{
}

void cTitleScene::Render(void)
{
}

cTitleScene* cTitleScene::Create(void)
{
	cTitleScene* newClass = new cTitleScene;
	newClass->AddRef();
	return newClass;
}

