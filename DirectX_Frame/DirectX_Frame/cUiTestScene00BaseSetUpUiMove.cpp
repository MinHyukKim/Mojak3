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

void cUiTestScene::SetupBaseButton(void)
{

	//테스트용 메인버튼들mainUiLocalX, mainUiLocalY
	m_pMainRootImageView = cUIImageView::Create();
	m_pMainRootImageView->SetTexture("Texture/Ui/TestRoot2.png");
	m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height);
	m_pMainRootImageView->m_Alpha = 200;
	m_pUiRoot = m_pMainRootImageView;

	m_pMainRootImageViewMove = cUIButton::Create();
	m_pMainRootImageViewMove->SetTexture("Texture/Ui/TestRoot2.png",
		"Texture/Ui/TestRoot2.png",
		"Texture/Ui/TestRoot2.png");
	m_pMainRootImageViewMove->m_Alpha = 0;
	m_pMainRootImageViewMove->SetPosition(0, 0);
	m_pMainRootImageViewMove->SetDelegate(this);
	m_pMainRootImageViewMove->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainRootImageViewMove);

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

	m_pMinButton = cUIButton::Create();
	m_pMinButton->SetTexture("Texture/Ui/button_min_up.png",
		"Texture/Ui/button_min_over.png",
		"Texture/Ui/button_min_up.png");
	m_pMinButton->SetPosition(mainButtonSrart + 190, mainButtonH + 26);
	m_pMinButton->SetDelegate(this);
	m_pMinButton->SetTag(E_MAIN_BUTTON_MIN);
	m_pUiRoot->AddChild(m_pMinButton);

	m_pMainMainButton = cUIButton::Create();
	m_pMainMainButton->SetTexture("Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-down.png");
	m_pMainMainButton->SetPosition(mainButtonSrart - 150, mainButtonH + 25);
	m_pMainMainButton->SetDelegate(this);
	m_pMainMainButton->SetTag(E_MAIN_BUTTON_MAIN);
	m_pUiRoot->AddChild(m_pMainMainButton);

	//게이지 이미지들
	//피통 이미지
	//최대
	m_pMainHpMaxImage = cUIImageViewTemp::Create();
	m_pMainHpMaxImage->SetTexture("Texture/Ui/HPmainE.png");
	m_pMainHpMaxImage->SetPosition(m_nMainHPx, m_nMainHPy);
	m_pMainHpMaxImage->SetRectSize();
	//m_pMainHpMaxImage->m_rc.right = 50.0f;
	m_pMainHpMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainHpMaxImage);
	//현재량
	m_pMainHpImage = cUIImageViewTemp::Create();
	m_pMainHpImage->SetTexture("Texture/Ui/HPmain.png");
	m_pMainHpImage->SetPosition(m_nMainHPx, m_nMainHPy);
	m_pMainHpImage->SetRectSize();
	m_pMainHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pMainHpImage->stImageInfo.Width;
	m_pMainHpImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainHpImage);
	//피통 택스트
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP());
	m_pMainHpText = cUITextView::Create();
	m_pMainHpText->SetText(szHP);
	m_pMainHpText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainHpText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainHpText->SetSize(ST_SIZE(100, 12));
	//m_pMainHpText->SetPosition(10, 150 - 7); //마비체
	m_pMainHpText->SetPosition(m_nMainHPx - 10, m_nMainHPy);   //나눔고딕
	m_pMainHpText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainHpText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainHpText);

	//마나통 이미지
	//최대
	m_pMainMpMaxImage = cUIImageViewTemp::Create();
	m_pMainMpMaxImage->SetTexture("Texture/Ui/MPmainE.png");
	m_pMainMpMaxImage->SetPosition(m_nMainMPx, m_nMainMPy);
	m_pMainMpMaxImage->SetRectSize();
	//m_pMainMpMaxImage->m_rc.right = 50.0f;
	m_pMainMpMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainMpMaxImage);
	//현재량
	m_pMainMpImage = cUIImageViewTemp::Create();
	m_pMainMpImage->SetTexture("Texture/Ui/MPmain.png");
	m_pMainMpImage->SetPosition(m_nMainMPx, m_nMainMPy);
	m_pMainMpImage->SetRectSize();
	m_pMainMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMainMpImage->stImageInfo.Width;
	m_pMainMpImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainMpImage);
	//마나 택스트
	char szMP[32] = { '\0', };
	sprintf_s(szMP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP());
	m_pMainMpText = cUITextView::Create();
	m_pMainMpText->SetText(szMP);
	m_pMainMpText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainMpText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainMpText->SetSize(ST_SIZE(100, 12));
	//m_pMainMpText->SetPosition(10, 150 - 7); //마비체
	m_pMainMpText->SetPosition(m_nMainMPx - 10, m_nMainMPy);   //나눔고딕
	m_pMainMpText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainMpText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainMpText);

	//스태미너 이미지
	//최대
	m_pMainStaminaMaxImage = cUIImageViewTemp::Create();
	m_pMainStaminaMaxImage->SetTexture("Texture/Ui/SPmainE.png");
	m_pMainStaminaMaxImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
	m_pMainStaminaMaxImage->SetRectSize();
	//m_pMainStaminaMaxImage->m_rc.right = 50.0f;
	m_pMainStaminaMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainStaminaMaxImage);
	//현재량
	m_pMainStaminaImage = cUIImageViewTemp::Create();
	m_pMainStaminaImage->SetTexture("Texture/Ui/SPmain.png");
	m_pMainStaminaImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
	m_pMainStaminaImage->SetRectSize();
	m_pMainStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pMainStaminaImage->stImageInfo.Width;
	m_pMainStaminaImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainStaminaImage);
	//스테미너 택스트
	char szStamina[32] = { '\0', };
	sprintf_s(szStamina, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina());
	m_pMainStaminaText = cUITextView::Create();
	m_pMainStaminaText->SetText(szStamina);
	m_pMainStaminaText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainStaminaText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainStaminaText->SetSize(ST_SIZE(100, 12));
	//m_pMainStaminaText->SetPosition(10, 150 - 7); //마비체
	m_pMainStaminaText->SetPosition(m_nMainStaminaX - 10, m_nMainStaminaY);   //나눔고딕
	m_pMainStaminaText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainStaminaText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainStaminaText);

	//경험지 게이지
	//최대
	m_pMainEXPMaxImage = cUIImageViewTemp::Create();
	m_pMainEXPMaxImage->SetTexture("Texture/Ui/EXPe1.png");
	m_pMainEXPMaxImage->SetPosition(m_nMainEXPx, m_nMainEXPy);
	m_pMainEXPMaxImage->SetRectSize();
	//m_pMainEXPMaxImage->m_rc.right = 50.0f;
	m_pMainEXPMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainEXPMaxImage);
	//현재량
	m_pMainEXPImage = cUIImageViewTemp::Create();
	m_pMainEXPImage->SetTexture("Texture/Ui/EXP1.png");
	m_pMainEXPImage->SetPosition(m_nMainEXPx, m_nMainEXPy);
	m_pMainEXPImage->SetRectSize();
	m_pMainEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pMainEXPImage->stImageInfo.Width;
	m_pMainEXPImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainEXPImage);

	//경험치 및 레벨 택스트
	char sEXP[64] = { '\0', };
	sprintf_s(sEXP, "%.1f %%"
		, (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() / g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * 100.0f);
	m_pMainEXPText = cUITextView::Create();
	m_pMainEXPText->SetText(sEXP);
	m_pMainEXPText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainEXPText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainEXPText->SetSize(ST_SIZE(120, 40));
	//m_pMainEXPText->SetPosition(-10, 280 - 7); //마비체
	m_pMainEXPText->SetPosition(315, 5);   //나눔고딕
	m_pMainEXPText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainEXPText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainEXPText);

	char sLv[64] = { '\0', };
	sprintf_s(sLv, "Lv %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetLevel());
	m_pMainLevelText = cUITextView::Create();
	m_pMainLevelText->SetText(sLv);
	m_pMainLevelText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainLevelText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainLevelText->SetSize(ST_SIZE(120, 40));
	//m_pMainLevelText->SetPosition(-10, 280 - 7); //마비체
	m_pMainLevelText->SetPosition(85, 5);   //나눔고딕
	m_pMainLevelText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainLevelText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainLevelText);

	//종료 관련
	m_pUiExitBackImage = cUIButton::Create();
	m_pUiExitBackImage->SetTexture("Texture/Ui/extiBack.png",
		"Texture/Ui/extiBack.png", "Texture/Ui/extiBack.png");
	m_pUiExitBackImage->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height - 40);
	m_pUiExitBackImage->SetDelegate(this);
	m_pUiExitBackImage->m_Alpha = 180;
	m_pUiExitBackImage->SetTag(E_BUTTON_NONE);
	m_pUiExit = m_pUiExitBackImage;

	m_pUiExitButton = cUIButton::Create();
	m_pUiExitButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pUiExitButton->SetPosition(15, 8);
	m_pUiExitButton->SetDelegate(this);
	m_pUiExitButton->m_Alpha = 200;
	m_pUiExitButton->SetTag(E_BUTTON_EXIT);
	m_pUiExit ->AddChild(m_pUiExitButton);

	//택스트
	m_pUiExitText = cUITextView::Create();
	m_pUiExitText->SetText("종료");
	m_pUiExitText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pUiExitText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pUiExitText->SetSize(ST_SIZE(80, 40));
	m_pUiExitText->SetPosition(5, -5);
	m_pUiExitText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pUiExitText->SetTag(E_TEXT_DIALOG);
	m_pUiExit->AddChild(m_pUiExitText);

}

