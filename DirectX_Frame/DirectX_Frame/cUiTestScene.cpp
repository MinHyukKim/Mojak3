#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//임시 플레이어
#include "cPlayer.h"
#include "cCamera.h"
//이미지
#include "cImage.h"

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isLbuttonDown(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
	, m_pUiTestRoot(NULL)
	, m_isMainMin(false)
	, m_pMainRootImageView(NULL)
	, m_pMainMainButton(NULL)
	, m_pUiTesterSize(NULL)
	//열고닫힘 여부
	, m_isMainWindowOn(false)
	, m_isInfoWindowOn(false)
	, m_isSkillWindowOn(false)
	, m_isQuestWindowOn(false)
	, m_isInventoryWindowOn(false)
	//
	, m_pInfoUi(NULL)
	, m_pSkillUi(NULL)
	, m_pQuestUi(NULL)
	, m_pInventoryUi(NULL)
	, invX(20)
	, invY(20)
	, skillX(680)
	, skillY(20)
	, infoX(354)
	, infoY(20)
	, queX(500)
	, queY(60)
	//아이탬 픽킹
	, isPickUpItem(false)
	//착용 여부
	, m_isTorsoMount(0) 
	, m_isWeaponHandMount(false)
	, m_isSubHandMount(false)
	, m_isShoesMount(-1)
	//임시 플레이어
	, m_pPlayer(NULL)
	, m_pMainCamera(NULL)
	//임시 스탯
	, m_nTempMaxHP(70)
	, m_nTempHP(70)
	, m_nTempMaxMP(60)
	, m_nTempMP(60)
	, m_nTempMaxStamina(75)
	, nTempStamina(75)
	, m_nTempSTR(30)
	, m_nTempINT(23)
	, m_nTempWill(33)
	, m_nTempLuck(19)
	, m_nTempWorkmanship(26)
	, m_nTempDamege(24)
	, m_nTempTotalDamage(24)
	, m_nTempMagicDamege(2)
	, m_nTempTotalMagicDamage(2)
	, m_fTempInjury(3.0f)
	, m_fTempCritical(17.2f)
	, m_nTempBalance(53)
	, m_nTempDefense(9)
	, m_nTempProtect(0)
	, m_nTempMagicDefense(2)
	, m_nTempMagicProtect(0)
	, m_nTempArmorPiercing(1)
	, m_pHpMaxImage(NULL)
	, m_pHpImage(NULL)
	//매인 게이지바들 위치
	, m_nMainHPx(50)
	, m_nMainHPy(2)
	, m_nMainMPx(50)
	, m_nMainMPy(12)
	, m_nMainStaminaX(50)
	, m_nMainStaminaY(23)
	, m_nMainEXPx(160)
	, m_nMainEXPy(20)
	, m_eEquipTorso(E_TORSO_WEAR_01)
	, m_eEquipShoes(E_SHOES_EMPTY)
	, m_eEquipWeaponHand(E_WEAPON_EMPTY)
	, m_nItemMax(3)
{
	D3DXMatrixIdentity(&m_matWorldMatrix);
	m_vecTempPlayerItem.reserve(INVMAX);
	m_vecInventoryUiBlock.reserve(INVMAX);
	m_nWearDef = 2;
	m_nShoesDef = 2;
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

	//베이스 버튼(태스트 택스트 포함
	this->SetupBaseButton();

	//임시 태스트용
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTesterSize->SetTexture("Texture/Ui/dialog2.png");
	m_pUiTesterSize->SetPosition(mainUiLocalX - 20, mainUiLocalY - 140);
	m_pUiTesterSize->m_Alpha = 180;
	m_pUiTestRoot = m_pUiTesterSize;	


	//플레이어 정보 창 셋업
	this->SetupInfoUi();
	//스킬 창 셋업
	this->SetupSkillUi();
	//퀘스트 창 셋업
	this->SetupQuestUi();
	//인벤토리 창 셋업
	this->SetupInventoryUi();
	//임시 플레이어 셋업
	m_nBasicDef = g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefence();
//	this->SetUpTempPlayer();

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
	SAFE_RELEASE(m_pUiTestRoot);
	SAFE_RELEASE(m_pInfoUi);
	SAFE_RELEASE(m_pSkillUi);
	SAFE_RELEASE(m_pQuestUi);
	SAFE_RELEASE(m_pInventoryUi);
	//임시용 플레이어
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pMainCamera);
}

