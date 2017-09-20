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
	//메인 버튼들
	E_MAIN_BUTTON_PLAYER_INFO = 213,
	E_MAIN_BUTTON_SKILL = 214,
	E_MAIN_BUTTON_QUEST = 215,
	E_MAIN_BUTTON_INVENTORY = 216,
	E_MAIN_BUTTON_ABILITY = 217,
	E_MAIN_BUTTON_ACTION = 218,
	E_MAIN_BUTTON_PET = 219,
	E_MAIN_BUTTON_MESSENGER = 220,
	E_MAIN_BUTTON_MIN = 221,
	E_MAIN_BUTTON_MAIN = 222,
	E_TEXT_VIEW
};

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isClick(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
	, m_pUiTestRoot(NULL)
	, m_isMainMin(false)
	, m_pMainRootImageView(NULL)
	, m_pMainMainButton(NULL)
	, m_pUiTesterSize(NULL)
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



	//테스트용 메인버튼들
	/*cUIImageView* */m_pMainRootImageView = cUIImageView::Create();
	m_pMainRootImageView->SetTexture("Texture/Ui/TestRoot2.png");
	m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pUiRoot = m_pMainRootImageView;

	cUITextView* pTextView = cUITextView::Create();
	pTextView->SetText("태스트용");
	pTextView->SetFontType(g_pFontManager->E_NORMAL);
	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	pTextView->SetSize(ST_SIZE(400, 500));
	pTextView->SetPosition(0, -300);
	pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUiRoot->AddChild(pTextView);

	cUIButton* pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_info_button_up.png", 
		"Texture/Ui/player_info_button_over.png",
		"Texture/Ui/player_info_button_down.png");
	pButton->SetPosition(mainButtonSrart, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_PLAYER_INFO);
	m_pUiRoot->AddChild(pButton);

	pButton =  cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_sikill_button_up.png", 
		"Texture/Ui/player_sikill_button_over.png",
		"Texture/Ui/player_sikill_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_SKILL);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_quest_button_up.png", 
		"Texture/Ui/player_quest_button_over.png",
		"Texture/Ui/player_quest_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 2, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_QUEST);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_inventory_button_up.png", 
		"Texture/Ui/player_inventory_button_over.png",
		"Texture/Ui/player_inventory_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 3, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_INVENTORY);
	m_pUiRoot->AddChild(pButton);

//	pButton = cUIButton::Create();
//	pButton->SetTexture("Texture/Ui/player_ability_button_up.png", 
//		"Texture/Ui/player_ability_button_over.png",
//		"Texture/Ui/player_ability_button_down.png");
//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 4, mainButtonH);
//	pButton->SetDelegate(this);
//	pButton->SetTag(E_MAIN_BUTTON_ABILITY);
//	m_pUiRoot->AddChild(pButton);
//
//	pButton = cUIButton::Create();
//	pButton->SetTexture("Texture/Ui/player_action_button_up.png", 
//		"Texture/Ui/player_action_button_over.png",
//		"Texture/Ui/player_action_button_down.png");
//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 5, mainButtonH);
//	pButton->SetDelegate(this);
//	pButton->SetTag(E_MAIN_BUTTON_ACTION);
//	m_pUiRoot->AddChild(pButton);
//
//	pButton = cUIButton::Create();
//	pButton->SetTexture("Texture/Ui/player_pet_button_up.png", 
//		"Texture/Ui/player_pet_button_over.png",
//		"Texture/Ui/player_pet_button_down.png");
//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 6, mainButtonH);
//	pButton->SetDelegate(this);
//	pButton->SetTag(E_MAIN_BUTTON_PET);
//	m_pUiRoot->AddChild(pButton);

	cUIButton* pMinButton = cUIButton::Create();
	pMinButton->SetTexture("Texture/Ui/button_min_up.png",
		"Texture/Ui/button_min_over.png",
		"Texture/Ui/button_min_up.png");
	pMinButton->SetPosition(mainButtonSrart + 190, mainButtonH + 26);
	pMinButton->SetDelegate(this);
	pMinButton->SetTag(E_MAIN_BUTTON_MIN);
	m_pUiRoot->AddChild(pMinButton);

	m_pMainMainButton = cUIButton::Create();
	m_pMainMainButton->SetTexture("Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-down.png");
	m_pMainMainButton->SetPosition(mainButtonSrart - 150, mainButtonH + 25);
	m_pMainMainButton->SetDelegate(this);
	m_pMainMainButton->SetTag(E_MAIN_BUTTON_MAIN);
	m_pUiRoot->AddChild(m_pMainMainButton);

	//임시 태스트용
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTestRoot = m_pUiTesterSize;

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
//	SAFE_RELEASE(m_pMainRootImageView);
	SAFE_RELEASE(m_pUiTestRoot);
//	SAFE_RELEASE(m_pMainMainButton);
}

void cUiTestScene::Update(void)
{
	//메인창 내리기
	if (m_isMainMin == true) m_pMainRootImageView->SetPosition(300, 520);
	else m_pMainRootImageView->SetPosition(300, 502);

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

//딜리게이트(클릭)
void cUiTestScene::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		pTextView->SetText("플레이어 정보창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		pTextView->SetText("플레이어 스킬창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		pTextView->SetText("퀘스트창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
		pTextView->SetText("인벤토리 창 구현하기");
	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
//	{
//		pTextView->SetText("재능창 구현하기(추가구성)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
//	{
//		pTextView->SetText("액션 창 구현하기(추가구성)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
//	{
//		pTextView->SetText("펫 창 구현하기(추가 구성)");
//	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}

}
