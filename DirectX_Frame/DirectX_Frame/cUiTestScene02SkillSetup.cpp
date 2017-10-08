#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//플레이어
#include "cPlayer.h"
#include "cCamera.h"
//이미지
#include "cImage.h"


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
	m_pSkillUiImage->SetTexture("Texture/Ui/Base2.png"
	, "Texture/Ui/Base2.png", "Texture/Ui/Base2.png");
	m_pSkillUiImage->SetPosition(2, 47);
	m_pSkillUiImage->SetDelegate(this);
	m_pSkillUiImage->m_Alpha = 180;
	m_pSkillUiImage->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSkillUiImage);
	//택스트
	m_pSkillUiText = cUITextView::Create();
	m_pSkillUiText->SetText("스킬");
	m_pSkillUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pSkillUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pSkillUiText->SetSize(ST_SIZE(200, 100));
	m_pSkillUiText->SetPosition(-40, -30);
	m_pSkillUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pSkillUiText->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSkillUiText);
	//닫기 버튼
	m_pSkillCloseButton = cUIButton::Create();
	m_pSkillCloseButton->SetTexture("Texture/Ui/button_close_up.png"
		, "Texture/Ui/button_close_over.png", "Texture/Ui/button_close_up.png");
	m_pSkillCloseButton->SetPosition(290, 10);
	m_pSkillCloseButton->SetDelegate(this);
	m_pSkillCloseButton->SetTag(E_BUTTON_SKILL_CLOSE);
	m_pSkillCloseButton->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillCloseButton);

	//보유 스킬
//	cUIButton* pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/skillDefenseUi.png"
//		, "Texture/Ui/skillDefenseUi.png", "Texture/Ui/skillDefenseUi.png");
//	pHaveSkill->SetPosition(10, 60);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(pHaveSkill);

	cUIButton* pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/skillSmashUi.png"
		, "Texture/Ui/skillSmashUi.png", "Texture/Ui/skillSmashUi.png");
	pHaveSkill->SetPosition(10, 60);   //10, 110
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(pHaveSkill);

	pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/skillCounterUi.png"
		, "Texture/Ui/skillCounterUi.png", "Texture/Ui/skillCounterUi.png");
	pHaveSkill->SetPosition(10, 110); //10, 160
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(pHaveSkill);

//	pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/skillDownAttackUi.png"
//		, "Texture/Ui/skillDownAttackUi.png", "Texture/Ui/skillDownAttackUi.png");
//	pHaveSkill->SetPosition(10, 210);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(pHaveSkill);

//	pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/skillWindmillUi.png"
//		, "Texture/Ui/skillWindmillUi.png", "Texture/Ui/skillWindmillUi.png");
//	pHaveSkill->SetPosition(10, 260);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(pHaveSkill);

	pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/skillCombatUi.png"
		, "Texture/Ui/skillCombatUi.png", "Texture/Ui/skillCombatUi.png");
	pHaveSkill->SetPosition(10, 160);  //10, 310
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(pHaveSkill);

	//옆버튼들
	//페시브 표시(안씀) AP로 변경
	pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/APbuttonUp6542.png"
		, "Texture/Ui/APbuttonUp6542.png", "Texture/Ui/APbuttonDown6542.png");
	pHaveSkill->SetPosition(180, 160);  //100, 310 
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_USE_COMBAT);
	m_pSkillUi->AddChild(pHaveSkill);

	//사용 여부 버튼 (ap수련으로 변경)
//	pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/buttonUp6542Use.png"
//		, "Texture/Ui/buttonUp6542Use.png", "Texture/Ui/buttonDown6542Use.png");
//	pHaveSkill->SetPosition(180, 260);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_USE_WINDMILL);
//	m_pSkillUi->AddChild(pHaveSkill);