void cUiTestScene::UpdateMainUi(void)
{
	//택스트
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP());
	m_pMainHpText->SetText(szHP);

	char szMP[32] = { '\0', };
	sprintf_s(szMP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP());
	m_pMainMpText->SetText(szMP);

	char szStamina[32] = { '\0', };
	sprintf_s(szStamina, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina());
	m_pMainStaminaText->SetText(szStamina);

	char sEXP[64] = { '\0', };
	sprintf_s(sEXP, "%.1f %%"
		, (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() / g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * 100.0f);
	m_pMainEXPText->SetText(sEXP);

	char sLv[64] = { '\0', };
	sprintf_s(sLv, "Lv %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetLevel());
	m_pMainLevelText->SetText(sLv);


	//게이지 업데이트
	//피통
	m_pMainHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pMainHpImage->stImageInfo.Width;
	//현재 피통이 최대량보다 많아질때
	if (m_pMainHpImage->m_rc.right >= m_pMainHpImage->stImageInfo.Width) m_pMainHpImage->m_rc.right = m_pMainHpImage->stImageInfo.Width;
	//현재 피통이 0보다 작아질때
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP() <= 0) m_pMainHpImage->m_rc.right = 1.0f;

	//마나통
	m_pMainMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMainMpImage->stImageInfo.Width;
	//현재 마나통이 최대량보다 많아질때
	if (m_pMainMpImage->m_rc.right >= m_pMainMpImage->stImageInfo.Width)  m_pMainMpImage->m_rc.right = m_pMainMpImage->stImageInfo.Width;
	//현재 마나통이 0보다 작아질때
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP() <= 0) m_pMainMpImage->m_rc.right = 1.0f;

	//스태미나 통
	m_pMainStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pMainStaminaImage->stImageInfo.Width;
	//현재 스태미나통이 최대량보다 많아질때
	if (m_pMainStaminaImage->m_rc.right >= m_pMainStaminaImage->stImageInfo.Width) m_pMainStaminaImage->m_rc.right = m_pMainStaminaImage->stImageInfo.Width;
	//현재 스태미나통이 0보다 작아질때
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina() <= 0) m_pMainStaminaImage->m_rc.right = 1.0f;

	//경험치
	m_pMainEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pMainEXPImage->stImageInfo.Width;
	if (m_pMainEXPImage->m_rc.right >= m_pMainEXPImage->stImageInfo.Width) m_pMainEXPImage->m_rc.right = m_pMainEXPImage->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() <= 0) m_pMainEXPImage->m_rc.right = 0.1f;


	//최소화
	//메인창 내리기
	if (m_isMainMin == true)
	{
		m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height + (m_pMainRootImageView->stImageInfo.Height / 2));
		m_pUiExitBackImage->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height - 40 + (m_pMainRootImageView->stImageInfo.Height / 2));
		m_pInfoButton->SetPosition(1000, 1000);
		m_pSkillButton->SetPosition(1000, 1000);
		m_pQuestButton->SetPosition(1000, 1000);
		m_pInventoryButton->SetPosition(1000, 1000);

		m_pMainHpMaxImage->SetPosition(m_nMainHPx, m_nMainHPy);
		m_pMainHpImage->SetPosition(m_nMainHPx, m_nMainHPy);
		m_pMainHpText->SetPosition(m_nMainHPx - 10, m_nMainHPy);

		m_pMainMpMaxImage->SetPosition(m_nMainMPx + 90, m_nMainHPy);
		m_pMainMpImage->SetPosition(m_nMainMPx + 90, m_nMainHPy);
		m_pMainMpText->SetPosition(m_nMainMPx + 80, m_nMainHPy);

		m_pMainStaminaMaxImage->SetPosition(m_nMainStaminaX + 180, m_nMainHPy);
		m_pMainStaminaImage->SetPosition(m_nMainStaminaX + 180, m_nMainHPy);
		m_pMainStaminaText->SetPosition(m_nMainStaminaX + 170, m_nMainHPy);

		m_pMinButton->SetTexture("Texture/Ui/button_max_up.png",
			"Texture/Ui/button_max_over.png",
			"Texture/Ui/button_max_up.png");
	}
	else
	{
		//제자리
		m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height);
		m_pUiExitBackImage->SetPosition(mainUiLocalX, mainUiLocalY - m_pMainRootImageView->stImageInfo.Height - 40);

		m_pInfoButton->SetPosition(mainButtonSrart, mainButtonH);
		m_pSkillButton->SetPosition(mainButtonSrart + mainButtoninterval, mainButtonH);
		m_pQuestButton->SetPosition(mainButtonSrart + mainButtoninterval * 2, mainButtonH);
		m_pInventoryButton->SetPosition(mainButtonSrart + mainButtoninterval * 3, mainButtonH);

		m_pMainHpMaxImage->SetPosition(m_nMainHPx, m_nMainHPy);
		m_pMainHpImage->SetPosition(m_nMainHPx, m_nMainHPy);
		m_pMainHpText->SetPosition(m_nMainHPx - 10, m_nMainHPy);

		m_pMainMpMaxImage->SetPosition(m_nMainMPx, m_nMainMPy);
		m_pMainMpImage->SetPosition(m_nMainMPx, m_nMainMPy);
		m_pMainMpText->SetPosition(m_nMainMPx - 10, m_nMainMPy);

		m_pMainStaminaMaxImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
		m_pMainStaminaImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
		m_pMainStaminaText->SetPosition(m_nMainStaminaX - 10, m_nMainStaminaY);

		m_pMinButton->SetTexture("Texture/Ui/button_min_up.png",
			"Texture/Ui/button_min_over.png",
			"Texture/Ui/button_min_up.png");
	}
}

