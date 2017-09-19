
#include "stdafx.h"
#include "cUiCustomizingScene.h"
//폰트 용
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//플레이어
#include "cPlayer.h"
#include "cCamera.h"

void cUiCustomizingScene::SetupHairStyle(void)
{
	//헤어 창(매시, 컬러)
	//헤어 창 머리
	m_pCustomHairImageHead = cUIImageView::Create();
	m_pCustomHairImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomHairImageHead->SetPosition(20, 20);
	m_pCustomHairImageHead->m_Alpha = 0;
	m_pCustomHairUi = m_pCustomHairImageHead;
	//헤어 창
	m_pCustomHairImage = cUIImageView::Create();
	m_pCustomHairImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomHairImage->SetPosition(2, 48);
	m_pCustomHairImage->m_Alpha = 0;
	m_pCustomHairUi->AddChild(m_pCustomHairImage);
	//헤어 버튼1
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(10, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_01);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//2
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(70, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_02);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//3
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(130, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_03);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
}