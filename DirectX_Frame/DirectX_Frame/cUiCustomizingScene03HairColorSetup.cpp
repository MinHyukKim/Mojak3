
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

void cUiCustomizingScene::SetupHairColor(void)
{
	int Y1 = 200;
	//헤어 칼라 버튼black
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBlackUp.png",
		"Texture/Ui/buttonBlackUp.png",
		"Texture/Ui/buttonBlackDown.png");
	m_pCustomHairSulastButton->SetPosition(10, Y1);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLACK);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//헤어 칼라 버튼midblue
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonMidBlueUp0.png",
		"Texture/Ui/buttonMidBlueUp0.png",
		"Texture/Ui/buttonMidBlueDown0.png");
	m_pCustomHairSulastButton->SetPosition(40, Y1);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_MID_BLUE);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//헤어 칼라 버튼red
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonRedUp.png",
		"Texture/Ui/buttonRedUp.png",
		"Texture/Ui/buttonRedDown.png");
	m_pCustomHairSulastButton->SetPosition(70, Y1);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_RED);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//헤어 칼라 버튼 갈색
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBrownUp.png",
		"Texture/Ui/buttonBrownUp.png",
		"Texture/Ui/buttonBrownDown.png");
	m_pCustomHairSulastButton->SetPosition(100, Y1);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_BROWN);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//헤어 칼라 버튼 갈색 블론드
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBlondeUp.png",
		"Texture/Ui/buttonBlondeUp.png",
		"Texture/Ui/buttonBlondeDown.png");
	m_pCustomHairSulastButton->SetPosition(130, Y1);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLONDE);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);

	//헤어 칼라 오랜지
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonOrangeUp.png",
		"Texture/Ui/buttonOrangeUp.png",
		"Texture/Ui/buttonOrangeDown.png");
	m_pCustomHairSulastButton->SetPosition(10, Y1 + 30);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_ORANGE);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//빈 버튼
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonDarkGreenUp.png",
		"Texture/Ui/buttonDarkGreenUp.png",
		"Texture/Ui/buttonDarkGreenDown.png");
	m_pCustomHairSulastButton->SetPosition(40, Y1 + 30);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_DARKGREEN);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//빈 버튼
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonWhiteUp.png",
		"Texture/Ui/buttonWhiteUp.png",
		"Texture/Ui/buttonWhiteDown.png");
	m_pCustomHairSulastButton->SetPosition(70, Y1 + 30);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_WHITE);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//빈 버튼 
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonSkyUp.png",
		"Texture/Ui/buttonSkyUp.png",
		"Texture/Ui/buttonSkyDown.png");
	m_pCustomHairSulastButton->SetPosition(100, Y1 + 30);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_SKY);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//빈 버튼
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBlueUp.png",
		"Texture/Ui/buttonBlueUp.png",
		"Texture/Ui/buttonBlueDown.png");
	m_pCustomHairSulastButton->SetPosition(130, Y1 + 30);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLUE);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
}