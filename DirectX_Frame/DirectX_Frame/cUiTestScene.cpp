#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

enum
{
	E_CONFIRM_BUTTON = 213,
	E_CANCEL_BUTTON = 214,
	E_TEXT_VIEW
};

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isClick(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
{
}

cUiTestScene::~cUiTestScene(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
}


HRESULT cUiTestScene::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pimageView = new cUIImageView;
	pimageView->SetTexture("Ui/panel-info.png");
	m_pUiRoot = pimageView;

	cUITextView* pTextView = new cUITextView;
//	pTextView->

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

void cUiTestScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

cSceneObject * cUiTestScene::Create(void)
{
	return nullptr;
}