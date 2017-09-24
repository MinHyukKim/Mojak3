#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

void cUiTestScene::SetupInfoUi(void)
{
	//정보 창 머리
	m_pInfoUiImageHead = cUIImageView::Create();
	m_pInfoUiImageHead->SetTexture("Texture/Ui/infoBaseHead1.png");
	m_pInfoUiImageHead->SetPosition(infoX, infoY);
	m_pInfoUiImageHead->m_Alpha = 200;
	m_pInfoUi = m_pInfoUiImageHead;
	//드래그 버튼
	m_pInfoUiMoveing = cUIButton::Create();
	m_pInfoUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pInfoUiMoveing->SetPosition(0, 0);
	m_pInfoUiMoveing->SetDelegate(this);
	m_pInfoUiMoveing->m_Alpha = 0;
	m_pInfoUiMoveing->SetTag(E_INFO_MOVE);
	m_pInfoUi->AddChild(m_pInfoUiMoveing);
	//정보 베이스 창
	m_pInfoUiImage = cUIButton::Create();
	m_pInfoUiImage->SetTexture("Texture/Ui/Base.png"
	, "Texture/Ui/Base.png", "Texture/Ui/Base.png");
	m_pInfoUiImage->SetPosition(2, 48);
	m_pInfoUiImage->SetDelegate(this);
	m_pInfoUiImage->SetTag(E_BUTTON_NONE);
	m_pInfoUiImage->m_Alpha = 180;
	m_pInfoUi->AddChild(m_pInfoUiImage);

	////글씨
	//cUITextView* TextFin = cUITextView::Create();
	//TextFin->SetText("완료");
	//TextFin->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	//TextFin->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	//TextFin->SetSize(ST_SIZE(50, 40));
	////TextFin->SetPosition(169, 355); //마비체
	//TextFin->SetPosition(169, 362);   //나눔고딕
	//TextFin->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	//TextFin->SetTag(E_TEXT_CUSTOM_FIN);
	//m_pCustomUi->AddChild(TextFin);

	//베이스 택스트들
	//이름
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("이름");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(10, 50 - 7); //마비체
	m_pInfoUiText->SetPosition(10, 50);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//나이
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("나이");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(10, 80 - 7); //마비체
	m_pInfoUiText->SetPosition(10, 80);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//종족/성별
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("종족/성별");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(100, 40));
	//m_pInfoUiText->SetPosition(-1, 110 - 7); //마비체
	m_pInfoUiText->SetPosition(-1, 110);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//피통
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("생명력");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(15, 150 - 7); //마비체
	m_pInfoUiText->SetPosition(15, 150);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//마나
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("마나");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(1, 170 - 7); //마비체
	m_pInfoUiText->SetPosition(10, 170);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//스태미나
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("스테미나");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(100, 40));
	//m_pInfoUiText->SetPosition(-5, 190 - 7); //마비체
	m_pInfoUiText->SetPosition(-5, 190);   //나눔고딕
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
}