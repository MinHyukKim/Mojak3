#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
{
}

cUiTestScene::~cUiTestScene(void)
{
	SAFE_RELEASE(m_pFont);
}


HRESULT cUiTestScene::Setup(void)
{


	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
}

void cUiTestScene::Update(void)
{
}

void cUiTestScene::Render(void)
{
}

cSceneObject * cUiTestScene::Create(void)
{
	return nullptr;
}