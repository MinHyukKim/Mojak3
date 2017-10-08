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

void cUiTestScene::SetupQuestUi(void)
{
	//퀘스트 창 머리
	m_pQuestUiImageHead = cUIImageView::Create();
	m_pQuestUiImageHead->SetTexture("Texture/Ui/questBaseHead1.png");
	m_pQuestUiImageHead->SetPosition(queX, queY);
	m_pQuestUiImageHead->m_Alpha = 200;
	m_pQuestUi = m_pQuestUiImageHead;
	//드래그 버튼
	m_pQuestUiMoveing = cUIButton::Create();
	m_pQuestUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pQuestUiMoveing->SetPosition(0, 0);
	m_pQuestUiMoveing->SetDelegate(this);
	m_pQuestUiMoveing->m_Alpha = 0;
	m_pQuestUiMoveing->SetTag(E_QUEST_MOVE);
	m_pQuestUi->AddChild(m_pQuestUiMoveing);
	//퀘스트 창
	m_pQuestUiImage = cUIButton::Create();
	m_pQuestUiImage->SetTexture("Texture/Ui/Base.png"
	, "Texture/Ui/Base.png", "Texture/Ui/Base.png");
	m_pQuestUiImage->SetPosition(2, 48);
	m_pQuestUiImage->SetDelegate(this);
	m_pQuestUiImage->m_Alpha = 180;
	m_pQuestUiImage->SetTag(E_BUTTON_NONE);
	m_pQuestUi->AddChild(m_pQuestUiImage);
	//택스트
	m_pQuestUiText = cUITextView::Create();
	m_pQuestUiText->SetText("퀘스트");
	m_pQuestUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pQuestUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pQuestUiText->SetSize(ST_SIZE(200, 100));
	m_pQuestUiText->SetPosition(-40, -30);
	m_pQuestUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pQuestUiText->SetTag(E_BUTTON_NONE);
	m_pQuestUi->AddChild(m_pQuestUiText);
	//택스트 및 이ㅣ미지

	//닫기 버튼
	m_pQuestCloseButton = cUIButton::Create();
	m_pQuestCloseButton->SetTexture("Texture/Ui/button_close_up.png"
		, "Texture/Ui/button_close_over.png", "Texture/Ui/button_close_up.png");
	m_pQuestCloseButton->SetPosition(290, 10);
	m_pQuestCloseButton->SetDelegate(this);
	m_pQuestCloseButton->SetTag(E_BUTTON_QUEST_CLOSE);
	m_pQuestCloseButton->m_Alpha = 180;
	m_pQuestUi->AddChild(m_pQuestCloseButton);

	//퀘 추가용
	m_pQuestUseImage = cUIButton::Create();
	m_pQuestUseImage->SetPosition(20, 70);
	m_pQuestUi->AddChild(m_pQuestUseImage);
	m_pQuestUseText = cUITextView::Create();
	m_pQuestUseText->SetPosition(30, 30);
	m_pQuestUi->AddChild(m_pQuestUseText);
}

void cUiTestScene::UpdateQuestUi(void)
{
	//퀘스트를 받았을 시
	if (m_eDialogStat == E_QUEST)
	{
		m_pQuestUseImage->SetTexture("Texture/Ui/quest.png"
			, "Texture/Ui/quest.png", "Texture/Ui/quest.png");
		m_pQuestUseImage->SetPosition(20, 70);
		m_pQuestUseImage->SetDelegate(this);
		m_pQuestUseImage->SetTag(E_BUTTON_NONE);
		m_pQuestUseImage->m_Alpha = 200;

		m_nKillFox += g_pObjectManager->ClearDeath(cObjectManager::MONSTER_FOX);
		//택스트
		char szKillCount[32] = { '\0', };
		sprintf_s(szKillCount, "[튜토리얼] 여우잡이  %d / %d", m_nKillFox, m_nKillFoxMax);
		m_pQuestUseText->SetText(szKillCount);
		m_pQuestUseText->SetFontType(g_pFontManager->E_INBUTTON);
		m_pQuestUseText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
		m_pQuestUseText->SetSize(ST_SIZE(220, 100));
		m_pQuestUseText->SetPosition(30, 30);
		m_pQuestUseText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		m_pQuestUseText->SetTag(E_BUTTON_NONE);

		//여우 카운터		
		if (m_nKillFox >= m_nKillFoxMax)
		{
			//대화 상태 바꾸기
			m_eDialogStat = E_FIN_QUEST;
		}
	}
}