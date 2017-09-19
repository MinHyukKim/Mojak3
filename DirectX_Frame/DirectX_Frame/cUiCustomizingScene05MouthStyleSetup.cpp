
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

void cUiCustomizingScene::SetupMouthStyle(void)
{
	//�� â(�ý���)
	m_pCustomMouthImageHead = cUIImageView::Create();
	m_pCustomMouthImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomMouthImageHead->SetPosition(20, 20);
	m_pCustomMouthImageHead->m_Alpha = 0;
	m_pCustomMouthUi = m_pCustomMouthImageHead;
	//�� â
	m_pCustomMouthImage = cUIImageView::Create();
	m_pCustomMouthImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomMouthImage->SetPosition(2, 48);
	m_pCustomMouthImage->m_Alpha = 0;
	m_pCustomMouthUi->AddChild(m_pCustomMouthImage);
	//�� ��ư 1
	m_pCustomMouthSulastButton = cUIButton::Create();
	m_pCustomMouthSulastButton->SetTexture("Texture/Ui/buttonMouth00Up.png",
		"Texture/Ui/buttonMouth00Up.png",
		"Texture/Ui/buttonMouth00Down.png");
	m_pCustomMouthSulastButton->SetPosition(10, 120);
	m_pCustomMouthSulastButton->SetDelegate(this);
	m_pCustomMouthSulastButton->SetTag(E_MOUTH_SELECT_01);
	m_pCustomMouthUi->AddChild(m_pCustomMouthSulastButton);
	//2
	m_pCustomMouthSulastButton = cUIButton::Create();
	m_pCustomMouthSulastButton->SetTexture("Texture/Ui/buttonMouth01Up.png",
		"Texture/Ui/buttonMouth01Up.png",
		"Texture/Ui/buttonMouth01Down.png");
	m_pCustomMouthSulastButton->SetPosition(70, 120);
	m_pCustomMouthSulastButton->SetDelegate(this);
	m_pCustomMouthSulastButton->SetTag(E_MOUTH_SELECT_02);
	m_pCustomMouthUi->AddChild(m_pCustomMouthSulastButton);
	//3
	m_pCustomMouthSulastButton = cUIButton::Create();
	m_pCustomMouthSulastButton->SetTexture("Texture/Ui/buttonMouth02Up.png",
		"Texture/Ui/buttonMouth02Up.png",
		"Texture/Ui/buttonMouth02Down.png");
	m_pCustomMouthSulastButton->SetPosition(130, 120);
	m_pCustomMouthSulastButton->SetDelegate(this);
	m_pCustomMouthSulastButton->SetTag(E_MOUTH_SELECT_03);
	m_pCustomMouthUi->AddChild(m_pCustomMouthSulastButton);
}