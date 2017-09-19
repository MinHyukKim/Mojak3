
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

void cUiCustomizingScene::SetupEyeStyle(void)
{
	//�� â(�ý���)
	//�� �Ӹ�
	m_pCustomEyeImageHead = cUIImageView::Create();
	m_pCustomEyeImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomEyeImageHead->SetPosition(20, 20);
	m_pCustomEyeImageHead->m_Alpha = 0;
	m_pCustomEyeUi = m_pCustomEyeImageHead;
	//�� â
	m_pCustomEyeImage = cUIImageView::Create();
	m_pCustomEyeImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomEyeImage->SetPosition(2, 48);
	m_pCustomEyeImage->m_Alpha = 0;
	m_pCustomEyeUi->AddChild(m_pCustomEyeImage);
	//�� ��ư1
	m_pCustomEyeSulastButton = cUIButton::Create();
	m_pCustomEyeSulastButton->SetTexture("Texture/Ui/buttonEye00Up.png",
		"Texture/Ui/buttonEye00Up.png",
		"Texture/Ui/buttonEye00Down.png");
	m_pCustomEyeSulastButton->SetPosition(10, 120);
	m_pCustomEyeSulastButton->SetDelegate(this);
	m_pCustomEyeSulastButton->SetTag(E_EYE_SELECT_01);
	m_pCustomEyeUi->AddChild(m_pCustomEyeSulastButton);
	//2
	m_pCustomEyeSulastButton = cUIButton::Create();
	m_pCustomEyeSulastButton->SetTexture("Texture/Ui/buttonEye01Up.png",
		"Texture/Ui/buttonEye01Up.png",
		"Texture/Ui/buttonEye01Down.png");
	m_pCustomEyeSulastButton->SetPosition(70, 120);
	m_pCustomEyeSulastButton->SetDelegate(this);
	m_pCustomEyeSulastButton->SetTag(E_EYE_SELECT_02);
	m_pCustomEyeUi->AddChild(m_pCustomEyeSulastButton);
	//3
	m_pCustomEyeSulastButton = cUIButton::Create();
	m_pCustomEyeSulastButton->SetTexture("Texture/Ui/buttonEye02Up.png",
		"Texture/Ui/buttonEye02Up.png",
		"Texture/Ui/buttonEye02Down.png");
	m_pCustomEyeSulastButton->SetPosition(130, 120);
	m_pCustomEyeSulastButton->SetDelegate(this);
	m_pCustomEyeSulastButton->SetTag(E_EYE_SELECT_03);
	m_pCustomEyeUi->AddChild(m_pCustomEyeSulastButton);
}