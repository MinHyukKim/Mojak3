#include "stdafx.h"
#include "cTestScene.h"

cTestScene::cTestScene(void)
{
}

cTestScene::~cTestScene(void)
{
}

cTestScene* cTestScene::Create(void)
{
	cTestScene* newClass = new cTestScene;
	newClass->AddRef();
	return newClass;
}

