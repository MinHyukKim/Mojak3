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
	//NPC대화 관련  75, 300
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/dialog5.png",
		"Texture/Ui/dialog5.png", "Texture/Ui/dialog5.png");
	m_pDialogBackImage->SetPosition(m_Wrc.right / 2 - 500, m_Wrc.bottom / 2 + 50);
	m_pDialogBackImage->SetDelegate(this);
	//m_pDialogBackImage->m_Alpha = 180;
	m_pDialogBackImage->SetTag(E_IMAGE_DIALOG);
	m_pDialogUi = m_pDialogBackImage;

	m_pDialogNameText = cUITextView::Create();
	m_pDialogNameText->SetText("태스트용 이름");
	m_pDialogNameText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogNameText->SetColor(D3DCOLOR_XRGB(0, 240, 240));
	m_pDialogNameText->SetSize(ST_SIZE(150, 50));
	m_pDialogNameText->SetPosition(10, 5);
	m_pDialogNameText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogNameText->SetTag(E_TEXT_DIALOG_HEAD);
	m_pDialogUi->AddChild(m_pDialogNameText);

	m_pDialogText = cUITextView::Create();
	m_pDialogText->SetText("대화창 태스트01");
	m_pDialogText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pDialogText->SetSize(ST_SIZE(150, 80));
	m_pDialogText->SetPosition(20, 30);
	m_pDialogText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogText->SetTag(E_TEXT_DIALOG);
	m_pDialogUi->AddChild(m_pDialogText);


	int DialogButtonX = 40;
	int DialogButtonY = 145;
	//닫기
	m_pDialogCloseButton = cUIButton::Create();
	m_pDialogCloseButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogCloseButton->SetPosition(DialogButtonX + 140, DialogButtonY);   //940, 30
	m_pDialogCloseButton->SetDelegate(this);
	m_pDialogCloseButton->SetTag(E_BUTTON_DIALOG_CLOSE);
	m_pDialogCloseButton->m_Alpha = 220;
	m_pDialogUi->AddChild(m_pDialogCloseButton);
	//닫기 택스트
	cUITextView* pTempText = cUITextView::Create();
	pTempText->SetText("대화종료");
	pTempText->SetFontType(g_pFontManager->E_INBUTTON);
	pTempText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pTempText->SetSize(ST_SIZE(100, 30));
	pTempText->SetPosition(DialogButtonX + 120, DialogButtonY - 10);
	pTempText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTempText->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(pTempText);

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

void cUiTestScene::changeDialogText(void)
{
	switch (m_eDialogNPCKind)
	{
		case E_DIALOG_NPC_NAO:
		{
			m_pDialogNameText->SetText("나오");
			m_pDialogNameText->SetPosition(-10, 5);
		}
		break;
	}
	

	switch (m_nDialogTextNum)
	{
		case 0:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("안녕하세요 귀한 곳에 누추한 분이 오셨군요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
		case 1:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("누추한 당신에게 퀘스트를 하나 던져주겠어요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
		case 2:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("가서 여우 3마리만 잡아오세요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-10, 20);
				//퀘수락 버튼 켜기

			}
		}
		break;
		case 3:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("대화창 태스트04");
			}
		}
		break;
		case 4:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("대화창 태스트05");
			}
		}
		break;
		case 5:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("대화창 태스트06");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
	}
}