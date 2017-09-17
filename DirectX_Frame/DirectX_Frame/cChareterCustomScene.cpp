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
	//플레이어 생성
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->CreateMesh("Chareter/DefaultPlayer/", "lisaAniTest.X");

	//카메라 연결
	m_pMainCamera = m_pPlayer->GetCamera();
	m_pMainCamera->Setup();


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
