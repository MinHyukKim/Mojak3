#include "stdafx.h"
#include "cCharTestScene.h"

cCharTestScene::cCharTestScene(void)
{
}

cCharTestScene::~cCharTestScene(void)
{
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

