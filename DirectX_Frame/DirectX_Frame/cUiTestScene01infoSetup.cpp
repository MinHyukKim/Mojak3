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

void cUiTestScene::SetupInfoUi(void)
{

	//���� â �Ӹ�
	m_pInfoUiImageHead = cUIImageView::Create();
	m_pInfoUiImageHead->SetTexture("Texture/Ui/infoBaseHead1.png");
	m_pInfoUiImageHead->SetPosition(infoX, infoY);
	m_pInfoUiImageHead->m_Alpha = 200;
	m_pInfoUi = m_pInfoUiImageHead;
	//�巡�� ��ư
	m_pInfoUiMoveing = cUIButton::Create();
	m_pInfoUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pInfoUiMoveing->SetPosition(0, 0);
	m_pInfoUiMoveing->SetDelegate(this);
	m_pInfoUiMoveing->m_Alpha = 0;
	m_pInfoUiMoveing->SetTag(E_INFO_MOVE);
	m_pInfoUi->AddChild(m_pInfoUiMoveing);
	//���� ���̽� â
	m_pInfoUiImage = cUIButton::Create();
	m_pInfoUiImage->SetTexture("Texture/Ui/infoBase3.png"
	, "Texture/Ui/infoBase3.png", "Texture/Ui/infoBase3.png");
	m_pInfoUiImage->SetPosition(2, 48);
	m_pInfoUiImage->SetDelegate(this);
	m_pInfoUiImage->SetTag(E_BUTTON_NONE);
	m_pInfoUiImage->m_Alpha = 180;
	m_pInfoUi->AddChild(m_pInfoUiImage);
	//�ݱ� ��ư
	m_pInfoCloseButton = cUIButton::Create();
	m_pInfoCloseButton->SetTexture("Texture/Ui/button_close_up.png"
		, "Texture/Ui/button_close_over.png", "Texture/Ui/button_close_up.png");
	m_pInfoCloseButton->SetPosition(290, 10);
	m_pInfoCloseButton->SetDelegate(this);
	m_pInfoCloseButton->SetTag(E_BUTTON_INFO_CLOSE);
	m_pInfoCloseButton->m_Alpha = 180;
	m_pInfoUi->AddChild(m_pInfoCloseButton);

	//�ý�Ʈ
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("ĳ���� ����");
	m_pInfoUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(200, 100));
	m_pInfoUiText->SetPosition(-20, -30);
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);

	//���̽� �ý�Ʈ��
	//�̸�
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("�̸�");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(10, 50 - 7); //����ü
	m_pInfoUiText->SetPosition(10, 50);   //�������
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//����
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("����");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(50, 40));
	//m_pInfoUiText->SetPosition(10, 80 - 7); //����ü
	m_pInfoUiText->SetPosition(10, 80);   //�������
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);
	//����/����
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("����/����");
	m_pInfoUiText->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(100, 40));
	//m_pInfoUiText->SetPosition(-1, 110 - 7); //����ü
	m_pInfoUiText->SetPosition(-1, 110);   //�������
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);

	//���� ���� �ֱ�
	//���� �̹���
	int InfoHPx = 80;
	int InfoHPy = 162;
	//�ִ�
	m_pHpMaxImage = cUIImageViewTemp::Create();
	m_pHpMaxImage->SetTexture("Texture/Ui/HPe.png");
	m_pHpMaxImage->SetPosition(InfoHPx, InfoHPy);
	m_pHpMaxImage->SetRectSize();
	//m_pHpMaxImage->m_rc.right = 50.0f;
	m_pHpMaxImage->m_Alpha = 160;
	m_pInfoUi->AddChild(m_pHpMaxImage);
	//���緮
	m_pHpImage = cUIImageViewTemp::Create();
	m_pHpImage->SetTexture("Texture/Ui/HP.png");
	m_pHpImage->SetPosition(InfoHPx, InfoHPy);
	m_pHpImage->SetRectSize();
	m_pHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pHpImage->stImageInfo.Width;
	m_pHpImage->m_Alpha = 220;
	m_pInfoUi->AddChild(m_pHpImage);
	//����
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "�����      %d / %d", m_nTempHP, m_nTempMaxHP);
	m_pTempInfoHP = cUITextView::Create();
	m_pTempInfoHP->SetText(szHP);
	m_pTempInfoHP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoHP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoHP->SetSize(ST_SIZE(120, 40));
	//m_pTotalInfo->SetPosition(10, 150 - 7); //����ü
	m_pTempInfoHP->SetPosition(10, 150);   //�������
	m_pTempInfoHP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoHP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoHP);

	//������ �̹���
	int InfoMPx = 80;
	int InfoMPy = 182;
	//�ִ�
	m_pMpMaxImage = cUIImageViewTemp::Create();
	m_pMpMaxImage->SetTexture("Texture/Ui/MPe.png");
	m_pMpMaxImage->SetPosition(InfoMPx, InfoMPy);
	m_pMpMaxImage->SetRectSize();
	//m_pMpMaxImage->m_rc.right = 50.0f;
	m_pMpMaxImage->m_Alpha = 160;
	m_pInfoUi->AddChild(m_pMpMaxImage);
	//���緮
	m_pMpImage = cUIImageViewTemp::Create();
	m_pMpImage->SetTexture("Texture/Ui/MP.png");
	m_pMpImage->SetPosition(InfoMPx, InfoMPy);
	m_pMpImage->SetRectSize();
	m_pMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMpImage->stImageInfo.Width;
	m_pMpImage->m_Alpha = 220;
	m_pInfoUi->AddChild(m_pMpImage);
	//����
	char szMP[32] = { '\0', };
	sprintf_s(szMP, "����         %d / %d", m_nTempMP, m_nTempMaxMP);
	m_pTempInfoMP = cUITextView::Create();
	m_pTempInfoMP->SetText(szMP);
	m_pTempInfoMP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMP->SetSize(ST_SIZE(150, 40));
	//m_pTempInfoMP->SetPosition(20, 170 - 7); //����ü
	m_pTempInfoMP->SetPosition(-5, 170);   //�������
	//m_pTempInfoMP->m_vPosition = D3DXVECTOR3(20, 170, -0.5f);
	m_pTempInfoMP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMP);	
	
	//���¹̳� �̹���
	int InfoStaminaX = 80;
	int InfoStaminaY = 202;
	//�ִ�
	m_pStaminaMaxImage = cUIImageViewTemp::Create();
	m_pStaminaMaxImage->SetTexture("Texture/Ui/SPe.png");
	m_pStaminaMaxImage->SetPosition(InfoStaminaX, InfoStaminaY);
	m_pStaminaMaxImage->SetRectSize();
	//m_pStaminaMaxImage->m_rc.right = 50.0f;
	m_pStaminaMaxImage->m_Alpha = 160;
	m_pInfoUi->AddChild(m_pStaminaMaxImage);
	//���緮
	m_pStaminaImage = cUIImageViewTemp::Create();
	m_pStaminaImage->SetTexture("Texture/Ui/SP.png");
	m_pStaminaImage->SetPosition(InfoStaminaX, InfoStaminaY);
	m_pStaminaImage->SetRectSize();
	m_pStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pStaminaImage->stImageInfo.Width;
	m_pStaminaImage->m_Alpha = 220;
	m_pInfoUi->AddChild(m_pStaminaImage);
	//���¹̳�
	char szStamina[64] = { '\0', };
	sprintf_s(szStamina, "���׹̳�   %d / %d", nTempStamina, m_nTempMaxStamina);
	m_pTempInfoStamina = cUITextView::Create();
	m_pTempInfoStamina->SetText(szStamina);
	m_pTempInfoStamina->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoStamina->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoStamina->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoStamina->SetPosition(19, 190 - 7); //����ü
	m_pTempInfoStamina->SetPosition(19, 190);   //�������
	m_pTempInfoStamina->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoStamina->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoStamina);

	//����
	char szLevel[32] = { '\0', };
	sprintf_s(szLevel, "����             %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetLevel());
	m_pInfoLevel = cUITextView::Create();
	m_pInfoLevel->SetText(szLevel);
	m_pInfoLevel->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoLevel->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoLevel->SetSize(ST_SIZE(150, 40));
	//m_pInfoLevel->SetPosition(10, 150 - 7); //����ü
	m_pInfoLevel->SetPosition(134, 150);   //�������
	m_pInfoLevel->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoLevel->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoLevel);

	//����ġ �̹���
	int InfoEXPx = 240;
	int InfoEXPy = 182;
	//�ִ�
	m_pEXPMaxImage = cUIImageViewTemp::Create();
	m_pEXPMaxImage->SetTexture("Texture/Ui/EXPinfoE.png");
	m_pEXPMaxImage->SetPosition(InfoEXPx, InfoEXPy);
	m_pEXPMaxImage->SetRectSize();
	//m_pEXPMaxImage->m_rc.right = 50.0f;
	m_pEXPMaxImage->m_Alpha = 160;
	m_pInfoUi->AddChild(m_pEXPMaxImage);
	//���緮
	m_pEXPImage = cUIImageViewTemp::Create();
	m_pEXPImage->SetTexture("Texture/Ui/EXPinfo1.png");
	m_pEXPImage->SetPosition(InfoEXPx, InfoEXPy);
	m_pEXPImage->SetRectSize();
	m_pEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pEXPImage->stImageInfo.Width;
	m_pEXPImage->m_Alpha = 220;
	m_pInfoUi->AddChild(m_pEXPImage);
	//����ġ
	char szEXP[32] = { '\0', };
	sprintf_s(szEXP, "����ġ          %.1f %%"
	, (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() / g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * 100.0f);
	m_pInfoEXP = cUITextView::Create();
	m_pInfoEXP->SetText(szEXP);
	m_pInfoEXP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoEXP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoEXP->SetSize(ST_SIZE(150, 40));
	//m_pInfoEXP->SetPosition(20, 170 - 7); //����ü
	m_pInfoEXP->SetPosition(146, 170);   //�������
	m_pInfoEXP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoEXP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoEXP);

	//�����Ƽ����Ʈ
	char szAP[64] = { '\0', };
	sprintf_s(szAP, "�����Ƽ����Ʈ     %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetAP());
	m_pInfoAP = cUITextView::Create();
	m_pInfoAP->SetText(szAP);
	m_pInfoAP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pInfoAP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoAP->SetSize(ST_SIZE(150, 40));
	//m_pInfoAP->SetPosition(19, 190 - 7); //����ü
	m_pInfoAP->SetPosition(148, 190);   //�������
	m_pInfoAP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoAP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoAP);

	//ü��
	char szSTR[64] = { '\0', };
	sprintf_s(szSTR, "ü��      %d", m_nTempSTR);
	m_pTempInfoSTR = cUITextView::Create();
	m_pTempInfoSTR->SetText(szSTR);
	m_pTempInfoSTR->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoSTR->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoSTR->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoSTR->SetPosition(19, 190 - 7); //����ü
	m_pTempInfoSTR->SetPosition(-0, 220);   //�������
	m_pTempInfoSTR->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoSTR->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoSTR);

	//����
	char szINT[64] = { '\0', };
	sprintf_s(szINT, "����      %d", m_nTempINT);
	m_pTempInfoINT = cUITextView::Create();
	m_pTempInfoINT->SetText(szINT);
	m_pTempInfoINT->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoINT->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoINT->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoINT->SetPosition(-10, 240 - 7); //����ü
	m_pTempInfoINT->SetPosition(-0, 240);   //�������
	m_pTempInfoINT->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoINT->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoINT);

	//����
	char szWill[64] = { '\0', };
	sprintf_s(szWill, "����      %d", m_nTempWill);
	m_pTempInfoWill = cUITextView::Create();
	m_pTempInfoWill->SetText(szWill);
	m_pTempInfoWill->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoWill->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoWill->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoWill->SetPosition(-10, 260 - 7); //����ü
	m_pTempInfoWill->SetPosition(-0, 260);   //�������
	m_pTempInfoWill->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoWill->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoWill);

	//���
	char szLuck[64] = { '\0', };
	sprintf_s(szLuck, "���      %d", m_nTempLuck);
	m_pTempInfoLuck = cUITextView::Create();
	m_pTempInfoLuck->SetText(szLuck);
	m_pTempInfoLuck->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoLuck->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoLuck->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoLuck->SetPosition(-10, 280 - 7); //����ü
	m_pTempInfoLuck->SetPosition(-0, 280);   //�������
	m_pTempInfoLuck->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoLuck->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoLuck);

	//�ؾ�
	char szWorkmanship[64] = { '\0', };
	sprintf_s(szWorkmanship, "�ؾ�      %d", m_nTempWorkmanship);
	m_pTempInfoWorkmanship = cUITextView::Create();
	m_pTempInfoWorkmanship->SetText(szWorkmanship);
	m_pTempInfoWorkmanship->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoWorkmanship->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoWorkmanship->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoWorkmanship->SetPosition(-10, 300 - 7); //����ü
	m_pTempInfoWorkmanship->SetPosition(-0, 300);   //�������
	m_pTempInfoWorkmanship->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoWorkmanship->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoWorkmanship);

	//������
	char szDamage[64] = { '\0', };
	sprintf_s(szDamage, "���ݷ�           %d", m_nTempTotalDamage);
	m_pTempInfoDamage = cUITextView::Create();
	m_pTempInfoDamage->SetText(szDamage);
	m_pTempInfoDamage->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoDamage->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoDamage->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoDamage->SetPosition(-10, 280 - 7); //����ü
	m_pTempInfoDamage->SetPosition(60, 220);   //�������
	m_pTempInfoDamage->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoDamage->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoDamage);

	//����
	char szMagicDamage[64] = { '\0', };
	sprintf_s(szMagicDamage, "�������ݷ�      %d", m_nTempTotalMagicDamage);
	m_pTempInfoMagicDamage = cUITextView::Create();
	m_pTempInfoMagicDamage->SetText(szMagicDamage);
	m_pTempInfoMagicDamage->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicDamage->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicDamage->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoMagicDamage->SetPosition(-10, 240 - 7); //����ü
	m_pTempInfoMagicDamage->SetPosition(60, 240);   //�������
	m_pTempInfoMagicDamage->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicDamage->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicDamage);

	//�λ��
	char szMagicInjury[64] = { '\0', };
	sprintf_s(szMagicInjury, "�λ��      %.1f %%", m_fTempInjury);
	m_pTempInfoInjury = cUITextView::Create();
	m_pTempInfoInjury->SetText(szMagicInjury);
	m_pTempInfoInjury->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoInjury->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoInjury->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoInjury->SetPosition(-10, 260 - 7); //����ü
	m_pTempInfoInjury->SetPosition(60, 260);   //�������
	m_pTempInfoInjury->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoInjury->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoInjury);

	//ũ��Ƽ��
	char szMagicCritical[64] = { '\0', };
	sprintf_s(szMagicCritical, "ũ��Ƽ��   %.1f %%", m_fTempCritical);
	m_pTempInfoCritical = cUITextView::Create();
	m_pTempInfoCritical->SetText(szMagicCritical);
	m_pTempInfoCritical->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoCritical->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoCritical->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoCritical->SetPosition(-10, 280 - 7); //����ü
	m_pTempInfoCritical->SetPosition(60, 280);   //�������
	m_pTempInfoCritical->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoCritical->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoCritical);
	
	//�뷱��
	char szMagicBalance[64] = { '\0', };
	sprintf_s(szMagicBalance, "������           %d", m_nTempBalance);
	m_pTempInfoBalance = cUITextView::Create();
	m_pTempInfoBalance->SetText(szMagicBalance);
	m_pTempInfoBalance->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoBalance->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoBalance->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoBalance->SetPosition(-10, 300 - 7); //����ü
	m_pTempInfoBalance->SetPosition(60, 300);   //�������
	m_pTempInfoBalance->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoBalance->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoBalance);

	//���
	char szDefense[64] = { '\0', };
	sprintf_s(szDefense, "���            %d", m_nTempDefense);
	m_pTempInfoDefense = cUITextView::Create();
	m_pTempInfoDefense->SetText(szDefense);
	m_pTempInfoDefense->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoDefense->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoDefense->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoDefense->SetPosition(-10, 240 - 7); //����ü
	m_pTempInfoDefense->SetPosition(170, 220);   //�������
	m_pTempInfoDefense->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoDefense->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoDefense);

	//��ȣ
	char szProtect[64] = { '\0', };
	sprintf_s(szProtect, "��ȣ            %d", m_nTempProtect);
	m_pTempInfoProtect = cUITextView::Create();
	m_pTempInfoProtect->SetText(szProtect);
	m_pTempInfoProtect->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoProtect->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoProtect->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoProtect->SetPosition(-10, 240 - 7); //����ü
	m_pTempInfoProtect->SetPosition(170, 240);   //�������
	m_pTempInfoProtect->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoProtect->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoProtect);

	//�������
	char szMagicDefense[64] = { '\0', };
	sprintf_s(szMagicDefense, "�������      %d", m_nTempMagicDefense);
	m_pTempInfoMagicDefense = cUITextView::Create();
	m_pTempInfoMagicDefense->SetText(szMagicDefense);
	m_pTempInfoMagicDefense->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicDefense->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicDefense->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoMagicDefense->SetPosition(-10, 260 - 7); //����ü
	m_pTempInfoMagicDefense->SetPosition(200, 260);   //�������
	m_pTempInfoMagicDefense->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicDefense->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicDefense);

	//������ȣ
	char szMagicProtect[64] = { '\0', };
	sprintf_s(szMagicProtect, "������ȣ      %d", m_nTempMagicProtect);
	m_pTempInfoMagicProtect = cUITextView::Create();
	m_pTempInfoMagicProtect->SetText(szMagicProtect);
	m_pTempInfoMagicProtect->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicProtect->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicProtect->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoMagicProtect->SetPosition(-10, 280 - 7); //����ü
	m_pTempInfoMagicProtect->SetPosition(200, 280);   //�������
	m_pTempInfoMagicProtect->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicProtect->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicProtect);

	//������
	char szArmorPiercing[64] = { '\0', };
	sprintf_s(szArmorPiercing, "������      %d", m_nTempArmorPiercing);
	m_pTempInfoArmorPiercing = cUITextView::Create();
	m_pTempInfoArmorPiercing->SetText(szArmorPiercing);
	m_pTempInfoArmorPiercing->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoArmorPiercing->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoArmorPiercing->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoArmorPiercing->SetPosition(-10, 280 - 7); //����ü
	m_pTempInfoArmorPiercing->SetPosition(200, 300);   //�������
	m_pTempInfoArmorPiercing->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoArmorPiercing->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoArmorPiercing);
}

