#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

cUiTestScene::cUiTestScene(void)
	: m_pFont(NULL)
	, m_isClick(false)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pUiRoot(NULL)
	, m_pUiTestRoot(NULL)
	, m_isMainMin(false)
	, m_pMainRootImageView(NULL)
	, m_pMainMainButton(NULL)
	, m_pUiTesterSize(NULL)
	//������� ����
	, m_isMainWindowOn(false)
	, m_isInfoWindowOn(false)
	, m_isSkillWindowOn(false)
	, m_isQuestWindowOn(false)
	, m_isInventoryWindowOn(false)
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

	//���̽� ��ư(�½�Ʈ �ý�Ʈ ����
	this->SetupBaseButton();

	//�ӽ� �½�Ʈ��
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTestRoot = m_pUiTesterSize;

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pUiRoot);
//	SAFE_RELEASE(m_pMainRootImageView);
	SAFE_RELEASE(m_pUiTestRoot);
//	SAFE_RELEASE(m_pMainMainButton);
}

void cUiTestScene::Update(void)
{
	this->changeMainButtonColor();
	//����â ������ (�ٽ� �����)
	if (m_isMainMin == true) m_pMainRootImageView->SetPosition(300, 520);
	else m_pMainRootImageView->SetPosition(300, 502);

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

//��������Ʈ(Ŭ��)
void cUiTestScene::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		m_isInfoWindowOn = !m_isInfoWindowOn;
		pTextView->SetText("�÷��̾� ����â �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		m_isSkillWindowOn = !m_isSkillWindowOn;
		pTextView->SetText("�÷��̾� ��ųâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		m_isQuestWindowOn = !m_isQuestWindowOn;
		pTextView->SetText("����Ʈâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
		pTextView->SetText("�κ��丮 â �����ϱ�");
	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
//	{
//		pTextView->SetText("���â �����ϱ�(�߰�����)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
//	{
//		pTextView->SetText("�׼� â �����ϱ�(�߰�����)");
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
//	{
//		pTextView->SetText("�� â �����ϱ�(�߰� ����)");
//	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}

}

void cUiTestScene::changeMainButtonColor(void)
{
	if (m_isInfoWindowOn)
	{
		m_pInfoButton->SetTexture("Texture/Ui/on_player_info_button_up.png",
			"Texture/Ui/on_player_info_button_over.png",
			"Texture/Ui/on_player_info_button_down.png");
	}
	else if (m_isInfoWindowOn == false)
	{
		m_pInfoButton->SetTexture("Texture/Ui/player_info_button_up.png",
			"Texture/Ui/player_info_button_over.png",
			"Texture/Ui/player_info_button_down.png");
	}

	if (m_isSkillWindowOn)
	{
		m_pSkillButton->SetTexture("Texture/Ui/on_player_sikill_button_up.png",
			"Texture/Ui/on_player_sikill_button_over.png",
			"Texture/Ui/on_player_sikill_button_down.png");
	}
	else if (m_isSkillWindowOn == false)
	{
		m_pSkillButton->SetTexture("Texture/Ui/player_sikill_button_up.png",
			"Texture/Ui/player_sikill_button_over.png",
			"Texture/Ui/player_sikill_button_down.png");
	}

	if (m_isQuestWindowOn)
	{
		m_pQuestButton->SetTexture("Texture/Ui/on_player_quest_button_up.png",
			"Texture/Ui/on_player_quest_button_over.png",
			"Texture/Ui/on_player_quest_button_down.png");
	}
	else if (m_isQuestWindowOn == false)
	{
		m_pQuestButton->SetTexture("Texture/Ui/player_quest_button_up.png",
			"Texture/Ui/player_quest_button_over.png",
			"Texture/Ui/player_quest_button_down.png");
	}

	if (m_isInventoryWindowOn)
	{
		m_pInventoryButton->SetTexture("Texture/Ui/on_player_inventory_button_up.png",
			"Texture/Ui/on_player_inventory_button_over.png",
			"Texture/Ui/on_player_inventory_button_down.png");
	}
	else if (m_isInventoryWindowOn == false)
	{
		m_pInventoryButton->SetTexture("Texture/Ui/player_inventory_button_up.png",
			"Texture/Ui/player_inventory_button_over.png",
			"Texture/Ui/player_inventory_button_down.png");
	}
}
