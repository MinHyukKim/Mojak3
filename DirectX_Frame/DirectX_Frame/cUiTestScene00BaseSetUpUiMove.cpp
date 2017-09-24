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

void cUiTestScene::SetupBaseButton(void)
{
	//테스트용 메인버튼들
	m_pMainRootImageView = cUIImageView::Create();
	m_pMainRootImageView->SetTexture("Texture/Ui/TestRoot2.png");
	m_pMainRootImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pMainRootImageView->m_Alpha = 200;
	m_pUiRoot = m_pMainRootImageView;

//	cUITextView* pTextView = cUITextView::Create();
//	pTextView->SetText("태스트용");
//	pTextView->SetFontType(g_pFontManager->E_NORMAL);
//	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
//	pTextView->SetSize(ST_SIZE(400, 500));
//	pTextView->SetPosition(0, -300);
//	pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	pTextView->SetTag(E_TEXT_VIEW);
//	m_pUiRoot->AddChild(pTextView);

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

	//	pButton = cUIButton::Create();
	//	pButton->SetTexture("Texture/Ui/player_ability_button_up.png", 
	//		"Texture/Ui/player_ability_button_over.png",
	//		"Texture/Ui/player_ability_button_down.png");
	//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 4, mainButtonH);
	//	pButton->SetDelegate(this);
	//	pButton->SetTag(E_MAIN_BUTTON_ABILITY);
	//	m_pUiRoot->AddChild(pButton);
	//
	//	pButton = cUIButton::Create();
	//	pButton->SetTexture("Texture/Ui/player_action_button_up.png", 
	//		"Texture/Ui/player_action_button_over.png",
	//		"Texture/Ui/player_action_button_down.png");
	//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 5, mainButtonH);
	//	pButton->SetDelegate(this);
	//	pButton->SetTag(E_MAIN_BUTTON_ACTION);
	//	m_pUiRoot->AddChild(pButton);
	//
	//	pButton = cUIButton::Create();
	//	pButton->SetTexture("Texture/Ui/player_pet_button_up.png", 
	//		"Texture/Ui/player_pet_button_over.png",
	//		"Texture/Ui/player_pet_button_down.png");
	//	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 6, mainButtonH);
	//	pButton->SetDelegate(this);
	//	pButton->SetTag(E_MAIN_BUTTON_PET);
	//	m_pUiRoot->AddChild(pButton);

	cUIButton* pMinButton = cUIButton::Create();
	pMinButton->SetTexture("Texture/Ui/button_min_up.png",
		"Texture/Ui/button_min_over.png",
		"Texture/Ui/button_min_up.png");
	pMinButton->SetPosition(mainButtonSrart + 190, mainButtonH + 26);
	pMinButton->SetDelegate(this);
	pMinButton->SetTag(E_MAIN_BUTTON_MIN);
	m_pUiRoot->AddChild(pMinButton);

	m_pMainMainButton = cUIButton::Create();
	m_pMainMainButton->SetTexture("Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-up.png",
		"Texture/Ui/main_button-down.png");
	m_pMainMainButton->SetPosition(mainButtonSrart - 150, mainButtonH + 25);
	m_pMainMainButton->SetDelegate(this);
	m_pMainMainButton->SetTag(E_MAIN_BUTTON_MAIN);
	m_pUiRoot->AddChild(m_pMainMainButton);
}

