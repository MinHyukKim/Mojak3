#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//�÷��̾�
#include "cPlayer.h"
#include "cCamera.h"
//�̹���
#include "cImage.h"

void cUiTestScene::SetupQuestUi(void)
{
	//����Ʈ â �Ӹ�
	m_pQuestUiImageHead = cUIImageView::Create();
	m_pQuestUiImageHead->SetTexture("Texture/Ui/questBaseHead1.png");
	m_pQuestUiImageHead->SetPosition(queX, queY);
	m_pQuestUiImageHead->m_Alpha = 200;
	m_pQuestUi = m_pQuestUiImageHead;
	//�巡�� ��ư
	m_pQuestUiMoveing = cUIButton::Create();
	m_pQuestUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pQuestUiMoveing->SetPosition(0, 0);
	m_pQuestUiMoveing->SetDelegate(this);
	m_pQuestUiMoveing->m_Alpha = 0;
	m_pQuestUiMoveing->SetTag(E_QUEST_MOVE);
	m_pQuestUi->AddChild(m_pQuestUiMoveing);
	//����Ʈ â
	m_pQuestUiImage = cUIButton::Create();
	m_pQuestUiImage->SetTexture("Texture/Ui/Base.png"
	, "Texture/Ui/Base.png", "Texture/Ui/Base.png");
	m_pQuestUiImage->SetPosition(2, 48);
	m_pQuestUiImage->SetDelegate(this);
	m_pQuestUiImage->m_Alpha = 180;
	m_pQuestUiImage->SetTag(E_BUTTON_NONE);
	m_pQuestUi->AddChild(m_pQuestUiImage);
	//�ý�Ʈ
	m_pQuestUiText = cUITextView::Create();
	m_pQuestUiText->SetText("����Ʈ");
	m_pQuestUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pQuestUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pQuestUiText->SetSize(ST_SIZE(200, 100));
	m_pQuestUiText->SetPosition(-40, -30);
	m_pQuestUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pQuestUiText->SetTag(E_BUTTON_NONE);
	m_pQuestUi->AddChild(m_pQuestUiText);
	//�ݱ� ��ư
	m_pQuestCloseButton = cUIButton::Create();
	m_pQuestCloseButton->SetTexture("Texture/Ui/button_close_up.png"
		, "Texture/Ui/button_close_over.png", "Texture/Ui/button_close_up.png");
	m_pQuestCloseButton->SetPosition(290, 10);
	m_pQuestCloseButton->SetDelegate(this);
	m_pQuestCloseButton->SetTag(E_BUTTON_QUEST_CLOSE);
	m_pQuestCloseButton->m_Alpha = 180;
	m_pQuestUi->AddChild(m_pQuestCloseButton);
}