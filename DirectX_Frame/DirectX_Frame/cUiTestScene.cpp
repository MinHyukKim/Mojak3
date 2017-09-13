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
	E_3_BUTTON = 215,
	E_4_BUTTON = 216,
	E_5_BUTTON = 217,
	E_6_BUTTON = 218,
	E_7_BUTTON = 219,
	E_8_BUTTON = 220,
	E_TEXT_VIEW
};

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isClick(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
	, m_pUiTestRoot(NULL)
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
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//���� uiƲ ��ġ
	int mainUiLocalX = 300;			//���� Ʋ x
	int mainUiLocalY = 500;			//���� Ʋ y

	int mainButtonH = -25;			//���� ��ư�� ����
	int mainButtoninterval = 40;	//���� ��ư�� ���� ����(ũ��)
	int mainButtonSrart = 180;		//���� ��ư�� ���� ���� ��ġ

	//�׽�Ʈ�� ���ι�ư��
	cUIImageView* pImageView = cUIImageView::Create();
	pImageView->SetTexture("Texture/Ui/TestRoot1.png");
	pImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pUiRoot = pImageView;

	cUITextView* pTextView = cUITextView::Create();
	pTextView->SetText("�½�Ʈ��");
	pTextView->SetSize(ST_SIZE(400, 200));
	pTextView->SetPosition(0, -300);
	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUiRoot->AddChild(pTextView);

	cUIButton* pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/01_button_up.png", "Texture/Ui/01_button_over.png",
		"Texture/Ui/01_button_down.png");
	pButton->SetPosition(mainButtonSrart, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_CONFIRM_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton =  cUIButton::Create();
	pButton->SetTexture("Texture/Ui/02_button_up.png", "Texture/Ui/02_button_over.png",
		"Texture/Ui/02_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_CANCEL_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/03_button_up.png", "Texture/Ui/03_button_over.png",
		"Texture/Ui/03_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 2, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_3_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/04_button_up.png", "Texture/Ui/04_button_over.png",
		"Texture/Ui/04_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 3, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_4_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/05_button_up.png", "Texture/Ui/05_button_over.png",
		"Texture/Ui/05_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 4, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_5_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/06_button_up.png", "Texture/Ui/06_button_over.png",
		"Texture/Ui/06_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 5, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_6_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/07_button_up.png", "Texture/Ui/07_button_over.png",
		"Texture/Ui/07_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 6, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_7_BUTTON);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/08_button_up.png", "Texture/Ui/08_button_over.png",
		"Texture/Ui/08_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 7, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_8_BUTTON);
	m_pUiRoot->AddChild(pButton);

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
	SAFE_RELEASE(m_pUiTestRoot);
}

void cUiTestScene::Update(void)
{
	if (m_pUiRoot) m_pUiRoot->Update();
}

void cUiTestScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	if(m_pUiRoot) m_pUiRoot->Render(m_pSprite);
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
		pTextView->SetText("1��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_CANCEL_BUTTON)
	{
		pTextView->SetText("2��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_3_BUTTON)
	{
		pTextView->SetText("3��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_4_BUTTON)
	{
		pTextView->SetText("4��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_5_BUTTON)
	{
		pTextView->SetText("5��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_6_BUTTON)
	{
		pTextView->SetText("6��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_7_BUTTON)
	{
		pTextView->SetText("7��ư �׽�Ʈ");
	}
	else if (pSender->GetTag() == E_8_BUTTON)
	{
		pTextView->SetText("8��ư �׽�Ʈ");
	}
}
