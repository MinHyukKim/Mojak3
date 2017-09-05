#include "stdafx.h"
#include "cMapToolScene.h"

//�׽�Ʈ��
#include "cFont.h"

cMapToolScene::cMapToolScene(void)
{
	//�׽�Ʈ��
	m_pFont = NULL;
}

cMapToolScene::~cMapToolScene(void)
{
}

HRESULT cMapToolScene::Setup(void)
{
	//�׽�Ʈ��
	m_pFont = cFont::Create();
	m_pFont->Setup();
	m_pFont->DrawFont(0, 0, "���Ŵ��� �� ù �ε��� �����߽��ϴ�.");

	return S_OK;
}

void cMapToolScene::Reset(void)
{
	//�׽�Ʈ��
	SAFE_RELEASE(m_pFont);
}

void cMapToolScene::Update(void)
{
	//�׽�Ʈ��
	SAFE_UPDATE(m_pFont);
	if (g_pInputManager->IsOnceKeyDown(VK_SPACE))
	{

	}
}

void cMapToolScene::Render(void)
{
	//�׽�Ʈ��
	SAFE_RENDER(m_pFont);
}

cMapToolScene* cMapToolScene::Create(void)
{
	cMapToolScene* newClass = new cMapToolScene;
	newClass->AddRef();
	return newClass;
}

