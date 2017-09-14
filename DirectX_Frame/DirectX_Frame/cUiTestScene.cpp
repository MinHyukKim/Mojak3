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

	//메인 ui틀 위치
	int mainUiLocalX = 300;			//메인 틀 x
	int mainUiLocalY = 500;			//메인 틀 y

	int mainButtonH = -25;			//메인 버튼들 높이
	int mainButtoninterval = 40;	//메인 버튼들 가로 간격(크기)
	int mainButtonSrart = 180;		//메인 버튼들 최초 시작 위치

	//테스트용 메인버튼들
	cUIImageView* pImageView = cUIImageView::Create();
	pImageView->SetTexture("Texture/Ui/TestRoot1.png");
	pImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pUiRoot = pImageView;

	cUITextView* pTextView = cUITextView::Create();
	pTextView->SetText("태스트용");
	pTextView->SetSize(ST_SIZE(400, 200));
	pTextView->SetPosition(0, -300);
	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
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

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_ability_button_up.png", 
		"Texture/Ui/player_ability_button_over.png",
		"Texture/Ui/player_ability_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 4, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_ABILITY);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_action_button_up.png", 
		"Texture/Ui/player_action_button_over.png",
		"Texture/Ui/player_action_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 5, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_ACTION);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_pet_button_up.png", 
		"Texture/Ui/player_pet_button_over.png",
		"Texture/Ui/player_pet_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 6, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_PET);
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
	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
	{
		pTextView->SetText("재능창 구현하기(추가구성)");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
	{
		pTextView->SetText("액션 창 구현하기(추가구성)");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
	{
		pTextView->SetText("펫 창 구현하기(추가 구성)");
	}

//	E_MAIN_BUTTON_PLAYER_INFO = 213,
//		E_MAIN_BUTTON_SKILL = 214,
//		E_MAIN_BUTTON_QUEST = 215,
//		E_MAIN_BUTTON_INVENTORY = 216,
//		E_MAIN_BUTTON_ABILITY = 217,
//		E_MAIN_BUTTON_ACTION = 218,
//		E_MAIN_BUTTON_PET = 219,
//		E_MAIN_BUTTON_MESSENGER = 220,
//		E_TEXT_VIEW

}
