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
	//���̽�
	m_pDialogBackGround = cUIButton::Create();
	m_pDialogBackGround->SetTexture("Texture/Ui/dialog6.png",
		"Texture/Ui/dialog6.png", "Texture/Ui/dialog6.png");
	m_pDialogBackGround->SetPosition(m_Wrc.right / 2 - 500, m_Wrc.bottom / 2 + 100);
	m_pDialogBackGround->SetDelegate(this);
	m_pDialogBackGround->m_Alpha = 0;
	m_pDialogBackGround->SetTag(E_BUTTON_NONE);
	m_pDialogUi = m_pDialogBackGround;
	
	//�ް��� ���
	m_pDialogBackImage = cUIButton::Create();
	m_pDialogBackImage->SetTexture("Texture/Ui/blackImage.png",
		"Texture/Ui/blackImage.png", "Texture/Ui/blackImage.png");
	m_pDialogBackImage->SetPosition(-100, 50);
	m_pDialogBackImage->SetDelegate(this);
//	m_pDialogBackImage->m_Alpha = 0;
	m_pDialogBackImage->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(m_pDialogBackImage);

	//NPC �̹���
	m_pDialogNpcImage = cUIButton::Create();
	m_pDialogNpcImage->SetTexture("Texture/Ui/nao4.png",
		"Texture/Ui/nao4.png", "Texture/Ui/nao4.png");
	m_pDialogNpcImage->SetPosition(-70, -250);
	m_pDialogNpcImage->SetDelegate(this);
//	m_pDialogNpcImage->m_Alpha = 160;
	m_pDialogNpcImage->SetTag(E_BUTTON_NONE);
	m_pDialogUi->AddChild(m_pDialogNpcImage);

	//NPC��ȭâ  75, 300 
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
	int DialogButtonY = 100;
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

	//�� ���� ��ư
	m_pDialogAcceptButton = cUIButton::Create();
	m_pDialogAcceptButton->SetPosition(250, 100);
	m_pDialogUi->AddChild(m_pDialogAcceptButton);
	//������ �ý�Ʈ
	m_pDialogAcceptText = cUITextView::Create();
	m_pDialogUi->AddChild(m_pDialogAcceptText);
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
			if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_NONE_QUEST)
			{
				m_pDialogText->SetText("�ȳ��ϼ��� ���� ���� ������ ���� ���̱���");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
				m_isDialogFin = false;
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("���� ������� ��������");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("��ȭ�ο� ������� ���� ���̼̱���");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-0, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("�ȳ��ϼ��� �����Ͻ� �����ı��ڴ�");
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
				m_pDialogText->SetText("������ ��ſ��� ����Ʈ�� �ϳ� �����ְھ��");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(28, 20);
				m_isDialogFin = false;
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("���� ������� ��������");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("��-�� ���ϼ̾��");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-40, 20);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("������ ���� ��ñ� �ٶ��ϴ�");
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
				m_pDialogText->SetText("���� ���� 3������ ��ƿ�����");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-10, 20);
				//������ ��ư �ѱ�
				m_isDialogFin = true;
				//���� ��ư Ȱ��ȭ
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
				m_pDialogAcceptButton->SetPosition(250, 100);
				m_pDialogAcceptButton->SetDelegate(this);
				m_pDialogAcceptButton->SetTag(E_BUTTON_DIALOG_ACCEPT);
				//���� �ý�Ʈ
				m_pDialogAcceptText->SetText("����");
				m_pDialogAcceptText->SetFontType(g_pFontManager->E_INBUTTON);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
				m_pDialogAcceptText->SetSize(ST_SIZE(60, 30));
				m_pDialogAcceptText->SetPosition(40 + 210, 100 - 10);
				m_pDialogAcceptText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
				m_pDialogAcceptText->SetTag(E_BUTTON_NONE);
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_QUEST)
			{
				m_pDialogText->SetText("���� ������� ��������");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(-20, 20);
				//��ư ����
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonUp6024.png");
				m_pDialogAcceptButton->SetTag(E_BUTTON_NONE);
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(180, 180, 180));
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_FIN_QUEST)
			{
				m_pDialogText->SetText("���� ����� ������ �ֽ��ϴ�");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(0, 20);
				//���� ��ư �ѱ�
				m_pDialogAcceptButton->SetTexture("Texture/Ui/textButtonUp6024.png",
					"Texture/Ui/textButtonUp6024.png", "Texture/Ui/textButtonDown6024.png");
				m_pDialogAcceptButton->SetTag(E_BUTTON_DIALOG_REWARD);
				m_pDialogAcceptText->SetText("����");
				m_pDialogAcceptText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
			}
			else if (m_eDialogNPCKind == E_DIALOG_NPC_NAO && m_eDialogStat == E_END_QUEST)
			{
				m_pDialogText->SetText("����� ���࿡ ����� �ֱ⸦ �ٶ��ϴ�");
				m_pDialogText->SetSize(ST_SIZE(300, 80));
				m_pDialogText->SetPosition(0, 20);
				//��ư ����
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