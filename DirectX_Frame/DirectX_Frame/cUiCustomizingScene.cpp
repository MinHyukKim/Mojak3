
#include "stdafx.h"
#include "cUiCustomizingScene.h"
//폰트 용
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

enum
{
	E_SERVER_TEXT_NEXT,
	E_SERVER_TEXT_CANCEL,
	E_SERVER_BUTTON_SERVER = 213,
	E_SERVER_BUTTON_NEXT = 214,
	E_SERVER_BUTTON_CANCEL = 215,
	
};

cUiCustomizingScene::cUiCustomizingScene(void)
	: m_mUiTest(NULL)
	, m_pUiTesterSize(NULL)
	, m_pSprite(NULL)
	, m_pTexture(NULL)

	, m_pServerSulastHeadImage(NULL)
	, m_pServerSulastImage(NULL)
	, m_pServerSulastButton(NULL)
	, m_pServerTextNext(NULL)
	, m_pServerTextCancel(NULL)
	, m_pServerSulastUi(NULL)
{
}

cUiCustomizingScene::~cUiCustomizingScene(void)
{
	this->Reset();
}


cUiCustomizingScene * cUiCustomizingScene::Create(void)
{
	cUiCustomizingScene* newClass = new cUiCustomizingScene;
	newClass->AddRef();
	return newClass;
}

HRESULT cUiCustomizingScene::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//이미지 크기 태스트
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTesterSize->SetTexture("Texture/Ui/textButtonUp.png");
	m_pUiTesterSize->SetPosition(100, 20);
	m_mUiTest = m_pUiTesterSize;

	//서버 창 머리
	m_pServerSulastHeadImage = cUIImageView::Create();
	m_pServerSulastHeadImage->SetTexture("Texture/Ui/customUiBaseHead1.png"); 
	m_pServerSulastHeadImage->SetPosition(20, 20);
	m_pServerSulastHeadImage->m_Alpha = 200;
	m_pServerSulastUi = m_pServerSulastHeadImage;
	//서버 창
	m_pServerSulastImage = cUIImageView::Create();
	m_pServerSulastImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pServerSulastImage->SetPosition(2, 48);
	m_pServerSulastImage->m_Alpha = 180;
	m_pServerSulastUi->AddChild(m_pServerSulastImage);
	//버튼1(다음)
	m_pServerSulastButton = cUIButton::Create();
	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonDown6024.png");
	m_pServerSulastButton->SetPosition(10, 370);
	m_pServerSulastButton->SetDelegate(this);
	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_NEXT);
	m_pServerSulastUi->AddChild(m_pServerSulastButton);
	//택스트
	m_pServerTextNext = cUITextView::Create();
	m_pServerTextNext->SetText("다음>>");
	m_pServerTextNext->SetFontType(g_pFontManager->E_INBUTTON);
	m_pServerTextNext->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pServerTextNext->SetSize(ST_SIZE(50, 40));
	m_pServerTextNext->SetPosition(10, 363);
	m_pServerTextNext->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pServerTextNext->SetTag(E_SERVER_TEXT_NEXT);
	m_pServerSulastUi->AddChild(m_pServerTextNext);
	//버튼2(취소)
	m_pServerSulastButton = cUIButton::Create();
	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png");
	m_pServerSulastButton->SetPosition(164, 370);
	m_pServerSulastButton->SetDelegate(this);
	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_CANCEL);
	m_pServerSulastUi->AddChild(m_pServerSulastButton);
	//택스트
	m_pServerTextCancel = cUITextView::Create();
	m_pServerTextCancel->SetText("취소");
	m_pServerTextCancel->SetFontType(g_pFontManager->E_INBUTTON);
	m_pServerTextCancel->SetColor(D3DCOLOR_XRGB(180, 180, 180));
	m_pServerTextCancel->SetSize(ST_SIZE(50, 40));
	m_pServerTextCancel->SetPosition(169, 363);
	m_pServerTextCancel->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pServerTextCancel->SetTag(E_SERVER_TEXT_CANCEL);
	m_pServerSulastUi->AddChild(m_pServerTextCancel);

	//커마 창




	return D3D_OK;
}

void cUiCustomizingScene::Reset(void)
{
	SAFE_RELEASE(m_mUiTest);

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

	SAFE_RELEASE(m_pServerSulastUi);
}

void cUiCustomizingScene::Update(void)
{
	if (m_pServerSulastUi) m_pServerSulastUi->Update();
	if (m_mUiTest) m_mUiTest->Update();
}

void cUiCustomizingScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);

	if (m_pServerSulastUi) m_pServerSulastUi->Render(m_pSprite);
	if (m_mUiTest) m_mUiTest->Render(m_pSprite);
}

void cUiCustomizingScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cUiCustomizingScene::OnClick(cUIButton * pSender)
{
	//cUITextView* pTextView = (cUITextView*)m_pServerSulastUi->GetChildByTag(E_SERVER_TEXT_NEXT);
	// 0x8001 = 토글
	if (pSender->GetTag() == E_SERVER_BUTTON_NEXT)
	{

	}

	
}