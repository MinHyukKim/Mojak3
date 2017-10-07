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
	, m_nTempMaxHP(70) , m_nTempHP(70)
	, m_nTempMaxMP(60) , m_nTempMP(60)
	, m_nTempMaxStamina(75) , nTempStamina(75)
	, m_nTempSTR(30) , m_nTempINT(23) , m_nTempWill(33) , m_nTempLuck(19) , m_nTempWorkmanship(26)
	, m_nTempDamege(24) , m_nTempTotalDamage(24)
	, m_nTempMagicDamege(2) , m_nTempTotalMagicDamage(2)
	, m_fTempInjury(3.0f) , m_fTempCritical(17.2f)
	, m_nTempBalance(53) , m_nTempDefense(9) , m_nTempProtect(0)
	, m_nTempMagicDefense(2) , m_nTempMagicProtect(0) , m_nTempArmorPiercing(1)
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
	//대화창
	, m_pDialogUi(NULL)
	, m_isDialogOpen(false)
	//대화NPC 종류 태스트용 나오 맨첨은 NONE로 바꾸기
	, m_eDialogNPCKind(E_DIALOG_NPC_NAO)
	//대화 순서
	, m_eDialogText(E_TEXT_01)
	//닫기 관련
	, m_pUiExit(NULL)
	, m_isExitUiOn(false)
	//대화문 끝 여부
	, m_isDialogFin(false)
	//퀘 수락 여부
	, m_isAcceptQuest(false)
	//퀘 완료 여부
	, m_isQuestFin(false)
	//퀵슬롯 관련
	, m_pUiQuickSiot(NULL)
	//슬롯 등록
	, m_eQuickSiot01(E_QUICK_SIOT_NONE_01)
	, m_eQuickSiot02(E_QUICK_SIOT_NONE_02)
	, m_eQuickSiot03(E_QUICK_SIOT_NONE_03)
	, m_eQuickSiot04(E_QUICK_SIOT_NONE_04)
	, m_eQuickSiot05(E_QUICK_SIOT_NONE_05)
{
	D3DXMatrixIdentity(&m_matWorldMatrix);
	m_vecTempPlayerItem.reserve(INVMAX);
	m_vecInventoryUiBlock.reserve(INVMAX);
	m_nWearDef = 2;
	m_nShoesDef = 2;
	m_nDialogTextNum = 0;
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

//	RECT wrc;
	GetClientRect(g_hWnd, &m_Wrc);

	mainUiLocalX = m_Wrc.right / 2 - 220;			//메인 틀 x 300
	mainUiLocalY = m_Wrc.bottom / 2 + 235;			//메인 틀 y 502
	mainButtonH = -25;			//메인 버튼들 높이 -25
	mainButtoninterval = 40;	//메인 버튼들 가로 간격(크기) 40
	mainButtonSrart = 160;		//메인 버튼들 최초 시작 위치 160

	//베이스 버튼(태스트 택스트 포함
	this->SetupBaseButton();

	//임시 태스트용
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTesterSize->SetTexture("Texture/Ui/skillDefense.png");
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
	//대화 창 셋업
	this->SetupDialogUi();
	//임시 플레이어 능력치
	m_nBasicDef = g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDefence();
	//대화창받기
	m_isDialogOpen = g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDialogOpen();

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
	//대화창
	SAFE_RELEASE(m_pDialogUi);
	//메인 종료
	SAFE_RELEASE(m_pUiExit);
	//퀵
	SAFE_RELEASE(m_pUiQuickSiot);
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

	//대화창받기
	m_isDialogOpen = g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDialogOpen();
	if (g_pInputManager->IsOnceKeyUp('G') && m_pDialogUi)
	{
		m_isDialogOpen = !m_isDialogOpen;
		if (m_isDialogOpen == false)
		{
			m_pDialogBackImage->isOver = false;
		}
	}

	if (m_pUiRoot) m_pUiRoot->Update();										//ui기본 베이스
//	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Update();				//ui 스킬창
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Update();				//ui 퀘스트 창
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Update();  //ui 인벤토리 창

	if (m_pDialogUi && m_isDialogOpen) m_pDialogUi->Update();				//ui 대화창
	if (m_pUiQuickSiot) m_pUiQuickSiot->Update();							//ui 퀵슬롯 창

	if (m_pUiExit && m_isExitUiOn) m_pUiExit->Update();						//메인->나가기 창

	if (m_pInfoUi && m_isInfoWindowOn)										//ui info창
	{
		m_pInfoUi->Update();		
	}
	UpdateInfoUi();
	if (m_pSkillUi && m_isSkillWindowOn)
	{
		m_pSkillUi->Update();
		UpdateSkillUi();
	}


	//임시 플레이어
	SAFE_UPDATE(m_pPlayer);
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
	//대화 변경
	this->changeDialogText();
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
	//대화 조건 넣기
	if (m_pDialogUi && m_isDialogOpen) m_pDialogUi->Render(m_pSprite);
	//종료 관련
	if (m_pUiExit && m_isExitUiOn) m_pUiExit->Render(m_pSprite);
	//퀵슬롯 관련
	if (m_pUiQuickSiot) m_pUiQuickSiot->Render(m_pSprite);

	//크기 태스트용
//	if (m_pUiTestRoot) m_pUiTestRoot->Render(m_pSprite);


}

