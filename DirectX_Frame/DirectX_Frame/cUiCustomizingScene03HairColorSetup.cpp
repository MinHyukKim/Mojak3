
#include "stdafx.h"
#include "cUiCustomizingScene.h"
//��Ʈ ��
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//�÷��̾�
#include "cPlayer.h"
#include "cCamera.h"

void cUiCustomizingScene::SetupHairColor(void)
{
	//��� Į�� ��ưR
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2rad.png",
		"Texture/Ui/buttonBase2rad.png",
		"Texture/Ui/buttonBase2radDown.png");
	m_pCustomHairSulastButton->SetPosition(10, 180);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_01);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//��� Į�� ��ưB
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2blue.png",
		"Texture/Ui/buttonBase2blue.png",
		"Texture/Ui/buttonBase2blueDown.png");
	m_pCustomHairSulastButton->SetPosition(70, 180);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_02);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//��� Į�� ��ưY
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2yellow.png",
		"Texture/Ui/buttonBase2yellow.png",
		"Texture/Ui/buttonBase2yellowDown.png");
	m_pCustomHairSulastButton->SetPosition(130, 180);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_COLOR_SELECT_03);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
}