void cUiTestScene::UpdateInfoUi(void)
{
	//m_pPlayer->GetAbilityParamter()->GetStr
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "�����      %d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP());
	m_pTempInfoHP->SetText(szHP);

	char szMP[32] = { '\0', };
	sprintf_s(szMP, "����         %d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP());
	m_pTempInfoMP->SetText(szMP);

	char szStamina[64] = { '\0', };
	sprintf_s(szStamina, "���׹̳�   %d / %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina());
	m_pTempInfoStamina->SetText(szStamina);

	
	char szEXP[32] = { '\0', };
	sprintf_s(szEXP, "����ġ          %.1f %%"
		, (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() / g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * 100.0f);
	m_pInfoEXP->SetText(szEXP);

	char szAP[64] = { '\0', };
	sprintf_s(szAP, "�����Ƽ����Ʈ     %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetAP());
	m_pInfoAP->SetText(szAP);

	char szSTR[64] = { '\0', };
	sprintf_s(szSTR, "ü��      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetStr());
	m_pTempInfoSTR->SetText(szSTR);

	char szINT[64] = { '\0', };
	sprintf_s(szINT, "����      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetInt());
	m_pTempInfoINT->SetText(szINT);

	char szWill[64] = { '\0', };
	sprintf_s(szWill, "����      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetWill());
	m_pTempInfoWill->SetText(szWill);

	char szLuck[64] = { '\0', };
	sprintf_s(szLuck, "���      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetLuk());
	m_pTempInfoLuck->SetText(szLuck);

	char szWorkmanship[64] = { '\0', };
	sprintf_s(szWorkmanship, "�ؾ�      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDex());
	m_pTempInfoWorkmanship->SetText(szWorkmanship);

	char szDamage[64] = { '\0', };//p           p
	sprintf_s(szDamage, "���ݷ�    %d ~ %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinDamage()
	, g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinDamage() + g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetBonusDamage());
	m_pTempInfoDamage->SetText(szDamage);

	char szMagicDamage[64] = { '\0', };
	sprintf_s(szMagicDamage, "�������ݷ�      %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMagicDamage());
	m_pTempInfoMagicDamage->SetText(szMagicDamage);

	char szMagicInjury[64] = { '\0', };
	sprintf_s(szMagicInjury, "�λ��      %.1f %%", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetInjury());
	m_pTempInfoInjury->SetText(szMagicInjury);

	char szMagicCritical[64] = { '\0', };
	sprintf_s(szMagicCritical, "ũ��Ƽ��   %.1f %%", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetCritical());
	m_pTempInfoCritical->SetText(szMagicCritical);

	char szMagicBalance[64] = { '\0', };
	sprintf_s(szMagicBalance, "������           %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetBalance());
	m_pTempInfoBalance->SetText(szMagicBalance);

	char szDefense[64] = { '\0', };
	sprintf_s(szDefense, "���            %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefence());
	m_pTempInfoDefense->SetText(szDefense);

	char szProtect[64] = { '\0', };
	sprintf_s(szProtect, "��ȣ            %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetProtecte());
	m_pTempInfoProtect->SetText(szProtect);

	char szMagicDefense[64] = { '\0', };
	sprintf_s(szMagicDefense, "�������      %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMagicDefence());
	m_pTempInfoMagicDefense->SetText(szMagicDefense);

	char szMagicProtect[64] = { '\0', };
	sprintf_s(szMagicProtect, "������ȣ      %d", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMagicProtecte());
	m_pTempInfoMagicProtect->SetText(szMagicProtect);

	char szArmorPiercing[64] = { '\0', };
	sprintf_s(szArmorPiercing, "������      %.0f", g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetPenetration());
	m_pTempInfoArmorPiercing->SetText(szArmorPiercing);

	//�̹���	������Ʈ
	//ü��
	m_pHpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxHP()) * m_pHpImage->stImageInfo.Width;
	if (m_pHpImage->m_rc.right >= m_pHpImage->stImageInfo.Width) m_pHpImage->m_rc.right = m_pHpImage->stImageInfo.Width;
//	if (m_pHpImage->m_rc.right <= 0.0f) m_pHpImage->m_rc.right = 1.0f;
	if(g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinHP() <= 0) m_pHpImage->m_rc.right = 1.0f;

	//����
	m_pMpImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxMP()) * m_pMpImage->stImageInfo.Width;
	if (m_pMpImage->m_rc.right >= m_pMpImage->stImageInfo.Width) m_pMpImage->m_rc.right = m_pMpImage->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinMP() <= 0) m_pMpImage->m_rc.right = 1.0f;

	//���׹̳�
	m_pStaminaImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxStamina()) * m_pStaminaImage->stImageInfo.Width;
	if (m_pStaminaImage->m_rc.right >= m_pStaminaImage->stImageInfo.Width) m_pStaminaImage->m_rc.right = m_pStaminaImage->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMinStamina() <= 0) m_pStaminaImage->m_rc.right = 1.0f;

	//����ġ
	m_pEXPImage->m_rc.right = ((float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP()
		/ (float)g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetMaxEXP()) * m_pEXPImage->stImageInfo.Width;
	if (m_pEXPImage->m_rc.right >= m_pEXPImage->stImageInfo.Width) m_pEXPImage->m_rc.right = m_pEXPImage->stImageInfo.Width;
	if (g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetEXP() <= 0) m_pEXPImage->m_rc.right = 0.1f;
}