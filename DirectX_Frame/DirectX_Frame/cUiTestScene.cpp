#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
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
	, m_pUIImageView(NULL)
{
}

cUiTestScene::~cUiTestScene(void)
{
	this->Reset();
}

cUiTestScene* cUiTestScene::Create(void)
{
	cUiTestScene* newClass = new cUiTestScene;
	newClass->AddRef();
	return newClass;
}

HRESULT cUiTestScene::Setup(void)
{
//	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
//
//	m_pUIImageView = cUIImageView::Create();
//	m_pUIImageView->SetTexture("Ui/panel-info.png");
//	m_pUiRoot = m_pUIImageView;
//
//	cUITextView* pTextView = cUITextView::Create();
//	pTextView->SetText("�½�Ʈ��");
//	pTextView->SetSize(ST_SIZE(400, 200));
//	pTextView->SetPosition(80, 100);
//	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	pTextView->SetTag(E_TEXT_VIEW);
//	m_pUiRoot->AddChild(pTextView);
//
//	cUIButton* pButton = cUIButton::Create();
//	pButton->SetTexture("Ui/btn-med-up.png", "Ui/btn-med-over.png",
//		"Ui/btn-med-down.png");
//	pButton->SetPosition(135, 330);
//	pButton->SetDelegate(this);
//	pButton->SetTag(E_CONFIRM_BUTTON);
//	m_pUiRoot->AddChild(pButton);
//
//	pButton =  cUIButton::Create();
//	pButton->SetTexture("Ui/btn-med-up.png", "Ui/btn-med-over.png",
//		"Ui/btn-med-down.png");
//	pButton->SetPosition(135, 400);
//	pButton->SetDelegate(this);
//	pButton->SetTag(E_CANCEL_BUTTON);
//	m_pUiRoot->AddChild(pButton);

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
	SAFE_RELEASE(m_pUIImageView);
}

void cUiTestScene::Update(void)
{
//	if (m_pUiRoot) m_pUiRoot->Update();
}

void cUiTestScene::Render(void)
{
//	g_pD3DDevice->SetTexture(0, m_pTexture);
//	if(m_pUiRoot) m_pUiRoot->Render(m_pSprite);
}

void cUiTestScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

//void cUiTestScene::OnClick(cUIButton * pSender)
//{
//	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
//	if (pTextView == NULL) return;
//
//	if (pSender->GetTag() == E_CONFIRM_BUTTON)
//	{
//		pTextView->SetText("1��ư(CONFIRM) �ý�Ʈ ����");
//	}
//	else if (pSender->GetTag() == E_CANCEL_BUTTON)
//	{
//		pTextView->SetText("2��ư(CANCEL) �ý�Ʈ ����");
//	}
//}