//	pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/buttonUp6542Use.png"
//		, "Texture/Ui/buttonUp6542Use.png", "Texture/Ui/buttonDown6542Use.png");
//	pHaveSkill->SetPosition(180, 210);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_USE_DOWNATTACK);
//	m_pSkillUi->AddChild(pHaveSkill);

	pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/APbuttonUp6542.png"
		, "Texture/Ui/APbuttonUp6542.png", "Texture/Ui/APbuttonDown6542.png");
	pHaveSkill->SetPosition(180, 110);
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_USE_COUNTER);
	m_pSkillUi->AddChild(pHaveSkill);

	pHaveSkill = cUIButton::Create();
	pHaveSkill->SetTexture("Texture/Ui/APbuttonUp6542.png"
		, "Texture/Ui/APbuttonUp6542.png", "Texture/Ui/APbuttonDown6542.png");
	pHaveSkill->SetPosition(180, 60);
	pHaveSkill->SetDelegate(this);
	pHaveSkill->SetTag(E_BUTTON_USE_SMASH);
	m_pSkillUi->AddChild(pHaveSkill);

//	pHaveSkill = cUIButton::Create();
//	pHaveSkill->SetTexture("Texture/Ui/buttonUp6542Use.png"
//		, "Texture/Ui/buttonUp6542Use.png", "Texture/Ui/buttonDown6542Use.png");
//	pHaveSkill->SetPosition(180, 60);
//	pHaveSkill->SetDelegate(this);
//	pHaveSkill->SetTag(E_BUTTON_USE_DEFENSE);
//	m_pSkillUi->AddChild(pHaveSkill);

	//스킬 경험치 이미지
	//토탈 빈칸
	m_pSkillExpMax = cUIImageViewTemp::Create();
	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
	m_pSkillExpMax->SetPosition(255, 90);
	m_pSkillExpMax->SetRectSize();
	//m_pSkillExpMax->m_rc.right = 50.0f;
	m_pSkillExpMax->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillExpMax);

	m_pSkillExpMax = cUIImageViewTemp::Create();
	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
	m_pSkillExpMax->SetPosition(255, 140);
	m_pSkillExpMax->SetRectSize();
	//m_pSkillExpMax->m_rc.right = 50.0f;
	m_pSkillExpMax->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillExpMax);

	m_pSkillExpMax = cUIImageViewTemp::Create();
	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
	m_pSkillExpMax->SetPosition(255, 190);
	m_pSkillExpMax->SetRectSize();
	//m_pSkillExpMax->m_rc.right = 50.0f;
	m_pSkillExpMax->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillExpMax);

//	m_pSkillExpMax = cUIImageViewTemp::Create();
//	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
//	m_pSkillExpMax->SetPosition(255, 240);
//	m_pSkillExpMax->SetRectSize();
//	//m_pSkillExpMax->m_rc.right = 50.0f;
//	m_pSkillExpMax->m_Alpha = 180;
//	m_pSkillUi->AddChild(m_pSkillExpMax);
//
//	m_pSkillExpMax = cUIImageViewTemp::Create();
//	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
//	m_pSkillExpMax->SetPosition(255, 290);
//	m_pSkillExpMax->SetRectSize();
//	//m_pSkillExpMax->m_rc.right = 50.0f;
//	m_pSkillExpMax->m_Alpha = 180;
//	m_pSkillUi->AddChild(m_pSkillExpMax);
//
//	m_pSkillExpMax = cUIImageViewTemp::Create();
//	m_pSkillExpMax->SetTexture("Texture/Ui/ExpBarE2.png");
//	m_pSkillExpMax->SetPosition(255, 340);
//	m_pSkillExpMax->SetRectSize();
//	//m_pSkillExpMax->m_rc.right = 50.0f;
//	m_pSkillExpMax->m_Alpha = 180;
//	m_pSkillUi->AddChild(m_pSkillExpMax);

	//가변 바
	//디펜스
