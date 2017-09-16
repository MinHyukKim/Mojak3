#include "stdafx.h"
#include "cChareterCustomScene.h"

cChareterCustomScene::cChareterCustomScene(void)
{
}

cChareterCustomScene::~cChareterCustomScene(void)
{
}

HRESULT cChareterCustomScene::Setup(void)
{
	return E_NOTIMPL;
}

void cChareterCustomScene::Reset(void)
{
}

void cChareterCustomScene::Update(void)
{
}

void cChareterCustomScene::Render(void)
{
}

cChareterCustomScene* cChareterCustomScene::Create(void)
{
	cChareterCustomScene* newClass = new cChareterCustomScene;
	newClass->AddRef();
	return newClass;
}
