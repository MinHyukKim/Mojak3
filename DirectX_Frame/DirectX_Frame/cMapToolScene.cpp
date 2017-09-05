#include "stdafx.h"
#include "cMapToolScene.h"

//테스트용
#include "cFont.h"

cMapToolScene::cMapToolScene(void)
{
	//테스트용
	m_pFont = NULL;
}

cMapToolScene::~cMapToolScene(void)
{
}

HRESULT cMapToolScene::Setup(void)
{
	//테스트용
	m_pFont = cFont::Create();
	m_pFont->Setup();
	m_pFont->DrawFont(0, 0, "씬매니저 가 첫 로딩에 성공했습니다.");

	return S_OK;
}

void cMapToolScene::Reset(void)
{
	//테스트용
	SAFE_RELEASE(m_pFont);
}

void cMapToolScene::Update(void)
{
	//테스트용
	SAFE_UPDATE(m_pFont);
	if (g_pInputManager->IsOnceKeyDown(VK_SPACE))
	{

	}
}

void cMapToolScene::Render(void)
{
	//테스트용
	SAFE_RENDER(m_pFont);
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

