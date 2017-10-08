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
	//배이스
	m_pDialogBackGround = cUIButton::Create();
	m_pDialogBackGround->SetTexture("Texture/Ui/dialog6.png",
		"Texture/Ui/dialog6.png", "Texture/Ui/dialog6.png");
	m_pDialogBackGround->SetPosition(m_Wrc.right / 2 - 500, m_Wrc.bottom / 2 + 100);
	m_pDialogBackGround->SetDelegate(this);
	m_pDialogBackGround->m_Alpha = 0;
	m_pDialogBackGround->SetTag(E_BUTTON_NONE);
	m_pDialogUi = m_pDialogBackGround;
	
	//뒷검은 배경
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/blackImage.png",
		"Texture/Ui/blackImage.png", "Texture/Ui/blackImage.png");
	m_pDialogBackImage->SetPosition(-100, 50);
	m_pDialogBackImage->SetDelegate(this);
//	m_pDialogBackImage->m_Alpha = 0;
	m_pDialogBackImage->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(m_pDialogBackImage);

	//NPC 이미지
	m_pDialogNpcImage = cUIButton::Create();
	m_pDialogNpcImage->SetTexture("Texture/Ui/nao4.png",
		"Texture/Ui/nao4.png", "Texture/Ui/nao4.png");
	m_pDialogNpcImage->SetPosition(-70, -250);
	m_pDialogNpcImage->SetDelegate(this);
//	m_pDialogNpcImage->m_Alpha = 160;
	m_pDialogNpcImage->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(m_pDialogNpcImage);

	//NPC대화창  75, 300 
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/dialog6.png",
		"Texture/Ui/dialog6.png", "Texture/Ui/dialog6.png");
	m_pDialogBackImage->SetPosition(/*m_Wrc.right / 2 - 500, m_Wrc.bottom / 2 + 100*/0, 0);
	m_pDialogBackImage->SetDelegate(this);
	//m_pDialogBackImage->m_Alpha = 180;
	m_pDialogBackImage->SetTag(E_IMAGE_DIALOG);
	m_pDialogUi->AddChild(m_pDialogBackImage);
	//m_pDialogUi = m_pDialogBackImage;


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
	int DialogButtonY = 100;
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

	//퀘 수락 버튼
	m_pDialogAcceptButton = cUIButton::Create();
	m_pDialogAcceptButton->SetPosition(250, 100);
	m_pDialogUi->AddChild(m_pDialogAcceptButton);
	//퀘수락 택스트
	m_pDialogAcceptText = cUITextView::Create();
	m_pDialogUi->AddChild(m_pDialogAcceptText);
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
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_NONE_QUEST)
			{
				m_pDialogText->SetText("안녕하세요 귀한 곳에 누추한 분이 오셨군요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
				m_isDialogFin = false;
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("가서 여우들을 조지세요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("평화로운 여우들을 전부 죽이셨군요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-0, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("안녕하세요 누추하신 가정파괴자님");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-0, 20);
				m_pDialogAcceptButton->SetTag(E_BUTTON_NONE);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(180, 180, 180));
			}
		}
		break;
		case 1:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_NONE_QUEST)
			{
				m_pDialogText->SetText("누추한 당신에게 퀘스트를 하나 던져주겠어요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
				m_isDialogFin = false;
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("가서 여우들을 조지세요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("정-말 잘하셨어요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-40, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("보상이 맘에 드시기 바랍니다");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-40, 20);
				m_pDialogAcceptButton->SetTag(E_BUTTON_NONE);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(180, 180, 180));
			}
		}
		break;
		case 2:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_NONE_QUEST)
			{
				m_pDialogText->SetText("가서 여우 3마리만 잡아오세요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-10, 20);
				//퀘수락 버튼 켜기
				m_isDialogFin = true;
				//수락 버튼 활성화
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
				m_pDialogAcceptButton->SetPosition(250, 100);
				m_pDialogAcceptButton->SetDelegate(this);
				m_pDialogAcceptButton->SetTag(E_BUTTON_DIALOG_ACCEPT);
				//수락 택스트
				m_pDialogAcceptText->SetText("수락");
				m_pDialogAcceptText->SetFontType(g_pFontManager->E_INBUTTON);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
				m_pDialogAcceptText->SetSize(ST_SIZE(60, 30));
				m_pDialogAcceptText->SetPosition(40 + 210, 100 - 10);
				m_pDialogAcceptText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
				m_pDialogAcceptText->SetTag(E_BUTTON_NONE);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("가서 여우들을 조지세요");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
				//버튼 막기
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonUp6024.png");
				m_pDialogAcceptButton->SetTag(E_BUTTON_NONE);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(180, 180, 180));
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("여기 당신의 보상이 있습니다");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(0, 20);
				//보상 버튼 켜기
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
				m_pDialogAcceptButton->SetTag(E_BUTTON_DIALOG_REWARD);
				m_pDialogAcceptText->SetText("보상");
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("당신의 여행에 행운이 있기를 바랍니다");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(0, 20);
				//버튼 막기
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonUp6024.png");
				m_pDialogAcceptButton->SetTag(E_BUTTON_NONE);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(180, 180, 180));
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