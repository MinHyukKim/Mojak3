#include "stdafx.h"
#include "cChareterCustomScene.h"

#include "cPlayer.h"
#include "cCamera.h"

cChareterCustomScene::cChareterCustomScene(void)
	: m_pMainCamera(NULL)
	, m_pPlayer(NULL)
{
}

cChareterCustomScene::~cChareterCustomScene(void)
{
	this->Reset();
}

HRESULT cChareterCustomScene::Setup(void)
{

	return S_OK;
}

void cChareterCustomScene::Reset(void)
{
	SAFE_RELEASE(m_pPlayer);
}

void cChareterCustomScene::Update(void)
{
	SAFE_UPDATE(m_pPlayer);
	if (m_pMainCamera)
	{
		m_pMainCamera->TestController();
		m_pMainCamera->Update();
	}
}

void cChareterCustomScene::Render(void)
{
	SAFE_RENDER(m_pPlayer);
}

cChareterCustomScene* cChareterCustomScene::Create(void)
{
	cChareterCustomScene* newClass = new cChareterCustomScene;
	newClass->AddRef();
	return newClass;
}
