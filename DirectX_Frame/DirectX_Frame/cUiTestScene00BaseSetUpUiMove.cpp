#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//�÷��̾�
#include "cPlayer.h"
#include "cCamera.h"
//�̹���
#include "cImage.h"

void cUiTestScene::SetupBaseButton(void)
{

	//�׽�Ʈ�� ���ι�ư��mainUiLocalX, mainUiLocalY
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

	//������ �̹�����
	//���� �̹���
	//�ִ�
	m_pMainHpMaxImage = cUIImageViewTemp::Create();
	m_pMainHpMaxImage->SetTexture("Texture/Ui/HPmainE.png");
	m_pMainHpMaxImage->SetPosition(m_nMainHPx, m_nMainHPy);
	m_pMainHpMaxImage->SetRectSize();
	//m_pMainHpMaxImage->m_rc.right = 50.0f;
	m_pMainHpMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainHpMaxImage);
	//���緮
	m_pMainHpImage = cUIImageViewTemp::Create();
	m_pMainHpImage->SetTexture("Texture/Ui/HPmain.png");
	m_pMainHpImage->SetPosition(m_nMainHPx, m_nMainHPy);
	m_pMainHpImage->SetRectSize();
	m_pMainHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pMainHpImage->stImageInfo.Width;
	m_pMainHpImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainHpImage);
	//���� �ý�Ʈ
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP());
	m_pMainHpText = cUITextView::Create();
	m_pMainHpText->SetText(szHP);
	m_pMainHpText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainHpText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainHpText->SetSize(ST_SIZE(100, 12));
	//m_pMainHpText->SetPosition(10, 150 - 7); //����ü
	m_pMainHpText->SetPosition(m_nMainHPx - 10, m_nMainHPy);   //�������
	m_pMainHpText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainHpText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainHpText);

	//������ �̹���
	//�ִ�
	m_pMainMpMaxImage = cUIImageViewTemp::Create();
	m_pMainMpMaxImage->SetTexture("Texture/Ui/MPmainE.png");
	m_pMainMpMaxImage->SetPosition(m_nMainMPx, m_nMainMPy);
	m_pMainMpMaxImage->SetRectSize();
	//m_pMainMpMaxImage->m_rc.right = 50.0f;
	m_pMainMpMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainMpMaxImage);
	//���緮
	m_pMainMpImage = cUIImageViewTemp::Create();
	m_pMainMpImage->SetTexture("Texture/Ui/MPmain.png");
	m_pMainMpImage->SetPosition(m_nMainMPx, m_nMainMPy);
	m_pMainMpImage->SetRectSize();
	m_pMainMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMainMpImage->stImageInfo.Width;
	m_pMainMpImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainMpImage);
	//���� �ý�Ʈ
	char szMP[32] = { '\0', };
	sprintf_s(szMP, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP());
	m_pMainMpText = cUITextView::Create();
	m_pMainMpText->SetText(szMP);
	m_pMainMpText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainMpText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainMpText->SetSize(ST_SIZE(100, 12));
	//m_pMainMpText->SetPosition(10, 150 - 7); //����ü
	m_pMainMpText->SetPosition(m_nMainMPx - 10, m_nMainMPy);   //�������
	m_pMainMpText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainMpText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainMpText);

	//���¹̳� �̹���
	//�ִ�
	m_pMainStaminaMaxImage = cUIImageViewTemp::Create();
	m_pMainStaminaMaxImage->SetTexture("Texture/Ui/SPmainE.png");
	m_pMainStaminaMaxImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
	m_pMainStaminaMaxImage->SetRectSize();
	//m_pMainStaminaMaxImage->m_rc.right = 50.0f;
	m_pMainStaminaMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainStaminaMaxImage);
	//���緮
	m_pMainStaminaImage = cUIImageViewTemp::Create();
	m_pMainStaminaImage->SetTexture("Texture/Ui/SPmain.png");
	m_pMainStaminaImage->SetPosition(m_nMainStaminaX, m_nMainStaminaY);
	m_pMainStaminaImage->SetRectSize();
	m_pMainStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pMainStaminaImage->stImageInfo.Width;
	m_pMainStaminaImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainStaminaImage);
	//���׹̳� �ý�Ʈ
	char szStamina[32] = { '\0', };
	sprintf_s(szStamina, "%d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina());
	m_pMainStaminaText = cUITextView::Create();
	m_pMainStaminaText->SetText(szStamina);
	m_pMainStaminaText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainStaminaText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainStaminaText->SetSize(ST_SIZE(100, 12));
	//m_pMainStaminaText->SetPosition(10, 150 - 7); //����ü
	m_pMainStaminaText->SetPosition(m_nMainStaminaX - 10, m_nMainStaminaY);   //�������
	m_pMainStaminaText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainStaminaText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainStaminaText);

	//������ ������
	//�ִ�
	m_pMainEXPMaxImage = cUIImageViewTemp::Create();
	m_pMainEXPMaxImage->SetTexture("Texture/Ui/EXPe1.png");
	m_pMainEXPMaxImage->SetPosition(m_nMainEXPx, m_nMainEXPy);
	m_pMainEXPMaxImage->SetRectSize();
	//m_pMainEXPMaxImage->m_rc.right = 50.0f;
	m_pMainEXPMaxImage->m_Alpha = 160;
	m_pUiRoot->AddChild(m_pMainEXPMaxImage);
	//���緮
	m_pMainEXPImage = cUIImageViewTemp::Create();
	m_pMainEXPImage->SetTexture("Texture/Ui/EXP1.png");
	m_pMainEXPImage->SetPosition(m_nMainEXPx, m_nMainEXPy);
	m_pMainEXPImage->SetRectSize();
	m_pMainEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pMainEXPImage->stImageInfo.Width;
	m_pMainEXPImage->m_Alpha = 220;
	m_pUiRoot->AddChild(m_pMainEXPImage);

	//����ġ �� ���� �ý�Ʈ
	char sEXP[64] = { '\0', };
	sprintf_s(sEXP, "%.1f %%"
		, (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() / g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * 100.0f);
	m_pMainEXPText = cUITextView::Create();
	m_pMainEXPText->SetText(sEXP);
	m_pMainEXPText->SetFontType(g_pFontManager->E_TEMP_IN_SMALL);
	m_pMainEXPText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMainEXPText->SetSize(ST_SIZE(120, 40));
	//m_pMainEXPText->SetPosition(-10, 280 - 7); //����ü
	m_pMainEXPText->SetPosition(315, 5);   //�������
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
	//m_pMainLevelText->SetPosition(-10, 280 - 7); //����ü
	m_pMainLevelText->SetPosition(85, 5);   //�������
	m_pMainLevelText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pMainLevelText->SetTag(E_BUTTON_NONE);
	m_pUiRoot->AddChild(m_pMainLevelText);

	//���� ����
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

	//�ý�Ʈ
	m_pUiExitText = cUITextView::Create();
	m_pUiExitText->SetText("����");
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
	//�ý�Ʈ
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


	//������ ������Ʈ
	//����
	m_pMainHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pMainHpImage->stImageInfo.Width;
	//���� ������ �ִ뷮���� ��������
	if (m_pMainHpImage->m_rc.right >= m_pMainHpImage->stImageInfo.Width) m_pMainHpImage->m_rc.right = m_pMainHpImage->stImageInfo.Width;
	//���� ������ 0���� �۾�����
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP() <= 0) m_pMainHpImage->m_rc.right = 1.0f;

	//������
	m_pMainMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMainMpImage->stImageInfo.Width;
	//���� �������� �ִ뷮���� ��������
	if (m_pMainMpImage->m_rc.right >= m_pMainMpImage->stImageInfo.Width)  m_pMainMpImage->m_rc.right = m_pMainMpImage->stImageInfo.Width;
	//���� �������� 0���� �۾�����
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP() <= 0) m_pMainMpImage->m_rc.right = 1.0f;

	//���¹̳� ��
	m_pMainStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pMainStaminaImage->stImageInfo.Width;
	//���� ���¹̳����� �ִ뷮���� ��������
	if (m_pMainStaminaImage->m_rc.right >= m_pMainStaminaImage->stImageInfo.Width) m_pMainStaminaImage->m_rc.right = m_pMainStaminaImage->stImageInfo.Width;
	//���� ���¹̳����� 0���� �۾�����
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina() <= 0) m_pMainStaminaImage->m_rc.right = 1.0f;

	//����ġ
	m_pMainEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pMainEXPImage->stImageInfo.Width;
	if (m_pMainEXPImage->m_rc.right >= m_pMainEXPImage->stImageInfo.Width) m_pMainEXPImage->m_rc.right = m_pMainEXPImage->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() <= 0) m_pMainEXPImage->m_rc.right = 0.1f;


	//�ּ�ȭ
	//����â ������
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
		//���ڸ�
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
	//���� ����
	POINT ptMouse = m_ptMouse;				//���� ��ǥ ����

	GetCursorPos(&m_ptMouse);				//���콺 ��ǥ(�ɹ����� ������)
	ScreenToClient(g_hWnd, &m_ptMouse);		//���콺 ��ǥ(�ɹ����� ������)

	int nDeltaX = (m_ptMouse.x - ptMouse.x); //���� ��ǥ - ���� ��ǥ (������ ��)
	int nDeltaY = (m_ptMouse.y - ptMouse.y); //���� ��ǥ - ���� ��ǥ (������ ��)

	//�κ� â ����
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
			invX = m_pInventoryUiImageHead->GetPosition().x + nDeltaX; //���� ������ â���� ������ �縸ŭ �����ش�
			invY = m_pInventoryUiImageHead->GetPosition().y + nDeltaY;

			m_pInventoryUiImageHead->SetPosition(invX, invY);
		}
		else m_pInventoryUiMoveing->isClick = false;
	}
	else if (m_pInventoryUiMoveing->isClick == true)		//Ŭ�� ���¿��� ������
	{
		invX = m_pInventoryUiImageHead->GetPosition().x + nDeltaX; //���� ������ â���� ������ �縸ŭ �����ش�
		invY = m_pInventoryUiImageHead->GetPosition().y + nDeltaY;

		m_pInventoryUiImageHead->SetPosition(invX, invY);
	}

	//���� â ����
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

	//��ų â ����
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
	//�� â ����
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

	//�� ����
	int tempX;
	int tempY;
	bool isOnceCheck = true;
	
	if (m_isInventoryWindowOn)  //�κ��丮 â�� �������� 
	{
		for (int i = 0; i < m_vecTempPlayerItem.size(); i++)
		{
			if (m_vecTempPlayerItem[i] == NULL) return; //���� ������ ����

			if (isOnceCheck)    // �ߺ�üũ ����
			{
				//üũ �����϶�(������ ���¿��� ������ ������)
				if (m_vecTempPlayerItem[i]->isClick && m_pInventoryUiMoveing->isClick == false) 
				{
					tempX = m_vecTempPlayerItem[i]->GetPosition().x + nDeltaX;
					tempY = m_vecTempPlayerItem[i]->GetPosition().y + nDeltaY;

					m_vecTempPlayerItem[i]->SetPosition(tempX, tempY);  //��ǥ ��� �̵� ��
					isOnceCheck = false;   //�ߺ� üũ ���� �ٽ� false
				} // x = 160 ++24 y = 90 ++24
				else  //üũ ���°� �ƴ� �� (���콺�� ���� ���� ��)
				{
					RECT rcTemp;
					//���� �̹�����(��ü) �� �������� �浹 �� ��
					if (IntersectRect(&rcTemp, &m_pInventoryUiEquipImage->rc, &m_vecTempPlayerItem[i]->rc))
					{
						if (m_vecTempPlayerItem[i]->m_eItem == cUIButton::E_ITEM_WEAR) //�����϶� (��ư���� ���� �����)
						{
							//������ ����� �������� ������ ����
							// ���� �� ��� �ű�� ���� ���� ���� �� (��� ��ü)
							if (m_isTorsoMount != i)  
							{
								if (m_isTorsoMount > -1)  //��� ������ (-1�̸� �������)
								{
									//���� �������� ����� �������� �ű�� ����� ���� ��ġ�� ���� �� ������Ʈ
									//��ư ������ ���� ��ġ ����
									m_vecTempPlayerItem[m_isTorsoMount]->SetPosition(m_vecTempPlayerItem[i]->m_vItemPrevPos);
									m_vecTempPlayerItem[m_isTorsoMount]->Update();
								}
								//�̹��� ��ġ �̵� ��
								m_vecTempPlayerItem[i]->SetPosition(m_pInventoryUiEquipTorso->GetPosition());
								m_isTorsoMount = i; //���� ��� ����
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
							//������ ��� �̵�
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
					else // ��� ���� �� ��(��� ���� ������ĭ���� �̵� ��)
					{
						if (m_isTorsoMount == i)
						{
							m_isTorsoMount = -1; // -1(������� ���·� ����)
							m_eEquipTorso = E_TORSO_EMPTY;
						}
						if (m_isShoesMount == i)
						{
							m_isShoesMount = -1;
							m_eEquipShoes = E_SHOES_EMPTY;
						}
						this->_ItemInventory(i); //��ġ ������)
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
	//x��ǥ ���ϱ�
	const int nOffsetX = 160;
	const int nBlockSize = 24; //�� ũ��
	int nPositionX = m_vecTempPlayerItem[i]->GetPosition().x - nOffsetX;
	int nBlockX = nPositionX / nBlockSize; //��(��ġ)
	float fCheckX = nPositionX - nBlockX * (float)nBlockSize; //������
	//�������� ũ�Ⱑ ��ġ�� ���� �ݺ��� ũ�� ���� ������ �̵�
	if (fCheckX > nBlockSize * 0.5f && nBlockX < 6) nBlockX = nBlockX + 1;
	nPositionX = nBlockX * nBlockSize + nOffsetX;

	//y��ǥ ���ϱ�
	const int nOffsetY = 90;
	int nPositionY = m_vecTempPlayerItem[i]->GetPosition().y - nOffsetY;
	int nBlockY = nPositionY / nBlockSize;   //��(��ġ)
	float fCheckY = nPositionY - nBlockY * (float)nBlockSize; //������
	//������ ũ�Ⱑ ��ġ�� ���� �ݺ��� ũ�� ���� ������
	if (fCheckY > nBlockSize * 0.5f && nBlockY < 10) nBlockY += 1;
	nPositionY = nBlockY * nBlockSize + nOffsetY;

	m_vecTempPlayerItem[i]->SetPosition(nPositionX, nPositionY);

	RECT rc;
	//if(IntersectRect(&rc, &(), ()))
}
