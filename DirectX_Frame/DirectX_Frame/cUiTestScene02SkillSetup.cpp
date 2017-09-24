#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

void cUiTestScene::SetupSkillUi(void)
{
	//스킬 머리 창
	m_pSkillUiImageHead = cUIImageView::Create();
	m_pSkillUiImageHead->SetTexture("Texture/Ui/skillBaseHead1.png");
	m_pSkillUiImageHead->SetPosition(680, 20);
	m_pSkillUiImageHead->m_Alpha = 200;
	m_pSkillUi = m_pSkillUiImageHead;
	//드래그 버튼
	m_pSkillUiMoveing = cUIButton::Create();
	m_pSkillUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pSkillUiMoveing->SetPosition(0, 0);
	m_pSkillUiMoveing->SetDelegate(this);
	m_pSkillUiMoveing->m_Alpha = 0;
	m_pSkillUiMoveing->SetTag(E_SKILL_MOVE);
	m_pSkillUi->AddChild(m_pSkillUiMoveing);
	//스킬 창 베이스
	m_pSkillUiImage = cUIButton::Create();
	m_pSkillUiImage->SetTexture("Texture/Ui/Base.png"
	, "Texture/Ui/Base.png", "Texture/Ui/Base.png");
	m_pSkillUiImage->SetPosition(2, 47);
	m_pSkillUiImage->SetDelegate(this);
	m_pSkillUiImage->m_Alpha = 180;
	m_pSkillUiImage->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSkillUiImage);

}