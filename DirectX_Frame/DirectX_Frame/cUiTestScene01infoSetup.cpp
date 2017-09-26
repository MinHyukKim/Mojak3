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
	m_pInfoUiImage->SetTexture("Texture/Ui/infoBase3.png"
	, "Texture/Ui/infoBase3.png", "Texture/Ui/infoBase3.png");
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

	//택스트
	m_pInfoUiText = cUITextView::Create();
	m_pInfoUiText->SetText("캐릭터 정보");
	m_pInfoUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pInfoUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInfoUiText->SetSize(ST_SIZE(200, 100));
	m_pInfoUiText->SetPosition(-20, -30);
	m_pInfoUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInfoUiText->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pInfoUiText);

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

	//가변 정보 넣기
	//피통
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "생명력      %d / %d", m_nTempHP, m_nTempMaxHP);
	m_pTempInfoHP = cUITextView::Create();
	m_pTempInfoHP->SetText(szHP);
	m_pTempInfoHP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoHP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoHP->SetSize(ST_SIZE(120, 40));
	//m_pTotalInfo->SetPosition(10, 150 - 7); //마비체
	m_pTempInfoHP->SetPosition(10, 150);   //나눔고딕
	m_pTempInfoHP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoHP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoHP);

	//마나
	char szMP[32] = { '\0', };
	sprintf_s(szMP, "마나         %d / %d", m_nTempMP, m_nTempMaxMP);
	m_pTempInfoMP = cUITextView::Create();
	m_pTempInfoMP->SetText(szMP);
	m_pTempInfoMP->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMP->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMP->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoMP->SetPosition(20, 170 - 7); //마비체
	m_pTempInfoMP->SetPosition(20, 170);   //나눔고딕
	//m_pTempInfoMP->m_vPosition = D3DXVECTOR3(20, 170, -0.5f);
	m_pTempInfoMP->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMP->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMP);

	//스태미나
	char szStamina[64] = { '\0', };
	sprintf_s(szStamina, "스테미나   %d / %d", nTempStamina, m_nTempMaxStamina);
	m_pTempInfoStamina = cUITextView::Create();
	m_pTempInfoStamina->SetText(szStamina);
	m_pTempInfoStamina->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoStamina->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoStamina->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoStamina->SetPosition(19, 190 - 7); //마비체
	m_pTempInfoStamina->SetPosition(19, 190);   //나눔고딕
	m_pTempInfoStamina->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoStamina->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoStamina);

	//체력
	char szSTR[64] = { '\0', };
	sprintf_s(szSTR, "체력      %d", m_nTempSTR);
	m_pTempInfoSTR = cUITextView::Create();
	m_pTempInfoSTR->SetText(szSTR);
	m_pTempInfoSTR->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoSTR->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoSTR->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoSTR->SetPosition(19, 190 - 7); //마비체
	m_pTempInfoSTR->SetPosition(-0, 220);   //나눔고딕
	m_pTempInfoSTR->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoSTR->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoSTR);

	//지력
	char szINT[64] = { '\0', };
	sprintf_s(szINT, "지력      %d", m_nTempINT);
	m_pTempInfoINT = cUITextView::Create();
	m_pTempInfoINT->SetText(szINT);
	m_pTempInfoINT->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoINT->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoINT->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoINT->SetPosition(-10, 240 - 7); //마비체
	m_pTempInfoINT->SetPosition(-0, 240);   //나눔고딕
	m_pTempInfoINT->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoINT->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoINT);

	//의지
	char szWill[64] = { '\0', };
	sprintf_s(szWill, "의지      %d", m_nTempWill);
	m_pTempInfoWill = cUITextView::Create();
	m_pTempInfoWill->SetText(szWill);
	m_pTempInfoWill->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoWill->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoWill->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoWill->SetPosition(-10, 260 - 7); //마비체
	m_pTempInfoWill->SetPosition(-0, 260);   //나눔고딕
	m_pTempInfoWill->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoWill->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoWill);

	//행운
	char szLuck[64] = { '\0', };
	sprintf_s(szLuck, "행운      %d", m_nTempLuck);
	m_pTempInfoLuck = cUITextView::Create();
	m_pTempInfoLuck->SetText(szLuck);
	m_pTempInfoLuck->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoLuck->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoLuck->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoLuck->SetPosition(-10, 280 - 7); //마비체
	m_pTempInfoLuck->SetPosition(-0, 280);   //나눔고딕
	m_pTempInfoLuck->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoLuck->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoLuck);

	//솜씨
	char szWorkmanship[64] = { '\0', };
	sprintf_s(szWorkmanship, "솜씨      %d", m_nTempWorkmanship);
	m_pTempInfoWorkmanship = cUITextView::Create();
	m_pTempInfoWorkmanship->SetText(szWorkmanship);
	m_pTempInfoWorkmanship->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoWorkmanship->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoWorkmanship->SetSize(ST_SIZE(100, 40));
	//m_pTempInfoWorkmanship->SetPosition(-10, 300 - 7); //마비체
	m_pTempInfoWorkmanship->SetPosition(-0, 300);   //나눔고딕
	m_pTempInfoWorkmanship->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoWorkmanship->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoWorkmanship);

	//데미지
	char szDamage[64] = { '\0', };
	sprintf_s(szDamage, "공격력           %d", m_nTempTotalDamage);
	m_pTempInfoDamage = cUITextView::Create();
	m_pTempInfoDamage->SetText(szDamage);
	m_pTempInfoDamage->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoDamage->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoDamage->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoDamage->SetPosition(-10, 280 - 7); //마비체
	m_pTempInfoDamage->SetPosition(60, 220);   //나눔고딕
	m_pTempInfoDamage->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoDamage->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoDamage);

	//마공
	char szMagicDamage[64] = { '\0', };
	sprintf_s(szMagicDamage, "마법공격력      %d", m_nTempTotalMagicDamage);
	m_pTempInfoMagicDamage = cUITextView::Create();
	m_pTempInfoMagicDamage->SetText(szMagicDamage);
	m_pTempInfoMagicDamage->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicDamage->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicDamage->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoMagicDamage->SetPosition(-10, 240 - 7); //마비체
	m_pTempInfoMagicDamage->SetPosition(60, 240);   //나눔고딕
	m_pTempInfoMagicDamage->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicDamage->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicDamage);

	//부상률
	char szMagicInjury[64] = { '\0', };
	sprintf_s(szMagicInjury, "부상률      %.1f %%", m_fTempInjury);
	m_pTempInfoInjury = cUITextView::Create();
	m_pTempInfoInjury->SetText(szMagicInjury);
	m_pTempInfoInjury->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoInjury->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoInjury->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoInjury->SetPosition(-10, 260 - 7); //마비체
	m_pTempInfoInjury->SetPosition(60, 260);   //나눔고딕
	m_pTempInfoInjury->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoInjury->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoInjury);

	//크리티컬
	char szMagicCritical[64] = { '\0', };
	sprintf_s(szMagicCritical, "크리티컬   %.1f %%", m_fTempCritical);
	m_pTempInfoCritical = cUITextView::Create();
	m_pTempInfoCritical->SetText(szMagicCritical);
	m_pTempInfoCritical->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoCritical->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoCritical->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoCritical->SetPosition(-10, 280 - 7); //마비체
	m_pTempInfoCritical->SetPosition(60, 280);   //나눔고딕
	m_pTempInfoCritical->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoCritical->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoCritical);
	
	//밸런스
	char szMagicBalance[64] = { '\0', };
	sprintf_s(szMagicBalance, "벨런스           %d", m_nTempBalance);
	m_pTempInfoBalance = cUITextView::Create();
	m_pTempInfoBalance->SetText(szMagicBalance);
	m_pTempInfoBalance->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoBalance->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoBalance->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoBalance->SetPosition(-10, 300 - 7); //마비체
	m_pTempInfoBalance->SetPosition(60, 300);   //나눔고딕
	m_pTempInfoBalance->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoBalance->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoBalance);

	//방어
	char szDefense[64] = { '\0', };
	sprintf_s(szDefense, "방어            %d", m_nTempDefense);
	m_pTempInfoDefense = cUITextView::Create();
	m_pTempInfoDefense->SetText(szDefense);
	m_pTempInfoDefense->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoDefense->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoDefense->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoDefense->SetPosition(-10, 240 - 7); //마비체
	m_pTempInfoDefense->SetPosition(170, 220);   //나눔고딕
	m_pTempInfoDefense->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoDefense->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoDefense);

	//보호
	char szProtect[64] = { '\0', };
	sprintf_s(szProtect, "보호            %d", m_nTempProtect);
	m_pTempInfoProtect = cUITextView::Create();
	m_pTempInfoProtect->SetText(szProtect);
	m_pTempInfoProtect->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoProtect->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoProtect->SetSize(ST_SIZE(180, 40));
	//m_pTempInfoProtect->SetPosition(-10, 240 - 7); //마비체
	m_pTempInfoProtect->SetPosition(170, 240);   //나눔고딕
	m_pTempInfoProtect->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoProtect->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoProtect);

	//마법방어
	char szMagicDefense[64] = { '\0', };
	sprintf_s(szMagicDefense, "마법방어      %d", m_nTempMagicDefense);
	m_pTempInfoMagicDefense = cUITextView::Create();
	m_pTempInfoMagicDefense->SetText(szMagicDefense);
	m_pTempInfoMagicDefense->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicDefense->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicDefense->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoMagicDefense->SetPosition(-10, 260 - 7); //마비체
	m_pTempInfoMagicDefense->SetPosition(200, 260);   //나눔고딕
	m_pTempInfoMagicDefense->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicDefense->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicDefense);

	//마법보호
	char szMagicProtect[64] = { '\0', };
	sprintf_s(szMagicProtect, "마법보호      %d", m_nTempMagicProtect);
	m_pTempInfoMagicProtect = cUITextView::Create();
	m_pTempInfoMagicProtect->SetText(szMagicProtect);
	m_pTempInfoMagicProtect->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoMagicProtect->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoMagicProtect->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoMagicProtect->SetPosition(-10, 280 - 7); //마비체
	m_pTempInfoMagicProtect->SetPosition(200, 280);   //나눔고딕
	m_pTempInfoMagicProtect->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoMagicProtect->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoMagicProtect);

	//방어관통
	char szArmorPiercing[64] = { '\0', };
	sprintf_s(szArmorPiercing, "방어관통      %d", m_nTempArmorPiercing);
	m_pTempInfoArmorPiercing = cUITextView::Create();
	m_pTempInfoArmorPiercing->SetText(szArmorPiercing);
	m_pTempInfoArmorPiercing->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	m_pTempInfoArmorPiercing->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pTempInfoArmorPiercing->SetSize(ST_SIZE(120, 40));
	//m_pTempInfoArmorPiercing->SetPosition(-10, 280 - 7); //마비체
	m_pTempInfoArmorPiercing->SetPosition(200, 300);   //나눔고딕
	m_pTempInfoArmorPiercing->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pTempInfoArmorPiercing->SetTag(E_BUTTON_NONE);
	m_pInfoUi->AddChild(m_pTempInfoArmorPiercing);
}