void cUiTestScene::Update(void)
{
	this->changeMainButtonColor();
	////메인창 내리기 (다시 만들기)
	//if (m_isMainMin == true) m_pMainRootImageView->SetPosition(300, 520);
	//else m_pMainRootImageView->SetPosition(300, 502);
	//키입력
	if (g_pInputManager->IsOnceKeyDown('Q'))
	{
		m_isQuestWindowOn = !m_isQuestWindowOn;
	}
	else if (g_pInputManager->IsOnceKeyUp('Q'))
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isQuestWindowOn == false)
		{
			m_pQuestUiMoveing->isOver = false;
			m_pQuestUiImage->isOver = false;
		}
	}

	if (g_pInputManager->IsOnceKeyDown('K'))
	{
		m_isSkillWindowOn = !m_isSkillWindowOn;
	}
	else if (g_pInputManager->IsOnceKeyUp('K'))
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isSkillWindowOn == false)
		{
			m_pSkillUiMoveing->isOver = false;
			m_pSkillUiImage->isOver = false;
		}
	}
	if (g_pInputManager->IsOnceKeyDown('I'))
	{
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
	}
	else if (g_pInputManager->IsOnceKeyUp('I'))
	{
		if (m_isInventoryWindowOn == false)
		{
			m_pInventoryUiMoveing->isOver = false;
			m_pInventoryUiImage->isOver = false;
		}
	}

	if (g_pInputManager->IsOnceKeyDown('C'))
	{
		m_isInfoWindowOn = !m_isInfoWindowOn;
	}
	else if (g_pInputManager->IsOnceKeyUp('C'))
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isInfoWindowOn == false)
		{
			m_pInfoUiMoveing->isOver = false;
			m_pInfoUiImage->isOver = false;
		}
	}

	if (m_pUiRoot) m_pUiRoot->Update();
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Update();
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Update();
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Update();
	if (m_pInfoUi && m_isInfoWindowOn)
	{
		m_pInfoUi->Update();
		UpdateInfoUi();
	}

	//임시 플레이어
	SAFE_UPDATE(m_pPlayer);
	//m_matWorldMatrix._41 = m_pTempInfoHP->GetPosition().x;
	//m_matWorldMatrix._42 = m_pTempInfoHP->GetPosition().y;
	//이동
	this->MoveUiWindow();
	//메인 게이지 및 최소화 업뎃
	this->UpdateMainUi();
	
	//수치변화 시험용
	if (g_pInputManager->IsOnceKeyDown('M'))
	{
		m_nTempHP -= 1;
		m_nTempMP -= 1;
		nTempStamina -= 1;
		m_nTempSTR -= 1;
		m_nTempINT -= 1;
		m_nTempWill -= 1;
		m_nTempLuck -= 1;
		m_nTempWorkmanship -= 1;
		m_nTempTotalDamage -= 1;
		m_nTempTotalMagicDamage -= 1;
		m_fTempInjury -= 1.0f;
		m_fTempCritical -= 1.0f;
		m_nTempBalance -= 1;
		m_nTempDefense -= 1;
		m_nTempProtect -= 1;
		m_nTempMagicDefense -= 1;
		m_nTempMagicProtect -= 1;
		m_nTempArmorPiercing += 1;
	}

	if (m_pUiTestRoot) m_pUiTestRoot->Update();
	//매쉬 변경
	this->changePlayerMesh();
	//인벤 색 변경
	this->changeInventoryImage();
//	m_vecTempPlayerItem.resize(INVMAX);
}

void cUiTestScene::Render(void)
{

	g_pD3DDevice->SetTexture(0, m_pTexture);
	SAFE_RENDER(m_pPlayer);
	if (m_pUiRoot) m_pUiRoot->Render(m_pSprite);
	if (m_pInfoUi && m_isInfoWindowOn) m_pInfoUi->Render(m_pSprite);
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Render(m_pSprite);
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Render(m_pSprite);
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Render(m_pSprite);

	//크기 태스트용
	if (m_pUiTestRoot) m_pUiTestRoot->Render(m_pSprite);


}

bool cUiTestScene::GetMoveingOK()
{
	if (m_pMainMainButton->isOver) return false;
	if (m_pMainRootImageViewMove->isOver) return false;
	if (m_pMinButton->isOver) return false;
	if (m_pInfoButton->isOver) return false;
	if (m_pSkillButton->isOver) return false;
	if (m_pQuestButton->isOver) return false;
	if (m_pInventoryButton->isOver) return false;
	if (m_pInfoUiMoveing->isOver) return false;
	if (m_pInfoUiImage->isOver) return false;
	if (m_pSkillUiMoveing->isOver) return false;
	if (m_pSkillUiImage->isOver) return false;
	if (m_pQuestUiMoveing->isOver) return false;
	if (m_pQuestUiImage->isOver) return false;
	if (m_pInventoryUiMoveing->isOver) return false;
	if (m_pInventoryUiImage->isOver) return false;
	
	return true;
}