//	m_pSkillExpDefense = cUIImageViewTemp::Create();
//	m_pSkillExpDefense->SetTexture("Texture/Ui/ExpBar2.png");
//	m_pSkillExpDefense->SetPosition(255, 90);
//	m_pSkillExpDefense->SetRectSize();
//	m_pSkillExpDefense->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefenseEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefenseEXPMax()) * m_pSkillExpDefense->stImageInfo.Width;
//	m_pSkillExpDefense->m_Alpha = 220;
//	m_pSkillUi->AddChild(m_pSkillExpDefense);
	//스메시
	m_pSkillExpSmash = cUIImageViewTemp::Create();
	m_pSkillExpSmash->SetTexture("Texture/Ui/ExpBar2.png");
	m_pSkillExpSmash->SetPosition(255, 90); //255, 140
	m_pSkillExpSmash->SetRectSize();
	m_pSkillExpSmash->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashEXPMax()) * m_pSkillExpSmash->stImageInfo.Width;
	m_pSkillExpSmash->m_Alpha = 220;
	m_pSkillUi->AddChild(m_pSkillExpSmash);
	//카운터
	m_pSkillExpCounter = cUIImageViewTemp::Create();
	m_pSkillExpCounter->SetTexture("Texture/Ui/ExpBar2.png");
	m_pSkillExpCounter->SetPosition(255, 140); //255, 190
	m_pSkillExpCounter->SetRectSize();
	m_pSkillExpCounter->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterEXPMax()) * m_pSkillExpCounter->stImageInfo.Width;
	m_pSkillExpCounter->m_Alpha = 220;
	m_pSkillUi->AddChild(m_pSkillExpCounter);
	//다운어택
//	m_pSkillExpDownAttack = cUIImageViewTemp::Create();
//	m_pSkillExpDownAttack->SetTexture("Texture/Ui/ExpBar2.png");
//	m_pSkillExpDownAttack->SetPosition(255, 240);
//	m_pSkillExpDownAttack->SetRectSize();
//	m_pSkillExpDownAttack->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDownAttackEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDownAttackEXPMax()) * m_pSkillExpDownAttack->stImageInfo.Width;
//	m_pSkillExpDownAttack->m_Alpha = 220;
//	m_pSkillUi->AddChild(m_pSkillExpDownAttack);
	//윈드밀
//	m_pSkillExpWindmill = cUIImageViewTemp::Create();
//	m_pSkillExpWindmill->SetTexture("Texture/Ui/ExpBar2.png");
//	m_pSkillExpWindmill->SetPosition(255, 290);
//	m_pSkillExpWindmill->SetRectSize();
//	m_pSkillExpWindmill->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWindmillEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWindmillEXPMax()) * m_pSkillExpWindmill->stImageInfo.Width;
//	m_pSkillExpWindmill->m_Alpha = 220;
//	m_pSkillUi->AddChild(m_pSkillExpWindmill);
	//컴뱃 마스터리
	m_pSkillExpCombat = cUIImageViewTemp::Create();
	m_pSkillExpCombat->SetTexture("Texture/Ui/ExpBar2.png");
	m_pSkillExpCombat->SetPosition(255, 190);  //255, 340
	m_pSkillExpCombat->SetRectSize();
	m_pSkillExpCombat->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatEXPMax()) * m_pSkillExpCombat->stImageInfo.Width;
	m_pSkillExpCombat->m_Alpha = 220;
	m_pSkillUi->AddChild(m_pSkillExpCombat);

	//레벨 택스트
//	char szSKillLevelSmash[64] = { '\0', };
//	sprintf_s(szSKillLevelSmash, "랭크 F");

//	m_pSKillLevelDefense = cUITextView::Create();
//	m_pSKillLevelDefense->SetText("랭크 F");
//	m_pSKillLevelDefense->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
//	m_pSKillLevelDefense->SetColor(D3DCOLOR_XRGB(255, 255, 255));
//	m_pSKillLevelDefense->SetSize(ST_SIZE(30, 40));
//	m_pSKillLevelDefense->SetPosition(260, 60);
//	m_pSKillLevelDefense->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	m_pSKillLevelDefense->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(m_pSKillLevelDefense);

	m_pSKillLevelSmash = cUITextView::Create();
	m_pSKillLevelSmash->SetText("랭크 F");
	m_pSKillLevelSmash->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pSKillLevelSmash->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pSKillLevelSmash->SetSize(ST_SIZE(30, 40));
	m_pSKillLevelSmash->SetPosition(260, 60);   //260,110
	m_pSKillLevelSmash->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pSKillLevelSmash->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSKillLevelSmash);

	m_pSKillLevelCounter = cUITextView::Create();
	m_pSKillLevelCounter->SetText("랭크 F");
	m_pSKillLevelCounter->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pSKillLevelCounter->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pSKillLevelCounter->SetSize(ST_SIZE(30, 40));
	m_pSKillLevelCounter->SetPosition(260, 110); //260 160
	m_pSKillLevelCounter->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pSKillLevelCounter->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSKillLevelCounter);

