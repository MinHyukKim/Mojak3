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

void cUiTestScene::SetupDialogUi(void)
{
	//NPC대화 관련
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/dialog3.png",
		"Texture/Ui/dialog3.png", "Texture/Ui/dialog3.png");
	m_pDialogBackImage->SetPosition(300, 300);
	m_pDialogBackImage->SetDelegate(this);
	m_pDialogBackImage->m_Alpha = 180;
	m_pDialogBackImage->SetTag(E_IMAGE_DIALOG);
	m_pDialogUi = m_pDialogBackImage;

	m_pDialogNameText = cUITextView::Create();
	m_pDialogNameText->SetText("태스트용 이름");
	m_pDialogNameText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogNameText->SetColor(D3DCOLOR_XRGB(0, 240, 240));
	m_pDialogNameText->SetSize(ST_SIZE(200, 30));
	m_pDialogNameText->SetPosition(10, 5);
	m_pDialogNameText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogNameText->SetTag(E_TEXT_DIALOG_HEAD);
	m_pDialogUi->AddChild(m_pDialogNameText);

	m_pDialogText = cUITextView::Create();
	m_pDialogText->SetText("대화창 태스트01");
	m_pDialogText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pDialogText->SetSize(ST_SIZE(200, 100));
	m_pDialogText->SetPosition(20, 30);
	m_pDialogText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogText->SetTag(E_TEXT_DIALOG);
	m_pDialogUi->AddChild(m_pDialogText);

	int DialogButtonX = 310;
	int DialogButtonY = 145;
	//대화창 이전 버튼
	m_pDialogPrev = cUIButton::Create();
	m_pDialogPrev->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogPrev->SetPosition(DialogButtonX, DialogButtonY);
	m_pDialogPrev->SetDelegate(this);
	m_pDialogPrev->SetTag(E_BUTTON_DIALOG_PREV);
	m_pDialogUi->AddChild(m_pDialogPrev);
	//이전 택스트
	pDialogPrevText = cUITextView::Create();
	pDialogPrevText->SetText("이전");
	pDialogPrevText->SetFontType(g_pFontManager->E_INBUTTON);
	pDialogPrevText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pDialogPrevText->SetSize(ST_SIZE(60, 30));
	pDialogPrevText->SetPosition(DialogButtonX, DialogButtonY - 10);
	pDialogPrevText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pDialogPrevText->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(pDialogPrevText);

	//대화창 다음 버튼
	m_pDialogNext = cUIButton::Create();
	m_pDialogNext->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogNext->SetPosition(DialogButtonX + 70, DialogButtonY);
	m_pDialogNext->SetDelegate(this);
	m_pDialogNext->SetTag(E_BUTTON_DIALOG_NEXT);
	m_pDialogUi->AddChild(m_pDialogNext);
	//다음 택스트
	pDialogNextText = cUITextView::Create();
	pDialogNextText->SetText("다음");
	pDialogNextText->SetFontType(g_pFontManager->E_INBUTTON);
	pDialogNextText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pDialogNextText->SetSize(ST_SIZE(60, 30));
	pDialogNextText->SetPosition(DialogButtonX + 70, DialogButtonY - 10);
	pDialogNextText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pDialogNextText->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(pDialogNextText);
}