//딜리게이트(클릭)
void cUiTestScene::OnClick(cUIButton * pSender)
{
//	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
//	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
//	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isInfoWindowOn == false)
		{
			m_pInfoUiMoveing->isOver = false;
			m_pInfoUiImage->isOver = false;
		}
		m_isInfoWindowOn = !m_isInfoWindowOn;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isSkillWindowOn == false)
		{
			m_pSkillUiMoveing->isOver = false;
			m_pSkillUiImage->isOver = false;
		}
		m_isSkillWindowOn = !m_isSkillWindowOn;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isQuestWindowOn == false)
		{
			m_pQuestUiMoveing->isOver = false;
			m_pQuestUiImage->isOver = false;
		}
		m_isQuestWindowOn = !m_isQuestWindowOn;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
	//	if (m_isInventoryWindowOn == false)
	//	{
		//	m_pInventoryUiMoveing->isOver = false;
		//	m_pInventoryUiImage->isOver = false;
	//	}
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}
	else if (pSender->GetTag() == E_BUTTON_TEST1)
	{
		isPickUpItem = !isPickUpItem;
	}
//	else if (pSender->GetTag() == E_BUTTON_INFO_CLOSE)
//	{
//	//	if (m_isInfoWindowOn) m_isInfoWindowOn = false;
//		m_isInfoWindowOn = !m_isInfoWindowOn;
//	}
//	else if (pSender->GetTag() == E_BUTTON_SKILL_CLOSE)
//	{
//	//	if (m_isSkillWindowOn) m_isSkillWindowOn = false;
//		m_isSkillWindowOn = !m_isSkillWindowOn;
//	}
//	else if (pSender->GetTag() == E_BUTTON_QUEST_CLOSE)
//	{
//	//	if (m_isQuestWindowOn) m_isQuestWindowOn = false;
//		m_isQuestWindowOn = !m_isQuestWindowOn;
//	}
//	else if (pSender->GetTag() == E_BUTTON_INVENTORY_CLOSE)
//	{
//	//	if (m_isInventoryWindowOn) m_isInventoryWindowOn = false;
//		m_isInventoryWindowOn = !m_isInventoryWindowOn;
//	}

}

void cUiTestScene::changeMainButtonColor(void)
{
	if (m_isInfoWindowOn)
	{
		m_pInfoButton->SetTexture("Texture/Ui/on_player_info_button_up.png",
			"Texture/Ui/on_player_info_button_over.png",
			"Texture/Ui/on_player_info_button_down.png");
	}
	else if (m_isInfoWindowOn == false)
	{
		m_pInfoButton->SetTexture("Texture/Ui/player_info_button_up.png",
			"Texture/Ui/player_info_button_over.png",
			"Texture/Ui/player_info_button_down.png");
	}

	if (m_isSkillWindowOn)
	{
		m_pSkillButton->SetTexture("Texture/Ui/on_player_sikill_button_up.png",
			"Texture/Ui/on_player_sikill_button_over.png",
			"Texture/Ui/on_player_sikill_button_down.png");
	}
	else if (m_isSkillWindowOn == false)
	{
		m_pSkillButton->SetTexture("Texture/Ui/player_sikill_button_up.png",
			"Texture/Ui/player_sikill_button_over.png",
			"Texture/Ui/player_sikill_button_down.png");
	}

	if (m_isQuestWindowOn)
	{
		m_pQuestButton->SetTexture("Texture/Ui/on_player_quest_button_up.png",
			"Texture/Ui/on_player_quest_button_over.png",
			"Texture/Ui/on_player_quest_button_down.png");
	}
	else if (m_isQuestWindowOn == false)
	{
		m_pQuestButton->SetTexture("Texture/Ui/player_quest_button_up.png",
			"Texture/Ui/player_quest_button_over.png",
			"Texture/Ui/player_quest_button_down.png");
	}

	if (m_isInventoryWindowOn)
	{
		m_pInventoryButton->SetTexture("Texture/Ui/on_player_inventory_button_up.png",
			"Texture/Ui/on_player_inventory_button_over.png",
			"Texture/Ui/on_player_inventory_button_down.png");
	}
	else if (m_isInventoryWindowOn == false)
	{
		m_pInventoryButton->SetTexture("Texture/Ui/player_inventory_button_up.png",
			"Texture/Ui/player_inventory_button_over.png",
			"Texture/Ui/player_inventory_button_down.png");
	}
}

void cUiTestScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}