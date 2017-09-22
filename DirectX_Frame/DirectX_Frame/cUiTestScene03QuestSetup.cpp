#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

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
	m_pQuestUiImage = cUIImageView::Create();
	m_pQuestUiImage->SetTexture("Texture/Ui/Base.png");
	m_pQuestUiImage->SetPosition(2, 48);
	m_pQuestUiImage->m_Alpha = 180;
	m_pQuestUi->AddChild(m_pQuestUiImage);
}