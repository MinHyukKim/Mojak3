
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

void cUiCustomizingScene::SetupTotal(void)
{
	//Ŀ�� â �Ӹ�
	m_pCustomImageHead = cUIImageView::Create();
	m_pCustomImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomImageHead->SetPosition(m_nX, m_nY);
	m_pCustomImageHead->m_Alpha = 200;
	m_pCustomUi = m_pCustomImageHead;
	//Ŀ�� â
	m_pCustomImage = cUIImageView::Create();
	m_pCustomImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomImage->SetPosition(2, 48);
	m_pCustomImage->m_Alpha = 180;
	m_pCustomUi->AddChild(m_pCustomImage);
	//�ý�Ʈ
	m_pCustomNameTest = cUITextView::Create();
	m_pCustomNameTest->SetText("ĳ���� ����");
	m_pCustomNameTest->SetFontType(g_pFontManager->E_INBUTTON);
	m_pCustomNameTest->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	m_pCustomNameTest->SetSize(ST_SIZE(200, 100));
	m_pCustomNameTest->SetPosition(-20, -30);
	m_pCustomNameTest->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pCustomNameTest->SetTag(E_TEXT_CUSTOM_NAME);
	m_pCustomUi->AddChild(m_pCustomNameTest);
	//���ù�ư
	//�Ӹ� ����
	m_pCustomButtonHair = cUIButton::Create();
	m_pCustomButtonHair->SetTexture("Texture/Ui/buttonHairUp.png",
		"Texture/Ui/buttonHairUp.png",
		"Texture/Ui/buttonHairUp.png");
	m_pCustomButtonHair->SetPosition(10, 60);
	m_pCustomButtonHair->SetDelegate(this);
	m_pCustomButtonHair->SetTag(E_CUSTOM_BUTTON_HAIR);
	m_pCustomUi->AddChild(m_pCustomButtonHair);
	//�� ����
	m_pCustomButtonEye = cUIButton::Create();
	m_pCustomButtonEye->SetTexture("Texture/Ui/buttonEyeUp.png",
		"Texture/Ui/buttonEyeUp.png",
		"Texture/Ui/buttonEyeUp.png");
	m_pCustomButtonEye->SetPosition(52, 60);
	m_pCustomButtonEye->SetDelegate(this);
	m_pCustomButtonEye->SetTag(E_CUSTOM_BUTTON_EYE);
	m_pCustomUi->AddChild(m_pCustomButtonEye);
	//�� ����
	m_pCustomButtonMouth = cUIButton::Create();
	m_pCustomButtonMouth->SetTexture("Texture/Ui/buttonMouseUp.png",
		"Texture/Ui/buttonMouseUp.png",
		"Texture/Ui/buttonMouseUp.png");
	m_pCustomButtonMouth->SetPosition(94, 60);
	m_pCustomButtonMouth->SetDelegate(this);
	m_pCustomButtonMouth->SetTag(E_CUSTOM_BUTTON_MOUTH);
	m_pCustomUi->AddChild(m_pCustomButtonMouth);
	//�Ϸ� ��ư (�̿�)
	m_pCustomButtonFin = cUIButton::Create();
	m_pCustomButtonFin->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonDown6024.png");
	m_pCustomButtonFin->SetPosition(164, 370);
	m_pCustomButtonFin->SetDelegate(this);
	m_pCustomButtonFin->SetTag(E_CUSTOM_BUTTON_FIN);
	m_pCustomUi->AddChild(m_pCustomButtonFin);
	//�۾�
	cUITextView* TextFin = cUITextView::Create();
	TextFin->SetText("�Ϸ�");
	TextFin->SetFontType(g_pFontManager->E_TEMP_INBUTTON);
	TextFin->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	TextFin->SetSize(ST_SIZE(50, 40));
	//TextFin->SetPosition(169, 355); //����ü
	TextFin->SetPosition(169, 362);   //�������
	TextFin->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	TextFin->SetTag(E_TEXT_CUSTOM_FIN);
	m_pCustomUi->AddChild(TextFin);
}