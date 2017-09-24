#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

void cUiTestScene::SetupSkillUi(void)
{
	//��ų �Ӹ� â
	m_pSkillUiImageHead = cUIImageView::Create();
	m_pSkillUiImageHead->SetTexture("Texture/Ui/skillBaseHead1.png");
	m_pSkillUiImageHead->SetPosition(680, 20);
	m_pSkillUiImageHead->m_Alpha = 200;
	m_pSkillUi = m_pSkillUiImageHead;
	//�巡�� ��ư
	m_pSkillUiMoveing = cUIButton::Create();
	m_pSkillUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pSkillUiMoveing->SetPosition(0, 0);
	m_pSkillUiMoveing->SetDelegate(this);
	m_pSkillUiMoveing->m_Alpha = 0;
	m_pSkillUiMoveing->SetTag(E_SKILL_MOVE);
	m_pSkillUi->AddChild(m_pSkillUiMoveing);
	//��ų â ���̽�
	m_pSkillUiImage = cUIButton::Create();
	m_pSkillUiImage->SetTexture("Texture/Ui/Base.png"
	, "Texture/Ui/Base.png", "Texture/Ui/Base.png");
	m_pSkillUiImage->SetPosition(2, 47);
	m_pSkillUiImage->SetDelegate(this);
	m_pSkillUiImage->m_Alpha = 180;
	m_pSkillUiImage->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSkillUiImage);

}