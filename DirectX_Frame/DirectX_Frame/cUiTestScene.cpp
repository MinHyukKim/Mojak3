#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

enum
{
	//���� ��ư��
	E_MAIN_BUTTON_PLAYER_INFO = 213,
	E_MAIN_BUTTON_SKILL = 214,
	E_MAIN_BUTTON_QUEST = 215,
	E_MAIN_BUTTON_INVENTORY = 216,
	E_MAIN_BUTTON_ABILITY = 217,
	E_MAIN_BUTTON_ACTION = 218,
	E_MAIN_BUTTON_PET = 219,
	E_MAIN_BUTTON_MESSENGER = 220,
	E_TEXT_VIEW
};

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isClick(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
	, m_pUiTestRoot(NULL)
{
}

cUiTestScene::~cUiTestScene(void)
{
	this->Reset();
}

cUiTestScene* cUiTestScene::Create(void)
{
	cUiTestScene* newClass = new cUiTestScene;
	newClass->AddRef();
	return newClass;
}

HRESULT cUiTestScene::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//���� uiƲ ��ġ
	int mainUiLocalX = 300;			//���� Ʋ x
	int mainUiLocalY = 500;			//���� Ʋ y

	int mainButtonH = -25;			//���� ��ư�� ����
	int mainButtoninterval = 40;	//���� ��ư�� ���� ����(ũ��)
	int mainButtonSrart = 180;		//���� ��ư�� ���� ���� ��ġ

	//�׽�Ʈ�� ���ι�ư��
	cUIImageView* pImageView = cUIImageView::Create();
	pImageView->SetTexture("Texture/Ui/TestRoot1.png");
	pImageView->SetPosition(mainUiLocalX, mainUiLocalY);
	m_pUiRoot = pImageView;

	cUITextView* pTextView = cUITextView::Create();
	pTextView->SetText("�½�Ʈ��");
	pTextView->SetSize(ST_SIZE(400, 200));
	pTextView->SetPosition(0, -300);
	pTextView->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUiRoot->AddChild(pTextView);

	cUIButton* pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_info_button_up.png", 
		"Texture/Ui/player_info_button_over.png",
		"Texture/Ui/player_info_button_down.png");
	pButton->SetPosition(mainButtonSrart, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_PLAYER_INFO);
	m_pUiRoot->AddChild(pButton);

	pButton =  cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_sikill_button_up.png", 
		"Texture/Ui/player_sikill_button_over.png",
		"Texture/Ui/player_sikill_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_SKILL);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_quest_button_up.png", 
		"Texture/Ui/player_quest_button_over.png",
		"Texture/Ui/player_quest_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 2, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_QUEST);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_inventory_button_up.png", 
		"Texture/Ui/player_inventory_button_over.png",
		"Texture/Ui/player_inventory_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 3, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_INVENTORY);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_ability_button_up.png", 
		"Texture/Ui/player_ability_button_over.png",
		"Texture/Ui/player_ability_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 4, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_ABILITY);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_action_button_up.png", 
		"Texture/Ui/player_action_button_over.png",
		"Texture/Ui/player_action_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 5, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_ACTION);
	m_pUiRoot->AddChild(pButton);

	pButton = cUIButton::Create();
	pButton->SetTexture("Texture/Ui/player_pet_button_up.png", 
		"Texture/Ui/player_pet_button_over.png",
		"Texture/Ui/player_pet_button_down.png");
	pButton->SetPosition(mainButtonSrart + mainButtoninterval * 6, mainButtonH);
	pButton->SetDelegate(this);
	pButton->SetTag(E_MAIN_BUTTON_PET);
	m_pUiRoot->AddChild(pButton);

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
	SAFE_RELEASE(m_pUiTestRoot);
}

void cUiTestScene::Update(void)
{
	if (m_pUiRoot) m_pUiRoot->Update();
}

void cUiTestScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	if(m_pUiRoot) m_pUiRoot->Render(m_pSprite);
}

void cUiTestScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cUiTestScene::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		pTextView->SetText("�÷��̾� ����â �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		pTextView->SetText("�÷��̾� ��ųâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		pTextView->SetText("����Ʈâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
		pTextView->SetText("�κ��丮 â �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
	{
		pTextView->SetText("���â �����ϱ�(�߰�����)");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
	{
		pTextView->SetText("�׼� â �����ϱ�(�߰�����)");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
	{
		pTextView->SetText("�� â �����ϱ�(�߰� ����)");
	}

//	E_MAIN_BUTTON_PLAYER_INFO = 213,
//		E_MAIN_BUTTON_SKILL = 214,
//		E_MAIN_BUTTON_QUEST = 215,
//		E_MAIN_BUTTON_INVENTORY = 216,
//		E_MAIN_BUTTON_ABILITY = 217,
//		E_MAIN_BUTTON_ACTION = 218,
//		E_MAIN_BUTTON_PET = 219,
//		E_MAIN_BUTTON_MESSENGER = 220,
//		E_TEXT_VIEW

}
