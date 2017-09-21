#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

void cUiTestScene::SetupBaseButton(void)
{
	//테스트용 메인버튼들
	m_pMainRootImageView = cUIImageView::Create();
	m_pMainRootImageView->SetTexture("Texture/Ui/TestRoot2.png");
	m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pMainRootImageView->m_Alpha = 200;
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

	m_pInfoButton = cUIButton::Create();
	m_pInfoButton->SetTexture("Texture/Ui/player_info_button_up.png",
		"Texture/Ui/player_info_button_over.png",
		"Texture/Ui/player_info_button_down.png");
	m_pInfoButton->SetPosition(mainButtonSrart, mainButtonH);
	m_pInfoButton->SetDelegate(this);
	m_pInfoButton->SetTag(E_MAIN_BUTTON_PLAYER_INFO);
	m_pUiRoot->AddChild(m_pInfoButton);

	m_pSkillButton = cUIButton::Create();
	m_pSkillButton->SetTexture("Texture/Ui/player_sikill_button_up.png",
		"Texture/Ui/player_sikill_button_over.png",
		"Texture/Ui/player_sikill_button_down.png");
	m_pSkillButton->SetPosition(mainButtonSrart + mainButtoninterval, mainButtonH);
	m_pSkillButton->SetDelegate(this);
	m_pSkillButton->SetTag(E_MAIN_BUTTON_SKILL);
	m_pUiRoot->AddChild(m_pSkillButton);

	m_pQuestButton = cUIButton::Create();
	m_pQuestButton->SetTexture("Texture/Ui/player_quest_button_up.png",
		"Texture/Ui/player_quest_button_over.png",
		"Texture/Ui/player_quest_button_down.png");
	m_pQuestButton->SetPosition(mainButtonSrart + mainButtoninterval * 2, mainButtonH);
	m_pQuestButton->SetDelegate(this);
	m_pQuestButton->SetTag(E_MAIN_BUTTON_QUEST);
	m_pUiRoot->AddChild(m_pQuestButton);

	m_pInventoryButton = cUIButton::Create();
	m_pInventoryButton->SetTexture("Texture/Ui/player_inventory_button_up.png",
		"Texture/Ui/player_inventory_button_over.png",
		"Texture/Ui/player_inventory_button_down.png");
	m_pInventoryButton->SetPosition(mainButtonSrart + mainButtoninterval * 3, mainButtonH);
	m_pInventoryButton->SetDelegate(this);
	m_pInventoryButton->SetTag(E_MAIN_BUTTON_INVENTORY);
	m_pUiRoot->AddChild(m_pInventoryButton);

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
}