//	m_pSKillLevelDownAttack = cUITextView::Create();
//	m_pSKillLevelDownAttack->SetText("랭크 F");
//	m_pSKillLevelDownAttack->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
//	m_pSKillLevelDownAttack->SetColor(D3DCOLOR_XRGB(255, 255, 255));
//	m_pSKillLevelDownAttack->SetSize(ST_SIZE(30, 40));
//	m_pSKillLevelDownAttack->SetPosition(260, 210);
//	m_pSKillLevelDownAttack->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	m_pSKillLevelDownAttack->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(m_pSKillLevelDownAttack);

//	m_pSKillLevelWindmill = cUITextView::Create();
//	m_pSKillLevelWindmill->SetText("랭크 F");
//	m_pSKillLevelWindmill->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
//	m_pSKillLevelWindmill->SetColor(D3DCOLOR_XRGB(255, 255, 255));
//	m_pSKillLevelWindmill->SetSize(ST_SIZE(30, 40));
//	m_pSKillLevelWindmill->SetPosition(260, 260);
//	m_pSKillLevelWindmill->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	m_pSKillLevelWindmill->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(m_pSKillLevelWindmill);

	m_pSKillLevelCombat = cUITextView::Create();
	m_pSKillLevelCombat->SetText("랭크 F");
	m_pSKillLevelCombat->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pSKillLevelCombat->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pSKillLevelCombat->SetSize(ST_SIZE(30, 40));
	m_pSKillLevelCombat->SetPosition(260, 160);  //260, 310
	m_pSKillLevelCombat->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pSKillLevelCombat->SetTag(E_BUTTON_NONE);
	m_pSkillUi->AddChild(m_pSKillLevelCombat);


	//예시
	//= ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
	//	/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pHpImage->stImageInfo.Width;
//	m_pHpImage = cUIImageViewTemp::Create();
//	m_pHpImage->SetTexture("Texture/Ui/HP.png");
//	m_pHpImage->SetPosition(InfoHPx, InfoHPy);
//	m_pHpImage->SetRectSize();
//	m_pHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pHpImage->stImageInfo.Width;
//	m_pHpImage->m_Alpha = 220;
//	m_pInfoUi->AddChild(m_pHpImage);

//	//택스트(사용하기)
//	cUITextView* pTextSkillUi = cUITextView::Create();
//	pTextSkillUi->SetText("사용하기");
//	pTextSkillUi->SetFontType(g_pFontManager->E_INBUTTON);
//	pTextSkillUi->SetColor(D3DCOLOR_XRGB(255, 255, 255));
//	pTextSkillUi->SetSize(ST_SIZE(70, 40));
//	pTextSkillUi->SetPosition(180, 50);
//	pTextSkillUi->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	pTextSkillUi->SetTag(E_BUTTON_NONE);
//	m_pSkillUi->AddChild(pTextSkillUi);

	//퀵 설정
	m_pUiQuickSiot1 = cUIButton::Create();
	m_pUiQuickSiot1->SetTexture("Texture/Ui/skillSmash.png"
		, "Texture/Ui/skillSmash.png", "Texture/Ui/skillSmash.png");
	m_pUiQuickSiot1->SetPosition(10, 10);
	m_pUiQuickSiot1->SetDelegate(this);
	m_pUiQuickSiot1->SetTag(E_BUTTON_QUICK_01);
