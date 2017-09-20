
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

void cUiCustomizingScene::SetupHairEyeColor(void)
{
	int Y1 = 200;

	//이미지 머리
	//이미지 머리
	m_pCustomColorImageHead = cUIImageView::Create();
	m_pCustomColorImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomColorImageHead->SetPosition(m_nX, m_nY);
	m_pCustomColorImageHead->m_Alpha = 0;
	m_pCustomColorUi = m_pCustomColorImageHead;

	//이미지 창
	m_pCustomColorImage = cUIImageView::Create();
	m_pCustomColorImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomColorImage->SetPosition(2, 48);
	m_pCustomColorImage->m_Alpha = 0;
	m_pCustomColorUi->AddChild(m_pCustomColorImage);

	//헤어 칼라 버튼black
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonBlackUp.png",
		"Texture/Ui/buttonBlackUp.png",
		"Texture/Ui/buttonBlackDown.png");
	m_pCustomColorSulastButton->SetPosition(10, Y1);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLACK);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//헤어 칼라 버튼midblue
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonMidBlueUp0.png",
		"Texture/Ui/buttonMidBlueUp0.png",
		"Texture/Ui/buttonMidBlueDown0.png");
	m_pCustomColorSulastButton->SetPosition(40, Y1);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_MID_BLUE);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//헤어 칼라 버튼red
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonRedUp.png",
		"Texture/Ui/buttonRedUp.png",
		"Texture/Ui/buttonRedDown.png");
	m_pCustomColorSulastButton->SetPosition(70, Y1);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_RED);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);
	//헤어 칼라 버튼 갈색
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonBrownUp.png",
		"Texture/Ui/buttonBrownUp.png",
		"Texture/Ui/buttonBrownDown.png");
	m_pCustomColorSulastButton->SetPosition(100, Y1);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_BROWN);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);
	//헤어 칼라 버튼 갈색 블론드
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonBlondeUp.png",
		"Texture/Ui/buttonBlondeUp.png",
		"Texture/Ui/buttonBlondeDown.png");
	m_pCustomColorSulastButton->SetPosition(130, Y1);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLONDE);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//헤어 칼라 오랜지
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonOrangeUp.png",
		"Texture/Ui/buttonOrangeUp.png",
		"Texture/Ui/buttonOrangeDown.png");
	m_pCustomColorSulastButton->SetPosition(10, Y1 + 30);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_ORANGE);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//그린
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonDarkGreenUp.png",
		"Texture/Ui/buttonDarkGreenUp.png",
		"Texture/Ui/buttonDarkGreenDown.png");
	m_pCustomColorSulastButton->SetPosition(40, Y1 + 30);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_DARKGREEN);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//흰색
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonWhiteUp.png",
		"Texture/Ui/buttonWhiteUp.png",
		"Texture/Ui/buttonWhiteDown.png");
	m_pCustomColorSulastButton->SetPosition(70, Y1 + 30);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_WHITE);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//하늘색
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonSkyUp.png",
		"Texture/Ui/buttonSkyUp.png",
		"Texture/Ui/buttonSkyDown.png");
	m_pCustomColorSulastButton->SetPosition(100, Y1 + 30);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_SKY);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);

	//파란
	m_pCustomColorSulastButton = cUIButton::Create();
	m_pCustomColorSulastButton->SetTexture("Texture/Ui/buttonBlueUp.png",
		"Texture/Ui/buttonBlueUp.png",
		"Texture/Ui/buttonBlueDown.png");
	m_pCustomColorSulastButton->SetPosition(130, Y1 + 30);
	m_pCustomColorSulastButton->SetDelegate(this);
	m_pCustomColorSulastButton->SetTag(E_HAIR_COLOR_SELECT_BLUE);
	m_pCustomColorUi->AddChild(m_pCustomColorSulastButton);
}