void cUiTestScene::MoveUiWindow(void)
{
	//무빙 관련
	POINT ptMouse = m_ptMouse;				//이전 좌표 저장

	GetCursorPos(&m_ptMouse);				//마우스 좌표(맴버변수 포인터)
	ScreenToClient(g_hWnd, &m_ptMouse);		//마우스 좌표(맴버변수 포인터)

	int nDeltaX = (m_ptMouse.x - ptMouse.x); //현재 좌표 - 이전 좌표 (음직인 양)
	int nDeltaY = (m_ptMouse.y - ptMouse.y); //현재 좌표 - 이전 좌표 (음직인 양)

	//인벤 창 무빙
//	if(m_pInventoryUiMoveing->GetButtonStatus() == 1)
	if (m_pInventoryUiMoveing->isOver)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON)
			&& m_pInfoUiMoveing->isClick == false
			&& m_pSkillUiMoveing->isClick == false
			&& m_pQuestUiMoveing->isClick == false
			//&& m_pInfoCloseButton->isOver == false
			&& m_pInventoryCloseButton->isOver == false
			//&& m_pSkillCloseButton->isOver == false
			/*&& m_pQuestCloseButton->isOver == false*/)
		{
			m_pInventoryUiMoveing->isClick = true;
			invX = m_pInventoryUiImageHead->GetPosition().x + nDeltaX; //잡은 윈도우 창에서 음직인 양만큼 더해준다
			invY = m_pInventoryUiImageHead->GetPosition().y + nDeltaY;

			m_pInventoryUiImageHead->SetPosition(invX, invY);
		}
		else m_pInventoryUiMoveing->isClick = false;
	}
	else if (m_pInventoryUiMoveing->isClick == true)		//클릭 상태에서 음직임
	{
		invX = m_pInventoryUiImageHead->GetPosition().x + nDeltaX; //잡은 윈도우 창에서 음직인 양만큼 더해준다
		invY = m_pInventoryUiImageHead->GetPosition().y + nDeltaY;

		m_pInventoryUiImageHead->SetPosition(invX, invY);
	}

	//정보 창 무빙
	if (m_pInfoUiMoveing->isOver)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON)
			&& m_pInventoryUiMoveing->isClick == false
			&& m_pSkillUiMoveing->isClick == false
			&& m_pQuestUiMoveing->isClick == false
			&& m_pInfoCloseButton->isOver == false
			//&& m_pInventoryCloseButton->isOver == false
			//&& m_pSkillCloseButton->isOver == false
			/*&& m_pQuestCloseButton->isOver == false*/)
		{
			m_pInfoUiMoveing->isClick = true;
			infoX = m_pInfoUiImageHead->GetPosition().x + nDeltaX;
			infoY = m_pInfoUiImageHead->GetPosition().y + nDeltaY;
			
			m_pInfoUiImageHead->SetPosition(infoX, infoY);
		}
		else m_pInfoUiMoveing->isClick = false;
	}
	else if (m_pInfoUiMoveing->isClick)
	{
		infoX = m_pInfoUiImageHead->GetPosition().x + nDeltaX;
		infoY = m_pInfoUiImageHead->GetPosition().y + nDeltaY;

		m_pInfoUiImageHead->SetPosition(infoX, infoY);
	}

	//스킬 창 무빙
	if (m_pSkillUiMoveing->isOver)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON)
			&& m_pInventoryUiMoveing->isClick == false
			&& m_pInfoUiMoveing->isClick == false
			&& m_pQuestUiMoveing->isClick == false
			//&& m_pInfoCloseButton->isOver == false
			//&& m_pInventoryCloseButton->isOver == false
			&& m_pSkillCloseButton->isOver == false
			/*&& m_pQuestCloseButton->isOver == false*/)
		{
			m_pSkillUiMoveing->isClick = true;
			skillX = m_pSkillUiImageHead->GetPosition().x + nDeltaX;
			skillY = m_pSkillUiImageHead->GetPosition().y + nDeltaY;

			m_pSkillUiImageHead->SetPosition(skillX, skillY);
		}
		else m_pSkillUiMoveing->isClick = false;
	}
	else if (m_pSkillUiMoveing->isClick)
	{
		skillX = m_pSkillUiImageHead->GetPosition().x + nDeltaX;
		skillY = m_pSkillUiImageHead->GetPosition().y + nDeltaY;

		m_pSkillUiImageHead->SetPosition(skillX, skillY);
	}
	//퀘 창 무빙
	if (m_pQuestUiMoveing->isOver)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON)
			&& m_pInventoryUiMoveing->isClick == false
			&& m_pSkillUiMoveing->isClick == false
			&& m_pInfoUiMoveing->isClick == false
			//&& m_pInfoCloseButton->isOver == false
			//&& m_pInventoryCloseButton->isOver == false
			//&& m_pSkillCloseButton->isOver == false
			&& m_pQuestCloseButton->isOver == false)
		{
			m_pQuestUiMoveing->isClick = true;
			queX = m_pQuestUiImageHead->GetPosition().x + nDeltaX;
			queY = m_pQuestUiImageHead->GetPosition().y + nDeltaY;

			m_pQuestUiImageHead->SetPosition(queX, queY);
		}
		else m_pQuestUiMoveing->isClick = false;
	}
	else if (m_pQuestUiMoveing->isClick)
	{
		queX = m_pQuestUiImageHead->GetPosition().x + nDeltaX;
		queY = m_pQuestUiImageHead->GetPosition().y + nDeltaY;

		m_pQuestUiImageHead->SetPosition(queX, queY);
	}

	//탬 무빙
	int tempX;
	int tempY;
	bool isOnceCheck = true;
	
	if (m_isInventoryWindowOn)  //인벤토리 창이 열릴때만 
	{
		for (int i = 0; i < m_vecTempPlayerItem.size(); i++)
		{
			if (m_vecTempPlayerItem[i] == NULL) return; //탬이 없으면 리턴

			if (isOnceCheck)    // 중복체크 방지
			{
				//체크 상태일때(오버된 상태에서 누르고 있을때)
				if (m_vecTempPlayerItem[i]->isClick && m_pInventoryUiMoveing->isClick == false) 
				{
					tempX = m_vecTempPlayerItem[i]->GetPosition().x + nDeltaX;
					tempY = m_vecTempPlayerItem[i]->GetPosition().y + nDeltaY;

					m_vecTempPlayerItem[i]->SetPosition(tempX, tempY);  //좌표 잡고 이동 후
					isOnceCheck = false;   //중복 체크 방지 다시 false
				} // x = 160 ++24 y = 90 ++24
				else  //체크 상태가 아닐 시 (마우스를 때고 있을 시)
				{
					RECT rcTemp;
					//착용 이미지들(전체) 와 아이탬이 충돌 할 시
					if (IntersectRect(&rcTemp, &m_pInventoryUiEquipImage->rc, &m_vecTempPlayerItem[i]->rc))
					{
						if (m_vecTempPlayerItem[i]->m_eItem == cUIButton::E_ITEM_WEAR) //몸통일때 (버튼에서 따로 만들기)
						{
							//기존에 착용안 아이템이 있으면 해제
							// 착용 중 장비가 옮기는 장비와 같지 않을 시 (장비 교체)
							if (m_isTorsoMount != i)  
							{
								if (m_isTorsoMount > -1)  //장비가 있을시 (-1이면 장비헤제)
								{
									//이전 착용중인 장비의 포지션을 옮기는 장비의 이전 위치로 변경 후 업데이트
									//버튼 내에서 이전 위치 저장
									m_vecTempPlayerItem[m_isTorsoMount]->SetPosition(m_vecTempPlayerItem[i]->m_vItemPrevPos);
									m_vecTempPlayerItem[m_isTorsoMount]->Update();
								}
								//이미지 위치 이동 후
								m_vecTempPlayerItem[i]->SetPosition(m_pInventoryUiEquipTorso->GetPosition());
								m_isTorsoMount = i; //착용 장비 변경
								if (m_vecTempPlayerItem[i]->m_eItemStats == cUIButton::E_ITEM_STATS_WEAR_01)
								{
									m_eEquipTorso = E_TORSO_WEAR_01;
								}
								else if (m_vecTempPlayerItem[i]->m_eItemStats == cUIButton::E_ITEM_STATS_WEAR_02)
								{
									m_eEquipTorso = E_TORSO_WEAR_02;
								}
								else if (m_vecTempPlayerItem[i]->m_eItemStats == cUIButton::E_ITEM_STATS_WEAR_03)
								{
									m_eEquipTorso = E_TORSO_WEAR_03;
								}
								break;
							}
							//없으면 기냥 이동
							else m_vecTempPlayerItem[i]->SetPosition(m_pInventoryUiEquipTorso->GetPosition());
						}
						else if (m_vecTempPlayerItem[i]->m_eItem == cUIButton::E_ITEM_SHOES)
						{
							if (m_isShoesMount != i)
							{
								if (m_isShoesMount > -1)
								{
									m_vecTempPlayerItem[m_isShoesMount]->SetPosition(m_vecTempPlayerItem[i]->m_vItemPrevPos);
									m_vecTempPlayerItem[m_isShoesMount]->Update();
								}
								m_vecTempPlayerItem[i]->SetPosition(m_pInventoryUiEquipShoes->GetPosition());
								m_isShoesMount = i;
								if (m_vecTempPlayerItem[i]->m_eItemStats == cUIButton::E_ITEM_STATS_SHOES_01)
								{
									m_eEquipShoes = E_SHOES_01;
								}
								break;
							}
						}
					}
					else // 장비 헤제 할 시(장비를 빼서 아이탬칸으로 이동 시)
					{
						if (m_isTorsoMount == i)
						{
							m_isTorsoMount = -1; // -1(장비헤제 상태로 변경)
							m_eEquipTorso = E_TORSO_EMPTY;
						}
						if (m_isShoesMount == i)
						{
							m_isShoesMount = -1;
							m_eEquipShoes = E_SHOES_EMPTY;
						}
						this->_ItemInventory(i); //위치 재정렬)
					}
				}
			}
			else
			{
				m_vecTempPlayerItem[i]->isClick = false;
			}

		}
	}
}

