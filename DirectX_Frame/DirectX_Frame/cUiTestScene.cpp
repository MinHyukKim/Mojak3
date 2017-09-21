#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

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
	, m_isInventoryUiMove(false)
{
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
	m_pUiTesterSize->SetTexture("Texture/Ui/inventoryBase.png");
	m_pUiTesterSize->SetPosition(10, 10);
	m_pUiTestRoot = m_pUiTesterSize;
	
//	//커마 창 머리
//	m_pCustomImageHead = cUIImageView::Create();
//	m_pCustomImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
//	m_pCustomImageHead->SetPosition(m_nX, m_nY);
//	m_pCustomImageHead->m_Alpha = 200;
//	m_pCustomUi = m_pCustomImageHead;
//	//커마 창
//	m_pCustomImage = cUIImageView::Create();
//	m_pCustomImage->SetTexture("Texture/Ui/customUiBase2.png");
//	m_pCustomImage->SetPosition(2, 48);
//	m_pCustomImage->m_Alpha = 180;
//	m_pCustomUi->AddChild(m_pCustomImage);

	//정보 창 머리
	m_pInfoUiImageHead = cUIImageView::Create();
	m_pInfoUiImageHead->SetTexture("Texture/Ui/infoBaseHead1.png");
	m_pInfoUiImageHead->SetPosition(354, 20);
	m_pInfoUiImageHead->m_Alpha = 200;
	m_pInfoUi = m_pInfoUiImageHead;
	//정보 베이스 창
	m_pInfoUiImage = cUIImageView::Create();
	m_pInfoUiImage->SetTexture("Texture/Ui/Base.png");
	m_pInfoUiImage->SetPosition(2, 48);
	m_pInfoUiImage->m_Alpha = 180;
	m_pInfoUi->AddChild(m_pInfoUiImage);

	//스킬 머리 창
	m_pSkillUiImageHead = cUIImageView::Create();
	m_pSkillUiImageHead->SetTexture("Texture/Ui/skillBaseHead1.png");
	m_pSkillUiImageHead->SetPosition(680, 20);
	m_pSkillUiImageHead->m_Alpha = 200;
	m_pSkillUi = m_pSkillUiImageHead;
	//스킬 창 베이스
	m_pSkillUiImage = cUIImageView::Create();
	m_pSkillUiImage->SetTexture("Texture/Ui/Base.png");
	m_pSkillUiImage->SetPosition(2, 48);
	m_pSkillUiImage->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillUiImage);

	//퀘스트 창 머리
	m_pQuestUiImageHead = cUIImageView::Create();
	m_pQuestUiImageHead->SetTexture("Texture/Ui/questBaseHead1.png");
	m_pQuestUiImageHead->SetPosition(500, 60);
	m_pQuestUiImageHead->m_Alpha = 200;
	m_pQuestUi = m_pQuestUiImageHead;
	//퀘스트 창
	m_pQuestUiImage = cUIImageView::Create();
	m_pQuestUiImage->SetTexture("Texture/Ui/Base.png");
	m_pQuestUiImage->SetPosition(2, 48);
	m_pQuestUiImage->m_Alpha = 180;
	m_pQuestUi->AddChild(m_pQuestUiImage);

	//인벤토리 창 셋업
	this->SetupInventoryUi();

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
//	SAFE_RELEASE(m_pMainRootImageView);
	SAFE_RELEASE(m_pUiTestRoot);
//	SAFE_RELEASE(m_pMainMainButton);
	if(m_pInfoUi) SAFE_RELEASE(m_pInfoUi);
	if(m_pSkillUi) SAFE_RELEASE(m_pSkillUi);
	if(m_pQuestUi) SAFE_RELEASE(m_pQuestUi);
	if(m_pInventoryUi) SAFE_RELEASE(m_pInventoryUi);
}

void cUiTestScene::Update(void)
{
	this->changeMainButtonColor();
	//메인창 내리기 (다시 만들기)
	if (m_isMainMin == true) m_pMainRootImageView->SetPosition(300, 520);
	else m_pMainRootImageView->SetPosition(300, 502);

	if (m_pUiRoot) m_pUiRoot->Update();
	if (m_pInfoUi && m_isInfoWindowOn) m_pInfoUi->Update();
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Update();
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Update();
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Update();

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (m_pInventoryUiMoveing->isOver)
	{
		m_isInventoryUiMove = true;
	}
	else if (m_pInventoryUiMoveing->isOver == false)
	{
		m_isInventoryUiMove = false;
	}
	if (m_isInventoryUiMove)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON))
		{
			m_pInventoryUiImageHead->SetPosition(ptMouse.x, ptMouse.y);
		}
	}

	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	
	if (m_pUiTestRoot) m_pUiTestRoot->Update();
}

void cUiTestScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	if (m_pUiRoot) m_pUiRoot->Render(m_pSprite);
	if (m_pInfoUi && m_isInfoWindowOn) m_pInfoUi->Render(m_pSprite);
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Render(m_pSprite);
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Render(m_pSprite);
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Render(m_pSprite);
	//크기 태스트용
	//if (m_pUiTestRoot) m_pUiTestRoot->Render(m_pSprite);
}

//딜리게이트(클릭)
void cUiTestScene::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		m_isInfoWindowOn = !m_isInfoWindowOn;
		pTextView->SetText("플레이어 정보창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		m_isSkillWindowOn = !m_isSkillWindowOn;
		pTextView->SetText("플레이어 스킬창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		m_isQuestWindowOn = !m_isQuestWindowOn;
		pTextView->SetText("퀘스트창 구현하기");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
		pTextView->SetText("인벤토리 창 구현하기");
	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
//	{
//		pTextView->SetText("재능창 구현하기(추가구성)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
//	{
//		pTextView->SetText("액션 창 구현하기(추가구성)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
//	{
//		pTextView->SetText("펫 창 구현하기(추가 구성)");
//	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}

}

void cUiTestScene::OnMouseOver(cUIButton * pSender)
{
	if (pSender->GetTag() == E_INVENTORY_MOVE)
	{
		//m_isInventoryUiMove = true;
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