//	m_pUiQuickSiot1->m_Alpha = 220;
	m_pUiQuickSiot = m_pUiQuickSiot1;
	
	//택스트
	cUITextView* pUiQuickText = cUITextView::Create();
	pUiQuickText->SetText("1");
	pUiQuickText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	pUiQuickText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pUiQuickText->SetSize(ST_SIZE(30, 40));
	pUiQuickText->SetPosition(-7, -8);
	pUiQuickText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pUiQuickText->SetTag(E_BUTTON_NONE);
	m_pUiQuickSiot->AddChild(pUiQuickText);

	m_pUiQuickSiot2 = cUIButton::Create();
	m_pUiQuickSiot2->SetTexture("Texture/Ui/skillCounter.png"
		, "Texture/Ui/skillCounter.png", "Texture/Ui/skillCounter.png");
	m_pUiQuickSiot2->SetPosition(50, 0);
	m_pUiQuickSiot2->SetDelegate(this);
	m_pUiQuickSiot2->SetTag(E_BUTTON_QUICK_02);
	m_pUiQuickSiot->AddChild(m_pUiQuickSiot2);

	//택스트
	pUiQuickText = cUITextView::Create();
	pUiQuickText->SetText("2");
	pUiQuickText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	pUiQuickText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pUiQuickText->SetSize(ST_SIZE(30, 40));
	pUiQuickText->SetPosition(-7 + 50, -8);
	pUiQuickText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pUiQuickText->SetTag(E_BUTTON_NONE);
	m_pUiQuickSiot->AddChild(pUiQuickText);

	m_pUiQuickSiot3 = cUIButton::Create();
	m_pUiQuickSiot3->SetTexture("Texture/Ui/QuickSiot.png"
		, "Texture/Ui/QuickSiot.png", "Texture/Ui/QuickSiot.png");
	m_pUiQuickSiot3->SetPosition(100, 0);
	m_pUiQuickSiot3->SetDelegate(this);
	m_pUiQuickSiot3->SetTag(E_BUTTON_QUICK_03);
	m_pUiQuickSiot->AddChild(m_pUiQuickSiot3);
	
	//택스트
	pUiQuickText = cUITextView::Create();
	pUiQuickText->SetText("3");
	pUiQuickText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	pUiQuickText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pUiQuickText->SetSize(ST_SIZE(30, 40));
	pUiQuickText->SetPosition(-7 + 100, -8);
	pUiQuickText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pUiQuickText->SetTag(E_BUTTON_NONE);
	m_pUiQuickSiot->AddChild(pUiQuickText);

	m_pUiQuickSiot4 = cUIButton::Create();
	m_pUiQuickSiot4->SetTexture("Texture/Ui/QuickSiot.png"
		, "Texture/Ui/QuickSiot.png", "Texture/Ui/QuickSiot.png");
	m_pUiQuickSiot4->SetPosition(150, 0);
	m_pUiQuickSiot4->SetDelegate(this);
	m_pUiQuickSiot4->SetTag(E_BUTTON_QUICK_04);
	m_pUiQuickSiot->AddChild(m_pUiQuickSiot4);

	//택스트
	pUiQuickText = cUITextView::Create();
	pUiQuickText->SetText("4");
	pUiQuickText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	pUiQuickText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pUiQuickText->SetSize(ST_SIZE(30, 40));
	pUiQuickText->SetPosition(-7 + 150, -8);
	pUiQuickText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pUiQuickText->SetTag(E_BUTTON_NONE);
	m_pUiQuickSiot->AddChild(pUiQuickText);

	m_pUiQuickSiot5 = cUIButton::Create();
	m_pUiQuickSiot5->SetTexture("Texture/Ui/QuickSiot.png"
		, "Texture/Ui/QuickSiot.png", "Texture/Ui/QuickSiot.png");
	m_pUiQuickSiot5->SetPosition(200, 0);
	m_pUiQuickSiot5->SetDelegate(this);
	m_pUiQuickSiot5->SetTag(E_BUTTON_QUICK_05);
	m_pUiQuickSiot->AddChild(m_pUiQuickSiot5);

	//택스트
	pUiQuickText = cUITextView::Create();
	pUiQuickText->SetText("5");
	pUiQuickText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	pUiQuickText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pUiQuickText->SetSize(ST_SIZE(30, 40));
	pUiQuickText->SetPosition(-7 + 200, -8);
	pUiQuickText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pUiQuickText->SetTag(E_BUTTON_NONE);
	m_pUiQuickSiot->AddChild(pUiQuickText);


}