bool cUiTestScene::GetMoveingOK()
{
	//매인
	if (m_pMainMainButton->isOver) return false;
	if (m_pMainRootImageViewMove->isOver) return false;
	if (m_pMinButton->isOver) return false;
	if (m_pInfoButton->isOver) return false;
	if (m_pSkillButton->isOver) return false;
	if (m_pQuestButton->isOver) return false;
	if (m_pInventoryButton->isOver) return false;
	//각자 ui창들
	if (m_pInfoUiMoveing->isOver) return false;
	if (m_pInfoUiImage->isOver) return false;
	if (m_pSkillUiMoveing->isOver) return false;
	if (m_pSkillUiImage->isOver) return false;
	if (m_pQuestUiMoveing->isOver) return false;
	if (m_pQuestUiImage->isOver) return false;
	if (m_pInventoryUiMoveing->isOver) return false;
	if (m_pInventoryUiImage->isOver) return false;
	//대화창 막기
	if (/*m_pDialogUi &&*/ m_pDialogBackImage->isOver) return false;
	//닫기 버튼용
	if (m_pInfoCloseButton->isOver) return false;
	if (m_pSkillCloseButton->isOver) return false;
	if (m_pQuestCloseButton->isOver) return false;
	if (m_pInventoryCloseButton->isOver) return false;
	if (m_pDialogCloseButton->isOver) return false;
	//메인->종료용
	if (m_pUiExitBackImage->isOver) return false;
	
	return true;
}


//딜리게이트(클릭)
void cUiTestScene::OnClick(cUIButton * pSender)
{

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		//클릭했을 때 화면이 닫히면 마우스 오버 조건을 flase로
		if (m_isInfoWindowOn == false)
		{
			m_pInfoUiMoveing->isOver = false;
			m_pInfoUiImage->isOver = false;
		//	m_pInfoCloseButton->isOver = false;
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
		if (m_isInventoryWindowOn == false)
		{
			m_pInventoryUiMoveing->isOver = false;
			m_pInventoryUiImage->isOver = false;
		}
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MAIN)
	{
		if (m_isExitUiOn == false)
		{
			m_pUiExitBackImage->isOver = false;
		}
		m_isExitUiOn = !m_isExitUiOn;
	}
	else if (pSender->GetTag() == E_BUTTON_TEST1)
	{
		isPickUpItem = !isPickUpItem;
	}

	else if (pSender->GetTag() == E_BUTTON_INFO_CLOSE)
	{
		m_isInfoWindowOn = false;
		if (m_isInfoWindowOn == false)
		{
			m_pInfoUiMoveing->isOver = false;
			m_pInfoUiImage->isOver = false;
			m_pInfoCloseButton->isOver = false;
		}	
	//	m_isInfoWindowOn = !m_isInfoWindowOn;B
	}
	else if (pSender->GetTag() == E_BUTTON_SKILL_CLOSE)
	{
		m_isSkillWindowOn = false;
		if (m_isSkillWindowOn == false)
		{
			m_pSkillUiMoveing->isOver = false;
			m_pSkillUiImage->isOver = false;
			m_pSkillCloseButton->isOver = false;
		}
	//	m_isSkillWindowOn = !m_isSkillWindowOn;
	}
	else if (pSender->GetTag() == E_BUTTON_QUEST_CLOSE)
	{
		m_isQuestWindowOn = false;
		if (m_isQuestWindowOn == false)
		{
			m_pQuestUiMoveing->isOver = false;
			m_pQuestUiImage->isOver = false;
			m_pQuestCloseButton->isOver = false;
		}
	//	m_isQuestWindowOn = !m_isQuestWindowOn;
	}
	else if (pSender->GetTag() == E_BUTTON_INVENTORY_CLOSE)
	{
		m_isInventoryWindowOn = false;
		if (m_isInventoryWindowOn == false)
		{
			m_pInventoryUiMoveing->isOver = false;
			m_pInventoryUiImage->isOver = false;
			m_pInventoryCloseButton->isOver = false;
		}
	//	m_isInventoryWindowOn = !m_isInventoryWindowOn;
	}
	else if (pSender->GetTag() == E_BUTTON_DIALOG_CLOSE)
	{
	//	m_isDialogOpen = false;
		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDialogOpen(false);
		if (/*m_isDialogOpen == false*/g_pObjectManager->GetPlayer()->GetAbilityParamter()->GetDialogOpen() == false)
		{
			m_pDialogBackImage->isOver = false;
			m_pDialogCloseButton->isOver = false;
			m_nDialogTextNum = 0;
		}
	}
	else if (pSender->GetTag() == E_BUTTON_EXIT)
	{
		PostQuitMessage(0);
	}
	else if (pSender->GetTag() == E_BUTTON_USE_SMASH)
	{
	//	if (m_eQuickSiot01 == E_QUICK_SIOT_NONE_01)
	//	{
	//		m_pUiQuickSiot1->SetTexture("Texture/Ui/skillSmash.png"
	//			, "Texture/Ui/skillSmash.png", "Texture/Ui/skillSmash.png");
	//		m_eQuickSiot01 = E_QUICK_SIOT_SMASH_01;
	//	}
	//	else if(m_eQuickSiot01 != E_QUICK_SIOT_NONE_01)
	}
	else if (pSender->GetTag() == E_BUTTON_USE_COUNTER)
	{

	}

	//대화창 관련 (열린 상태에서 NPC가 나오라면)
	if (m_isDialogOpen && m_eDialogNPCKind == E_DIALOG_NPC_NAO)
	{
		if (pSender->GetTag() == E_BUTTON_DIALOG_PREV && m_nDialogTextNum > 0 /*m_eDialogText > E_TEXT_01*/)
		{
			m_nDialogTextNum = m_nDialogTextNum - 1;
		}
		else if (pSender->GetTag() == E_BUTTON_DIALOG_NEXT && m_nDialogTextNum < 2)
		{
			m_nDialogTextNum += 1;
		}
	}

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