void cUiTestScene::_ItemInventory(int i)
{
	//x좌표 구하기
	const int nOffsetX = 160;
	const int nBlockSize = 24; //블럭 크기
	int nPositionX = m_vecTempPlayerItem[i]->GetPosition().x - nOffsetX;
	int nBlockX = nPositionX / nBlockSize; //몫(위치)
	float fCheckX = nPositionX - nBlockX * (float)nBlockSize; //나머지
	//나머지의 크기가 겹치는 블럭의 반보다 크면 다음 블럭으로 이동
	if (fCheckX > nBlockSize * 0.5f && nBlockX < 6) nBlockX = nBlockX + 1;
	nPositionX = nBlockX * nBlockSize + nOffsetX;

	//y좌표 구하기
	const int nOffsetY = 90;
	int nPositionY = m_vecTempPlayerItem[i]->GetPosition().y - nOffsetY;
	int nBlockY = nPositionY / nBlockSize;   //몫(위치)
	float fCheckY = nPositionY - nBlockY * (float)nBlockSize; //나머지
	//나머지 크기가 겹치는 블럭의 반보다 크면 다음 블럭으로
	if (fCheckY > nBlockSize * 0.5f && nBlockY < 10) nBlockY += 1;
	nPositionY = nBlockY * nBlockSize + nOffsetY;

	m_vecTempPlayerItem[i]->SetPosition(nPositionX, nPositionY);

	RECT rc;
	//if(IntersectRect(&rc, &(), ()))
}