void cUiTestScene::UpdateInfoUi(void)
{
	//m_pPlayer->GetAbilityParamter()->GetStr
	char szHP[32] = { '\0', };
	sprintf_s(szHP, "생명력      %d / %d", m_nTempHP, m_nTempMaxHP);
	m_pTempInfoHP->SetText(szHP);

	char szMP[32] = { '\0', };
	sprintf_s(szMP, "마나         %d / %d", m_nTempMP, m_nTempMaxMP);
	m_pTempInfoMP->SetText(szMP);

	char szStamina[64] = { '\0', };
	sprintf_s(szStamina, "스테미나   %d / %d", nTempStamina, m_nTempMaxStamina);
	m_pTempInfoStamina->SetText(szStamina);

	char szSTR[64] = { '\0', };
	sprintf_s(szSTR, "체력      %d", m_nTempSTR);
	m_pTempInfoSTR->SetText(szSTR);

	char szINT[64] = { '\0', };
	sprintf_s(szINT, "지력      %d", m_nTempINT);
	m_pTempInfoINT->SetText(szINT);

	char szWill[64] = { '\0', };
	sprintf_s(szWill, "의지      %d", m_nTempWill);
	m_pTempInfoWill->SetText(szWill);

	char szLuck[64] = { '\0', };
	sprintf_s(szLuck, "행운      %d", m_nTempLuck);
	m_pTempInfoLuck->SetText(szLuck);

	char szWorkmanship[64] = { '\0', };
	sprintf_s(szWorkmanship, "솜씨      %d", m_nTempWorkmanship);
	m_pTempInfoWorkmanship->SetText(szWorkmanship);

	char szDamage[64] = { '\0', };
	sprintf_s(szDamage, "공격력           %d", m_nTempTotalDamage);
	m_pTempInfoDamage->SetText(szDamage);

	char szMagicDamage[64] = { '\0', };
	sprintf_s(szMagicDamage, "마법공격력      %d", m_nTempTotalMagicDamage);
	m_pTempInfoMagicDamage->SetText(szMagicDamage);

	char szMagicInjury[64] = { '\0', };
	sprintf_s(szMagicInjury, "부상률      %.1f %%", m_fTempInjury);
	m_pTempInfoInjury->SetText(szMagicInjury);

	char szMagicCritical[64] = { '\0', };
	sprintf_s(szMagicCritical, "크리티컬   %.1f %%", m_fTempCritical);
	m_pTempInfoCritical->SetText(szMagicCritical);

	char szMagicBalance[64] = { '\0', };
	sprintf_s(szMagicBalance, "벨런스           %d", m_nTempBalance);
	m_pTempInfoBalance->SetText(szMagicBalance);

	char szDefense[64] = { '\0', };
	sprintf_s(szDefense, "방어            %d", m_nTempDefense);
	m_pTempInfoDefense->SetText(szDefense);

	char szProtect[64] = { '\0', };
	sprintf_s(szProtect, "보호            %d", m_nTempProtect);
	m_pTempInfoProtect->SetText(szProtect);

	char szMagicDefense[64] = { '\0', };
	sprintf_s(szMagicDefense, "마법방어      %d", m_nTempMagicDefense);
	m_pTempInfoMagicDefense->SetText(szMagicDefense);

	char szMagicProtect[64] = { '\0', };
	sprintf_s(szMagicProtect, "마법보호      %d", m_nTempMagicProtect);
	m_pTempInfoMagicProtect->SetText(szMagicProtect);

	char szArmorPiercing[64] = { '\0', };
	sprintf_s(szArmorPiercing, "방어관통      %d", m_nTempArmorPiercing);
	m_pTempInfoArmorPiercing->SetText(szArmorPiercing);
}