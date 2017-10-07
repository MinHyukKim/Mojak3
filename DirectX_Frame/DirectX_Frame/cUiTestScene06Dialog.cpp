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

void cUiTestScene::SetupDialogUi(void)
{
	//NPC��ȭ ����  75, 300
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/dialog5.png",
		"Texture/Ui/dialog5.png", "Texture/Ui/dialog5.png");
	m_pDialogBackImage->SetPosition(m_Wrc.right / 2 - 500, m_Wrc.bottom / 2 + 50);
	m_pDialogBackImage->SetDelegate(this);
	//m_pDialogBackImage->m_Alpha = 180;
	m_pDialogBackImage->SetTag(E_IMAGE_DIALOG);
	m_pDialogUi = m_pDialogBackImage;

	m_pDialogNameText = cUITextView::Create();
	m_pDialogNameText->SetText("�½�Ʈ�� �̸�");
	m_pDialogNameText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogNameText->SetColor(D3DCOLOR_XRGB(0, 240, 240));
	m_pDialogNameText->SetSize(ST_SIZE(150, 50));
	m_pDialogNameText->SetPosition(10, 5);
	m_pDialogNameText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogNameText->SetTag(E_TEXT_DIALOG_HEAD);
	m_pDialogUi->AddChild(m_pDialogNameText);

	m_pDialogText = cUITextView::Create();
	m_pDialogText->SetText("��ȭâ �½�Ʈ01");
	m_pDialogText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pDialogText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pDialogText->SetSize(ST_SIZE(150, 80));
	m_pDialogText->SetPosition(20, 30);
	m_pDialogText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pDialogText->SetTag(E_TEXT_DIALOG);
	m_pDialogUi->AddChild(m_pDialogText);


	int DialogButtonX = 40;
	int DialogButtonY = 145;
	//�ݱ�
	m_pDialogCloseButton = cUIButton::Create();
	m_pDialogCloseButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogCloseButton->SetPosition(DialogButtonX + 140, DialogButtonY);   //940, 30
	m_pDialogCloseButton->SetDelegate(this);
	m_pDialogCloseButton->SetTag(E_BUTTON_DIALOG_CLOSE);
	m_pDialogCloseButton->m_Alpha = 220;
	m_pDialogUi->AddChild(m_pDialogCloseButton);
	//�ݱ� �ý�Ʈ
	cUITextView* pTempText = cUITextView::Create();
	pTempText->SetText("��ȭ����");
	pTempText->SetFontType(g_pFontManager->E_INBUTTON);
	pTempText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pTempText->SetSize(ST_SIZE(100, 30));
	pTempText->SetPosition(DialogButtonX + 120, DialogButtonY - 10);
	pTempText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTempText->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(pTempText);

	//��ȭâ ���� ��ư
	m_pDialogPrev = cUIButton::Create();
	m_pDialogPrev->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogPrev->SetPosition(DialogButtonX, DialogButtonY);
	m_pDialogPrev->SetDelegate(this);
	m_pDialogPrev->SetTag(E_BUTTON_DIALOG_PREV);
	m_pDialogUi->AddChild(m_pDialogPrev);
	//���� �ý�Ʈ
	pDialogPrevText = cUITextView::Create();
	pDialogPrevText->SetText("����");
	pDialogPrevText->SetFontType(g_pFontManager->E_INBUTTON);
	pDialogPrevText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	pDialogPrevText->SetSize(ST_SIZE(60, 30));
	pDialogPrevText->SetPosition(DialogButtonX, DialogButtonY - 10);
	pDialogPrevText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pDialogPrevText->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(pDialogPrevText);

	//��ȭâ ���� ��ư
	m_pDialogNext = cUIButton::Create();
	m_pDialogNext->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
	m_pDialogNext->SetPosition(DialogButtonX + 70, DialogButtonY);
	m_pDialogNext->SetDelegate(this);
	m_pDialogNext->SetTag(E_BUTTON_DIALOG_NEXT);
	m_pDialogUi->AddChild(m_pDialogNext);
	//���� �ý�Ʈ
	pDialogNextText = cUITextView::Create();
	pDialogNextText->SetText("����");
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
			m_pDialogNameText->SetText("����");
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
				m_pDialogText->SetText("�ȳ��ϼ��� ���� ���� ������ ���� ���̱���");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
		case 1:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("������ ��ſ��� ����Ʈ�� �ϳ� �����ְھ��");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
		case 2:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("���� ���� 3������ ��ƿ�����");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-10, 20);
				//������ ��ư �ѱ�

			}
		}
		break;
		case 3:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("��ȭâ �½�Ʈ04");
			}
		}
		break;
		case 4:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("��ȭâ �½�Ʈ05");
			}
		}
		break;
		case 5:
		{
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO)
			{
				m_pDialogText->SetText("��ȭâ �½�Ʈ06");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
			}
		}
		break;
	}
}