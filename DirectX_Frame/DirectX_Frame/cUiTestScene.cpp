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
	pTextView->SetText("태스트용");
	pTextView->SetSize(ST_SIZE(300, 200));
	pTextView->SetPosition(100, 100);
	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUiRoot->AddChild(pTextView);

	D3DXMATRIX matWorld, matS, matR;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	matWorld = matS * matR;

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

void cUiTestScene::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_CONFIRM_BUTTON)
	{
		pTextView->SetText("1버튼(CONFIRM) 택스트 변경");
	}
	else if (pSender->GetTag() == E_CANCEL_BUTTON)
	{
		pTextView->SetText("2버튼(CANCEL) 택스트 변경");
	}
}

cSceneObject * cUiTestScene::Create(void)
{
	return nullptr;
}