void cUiTestScene::UpdateSkillUi(void)
{
	//이미지 업데이트
	//디펜스
//	m_pSkillExpDefense->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefenseEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefenseEXPMax()) * m_pSkillExpDefense->stImageInfo.Width;
//	if (m_pSkillExpDefense->m_rc.right >= m_pSkillExpDefense->stImageInfo.Width) m_pSkillExpDefense->m_rc.right = m_pSkillExpDefense->stImageInfo.Width;
//	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefenseEXP() <= 0) m_pSkillExpDefense->m_rc.right = 0.5f;

	//스메시
	m_pSkillExpSmash->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashEXPMax()) * m_pSkillExpSmash->stImageInfo.Width;
	if (m_pSkillExpSmash->m_rc.right >= m_pSkillExpSmash->stImageInfo.Width) m_pSkillExpSmash->m_rc.right = m_pSkillExpSmash->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashEXP() <= 0) m_pSkillExpSmash->m_rc.right = 0.5f;

	//카운터
	m_pSkillExpCounter->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterEXPMax()) * m_pSkillExpCounter->stImageInfo.Width;
	if (m_pSkillExpCounter->m_rc.right >= m_pSkillExpCounter->stImageInfo.Width) m_pSkillExpCounter->m_rc.right = m_pSkillExpCounter->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterEXP() <= 0) m_pSkillExpCounter->m_rc.right = 0.5f;

	//다운어택
//	m_pSkillExpDownAttack->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDownAttackEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDownAttackEXPMax()) * m_pSkillExpDownAttack->stImageInfo.Width;
//	if (m_pSkillExpDownAttack->m_rc.right >= m_pSkillExpDownAttack->stImageInfo.Width) m_pSkillExpDownAttack->m_rc.right = m_pSkillExpDownAttack->stImageInfo.Width;
//	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDownAttackEXP() <= 0) m_pSkillExpDownAttack->m_rc.right = 0.5f;

	//윈드밀
//	m_pSkillExpWindmill->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWindmillEXP()
//		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWindmillEXPMax()) * m_pSkillExpWindmill->stImageInfo.Width;
//	if (m_pSkillExpWindmill->m_rc.right >= m_pSkillExpWindmill->stImageInfo.Width) m_pSkillExpWindmill->m_rc.right = m_pSkillExpWindmill->stImageInfo.Width;
//	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWindmillEXP() <= 0) m_pSkillExpWindmill->m_rc.right = 0.5f;

	//컴뱃 마스터리
	m_pSkillExpCombat->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatEXPMax()) * m_pSkillExpCombat->stImageInfo.Width;
	if (m_pSkillExpCombat->m_rc.right >= m_pSkillExpCombat->stImageInfo.Width) m_pSkillExpCombat->m_rc.right = m_pSkillExpCombat->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatEXP() <= 0) m_pSkillExpCombat->m_rc.right = 0.5f;


	//랭크 변동
	//스메시
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 1)
	{
		m_pSKillLevelSmash->SetText("랭크 F");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 2)
	{
		m_pSKillLevelSmash->SetText("랭크 E");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 3)
	{
		m_pSKillLevelSmash->SetText("랭크 D");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 4)
	{
		m_pSKillLevelSmash->SetText("랭크 C");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 5)
	{
		m_pSKillLevelSmash->SetText("랭크 B");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetSmashLevel() == 6)
	{
		m_pSKillLevelSmash->SetText("랭크 A");
	}
	//카운터
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 1)
	{
		m_pSKillLevelCounter->SetText("랭크 F");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 2)
	{
		m_pSKillLevelCounter->SetText("랭크 E");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 3)
	{
		m_pSKillLevelCounter->SetText("랭크 D");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 4)
	{
		m_pSKillLevelCounter->SetText("랭크 C");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 5)
	{
		m_pSKillLevelCounter->SetText("랭크 B");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCounterLevel() == 6)
	{
		m_pSKillLevelCounter->SetText("랭크 A");
	}
	//컴뱃 마스터리
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 1)
	{
		m_pSKillLevelCombat->SetText("랭크 F");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 2)
	{
		m_pSKillLevelCombat->SetText("랭크 E");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 3)
	{
		m_pSKillLevelCombat->SetText("랭크 D");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 4)
	{
		m_pSKillLevelCombat->SetText("랭크 C");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 5)
	{
		m_pSKillLevelCombat->SetText("랭크 B");
	}
	else if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCombatLevel() == 6)
	{
		m_pSKillLevelCombat->SetText("랭크 A");
	}
}