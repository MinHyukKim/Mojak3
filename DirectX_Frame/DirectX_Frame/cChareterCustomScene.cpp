#include "stdafx.h"
#include "cChareterCustomScene.h"

#include "cPlayer.h"

cChareterCustomScene::cChareterCustomScene(void)
{
}

cChareterCustomScene::~cChareterCustomScene(void)
{
}

HRESULT cChareterCustomScene::Setup(void)
{
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->CreateMesh("./Chareter/DefaultPlayer/", "ChareterNoAnimation.X");


	return S_OK;
}

void cChareterCustomScene::Reset(void)
{
	SAFE_RELEASE(m_pPlayer);
}

void cChareterCustomScene::Update(void)
{
	SAFE_UPDATE(m_pPlayer);
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
