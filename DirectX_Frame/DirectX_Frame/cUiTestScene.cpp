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
//	m_pUIImageView = cUIImageView::Create();
//	m_pGrid = cGrid::Create();
	pimageView->SetTexture("Ui/panel-info.png");
	m_pUiRoot = pimageView;

	cUITextView* pTextView = new cUITextView;
	pTextView->SetText("태스트용");
	pTextView->SetSize(ST_SIZE(300, 200));
	pTextView->SetPosition(100, 100);
	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUiRoot->AddChild(pTextView);

	cUIButton* pButton = new cUIButton;
	pButton->SetTexture("Ui/btn-med-up.png", "Ui/btn-med-over.png",
		"Ui/btn-med-down.png");
	pButton->SetPosition(135, 330);
	pButton->SetDelegate(this);
	pButton->SetTag(E_CONFIRM_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetTexture("Ui/btn-med-up.png", "Ui/btn-med-over.png",
		"Ui/btn-med-down.png");
	pButton->SetPosition(135, 400);
	pButton->SetDelegate(this);
	pButton->SetTag(E_CONFIRM_BUTTON);
	m_pUiRoot->AddChild(pButton);


//	D3DXMATRIX matWorld, matS, matR;
//	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
//	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
//	matWorld = matS * matR;

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
//	SAFE_RELEASE(m_pFont);
//	SAFE_RELEASE(m_pSprite);
//	SAFE_RELEASE(m_pTexture);
//	SAFE_RELEASE(m_pUiRoot);
}

void cUiTestScene::Update(void)
{
	if (m_pUiRoot) m_pUiRoot->Update();
}

void cUiTestScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
//	SAFE_RENDER(m_pUiRoot->Render(m_pSprite));
	m_pUiRoot->Render(m_pSprite);
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
	cUiTestScene* newClass = new cUiTestScene;
	newClass->AddRef();
	return newClass;
}