void cUiTestScene::MoveUiWindow(void)
{
	//무빙 관련
	POINT ptMouse = m_ptMouse;				//이전 좌표 저장

	GetCursorPos(&m_ptMouse);				//마우스 좌표(맴버변수 포인터)
	ScreenToClient(g_hWnd, &m_ptMouse);		//마우스 좌표(맴버변수 포인터)

	float nDeltaX = (m_ptMouse.x - ptMouse.x); //현재 좌표 - 이전 좌표 (음직인 양)
	float nDeltaY = (m_ptMouse.y - ptMouse.y); //현재 좌표 - 이전 좌표 (음직인 양)

	//인벤 창 무빙
//	if(m_pInventoryUiMoveing->GetButtonStatus() == 1)
	if (m_pInventoryUiMoveing->isOver)
	{
		if (g_pInputManager->IsStayKeyDown(VK_LBUTTON) 
			&& m_pInfoUiMoveing->isClick == false
			&& m_pSkillUiMoveing->isClick == false
			&& m_pQuestUiMoveing->isClick == false)
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
			&& m_pQuestUiMoveing->isClick == false)
		{
			m_pInfoUiMoveing->isClick = true;
		//	infoX = m_pInfoUiImageHead->GetPosition().x + nDeltaX;
		//	infoY = m_pInfoUiImageHead->GetPosition().y + nDeltaY;
		//
		//	m_pInfoUiImageHead->SetPosition(infoX, infoY);
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
			&& m_pQuestUiMoveing->isClick == false)
		{
			m_pSkillUiMoveing->isClick = true;
			/*skillX = m_pSkillUiImageHead->GetPosition().x + nDeltaX;
			skillY = m_pSkillUiImageHead->GetPosition().y + nDeltaY;

			m_pSkillUiImageHead->SetPosition(skillX, skillY);*/
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
			&& m_pInfoUiMoveing->isClick == false)
		{
			m_pQuestUiMoveing->isClick = true;
			//queX = m_pQuestUiImageHead->GetPosition().x + nDeltaX;
			//queY = m_pQuestUiImageHead->GetPosition().y + nDeltaY;

			//m_pQuestUiImageHead->SetPosition(queX, queY);
		}
		else m_pQuestUiMoveing->isClick = false;
	}
	else if (m_pQuestUiMoveing->isClick)
	{
		m_pQuestUiMoveing->isClick = true;
		queX = m_pQuestUiImageHead->GetPosition().x + nDeltaX;
		queY = m_pQuestUiImageHead->GetPosition().y + nDeltaY;

		m_pQuestUiImageHead->SetPosition(queX, queY);
	}

	//탬무빙 태스트
	if (m_pTempItem->isOver)
	{
		if (g_pInputManager->IsOnceKeyDown(VK_LBUTTON))
		{
			isPickUpItem = !isPickUpItem;
		}
		if (isPickUpItem == true)
		{
			m_pTempItem->isClick = true;
			float temX = m_pTempItem->GetPosition().x + nDeltaX;
			float temY = m_pTempItem->GetPosition().y + nDeltaY;
		
			m_pTempItem->SetPosition(temX, temY);
		}
		//else m_pTempItem->isClick = false;

	//	else if (m_pTempItem->isClick)
	//	{
	//		float temX = m_pTempItem->GetPosition().x + nDeltaX;
	//		float temY = m_pTempItem->GetPosition().y + nDeltaY;
	//
	//		m_pTempItem->SetPosition(temX, temY);
	//	}

		if (isPickUpItem == false)
		{
			m_pTempItem->isClick = false;
			RECT rc;
			//몸통 장착시
			if (IntersectRect(&rc, &(m_pTempItem->rc), &(m_pInventoryUiEquipTorso->rc)))
			{
				m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("바디02"));
				m_pTempItem->SetPosition(60, 147);
				m_isTorsoMount = true;
			}
			//인벤토리 칸의 나머지 클릭하면 재자리로(미완)
			else if (IntersectRect(&rc, &(m_pTempItem->rc), &(m_pInventoryUiImage->rc)))
			{
				m_pTempItem->SetPosition(160, 90);
				m_isTorsoMount = false;
			}
			for (int i = 0; i < 60; i++)
			{
				if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_pTempItem->rc)))
				{
					//인벤토리 칸의 나머지 클릭하면 재자리로
					//임시용 자리 잡기
					m_pTempItem->SetPosition(160, 90);
					m_isTorsoMount = false;
				}
			}
		}
	}
}