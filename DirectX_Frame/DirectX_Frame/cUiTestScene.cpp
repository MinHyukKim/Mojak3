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
	, m_isLbuttonDown(false)
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
	//
	, m_pInfoUi(NULL)
	, m_pSkillUi(NULL)
	, m_pQuestUi(NULL)
	, m_pInventoryUi(NULL)
	, invX(20)
	, invY(20)
	, skillX(680)
	, skillY(20)
	, infoX(354)
	, infoY(20)
	, queX(500)
	, queY(60)
	//������ ��ŷ
	, isPickUpItem(false)
	//���� ����
	, m_isTorsoMount(false) //�ʱ⿡ ������ true�� ����
	, m_isWeaponHandMount(false)
	, m_isSubHandMount(false)
	, m_isShoesMount(false)
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
	m_pUiTesterSize->SetTexture("Texture/Ui/inventoryBase.png");
	m_pUiTesterSize->SetPosition(10, 10);
	m_pUiTestRoot = m_pUiTesterSize;	

	//�÷��̾� ���� â �¾�
	this->SetupInfoUi();
	//��ų â �¾�
	this->SetupSkillUi();
	//����Ʈ â �¾�
	this->SetupQuestUi();
	//�κ��丮 â �¾�
	this->SetupInventoryUi();

	return D3D_OK;
}

void cUiTestScene::Reset(void)
{
	if(m_pFont) SAFE_RELEASE(m_pFont);
	if(m_pSprite) SAFE_RELEASE(m_pSprite);
	if(m_pTexture) SAFE_RELEASE(m_pTexture);
	if(m_pUiRoot) SAFE_RELEASE(m_pUiRoot);
//	SAFE_RELEASE(m_pMainRootImageView);
	if(m_pUiTestRoot) SAFE_RELEASE(m_pUiTestRoot);
//	SAFE_RELEASE(m_pMainMainButton);
	if(m_pInfoUi) SAFE_RELEASE(m_pInfoUi);
	if(m_pSkillUi) SAFE_RELEASE(m_pSkillUi);
	if(m_pQuestUi) SAFE_RELEASE(m_pQuestUi);
	if(m_pInventoryUi) SAFE_RELEASE(m_pInventoryUi);
}

void cUiTestScene::Update(void)
{
	this->changeMainButtonColor();
	//����â ������ (�ٽ� �����)
	if (m_isMainMin == true) m_pMainRootImageView->SetPosition(300, 520);
	else m_pMainRootImageView->SetPosition(300, 502);

	if (m_pUiRoot) m_pUiRoot->Update();
	if (m_pInfoUi && m_isInfoWindowOn) m_pInfoUi->Update();
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Update();
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Update();
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Update();


	//�̵�
	this->MoveUiWindow();
	//�κ� �� ����
	this->changeInventoryImage();
	
	if (m_pUiTestRoot) m_pUiTestRoot->Update();
}

void cUiTestScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	if (m_pUiRoot) m_pUiRoot->Render(m_pSprite);
	if (m_pInfoUi && m_isInfoWindowOn) m_pInfoUi->Render(m_pSprite);
	if (m_pSkillUi && m_isSkillWindowOn) m_pSkillUi->Render(m_pSprite);
	if (m_pQuestUi && m_isQuestWindowOn) m_pQuestUi->Render(m_pSprite);
	if (m_pInventoryUi && m_isInventoryWindowOn) m_pInventoryUi->Render(m_pSprite);
	//ũ�� �½�Ʈ��
	//if (m_pUiTestRoot) m_pUiTestRoot->Render(m_pSprite);
}

//��������Ʈ(Ŭ��)
void cUiTestScene::OnClick(cUIButton * pSender)
{
//	cUITextView* pTextView = (cUITextView*)m_pUiRoot->GetChildByTag(E_TEXT_VIEW);
//	pTextView->SetColor(D3DCOLOR_XRGB(0, 0, 0));
//	if (pTextView == NULL) return;

	if (pSender->GetTag() == E_MAIN_BUTTON_PLAYER_INFO)
	{
		m_isInfoWindowOn = !m_isInfoWindowOn;
	//	pTextView->SetText("�÷��̾� ����â �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_SKILL)
	{
		m_isSkillWindowOn = !m_isSkillWindowOn;
	//	pTextView->SetText("�÷��̾� ��ųâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_QUEST)
	{
		m_isQuestWindowOn = !m_isQuestWindowOn;
	//	pTextView->SetText("����Ʈâ �����ϱ�");
	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_INVENTORY)
	{
		m_isInventoryWindowOn = !m_isInventoryWindowOn;
	//	pTextView->SetText("�κ��丮 â �����ϱ�");
	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ABILITY)
//	{
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_ACTION)
//	{
//	}
//	else if (pSender->GetTag() == E_MAIN_BUTTON_PET)
//	{
//	}
	else if (pSender->GetTag() == E_MAIN_BUTTON_MIN)
	{
		m_isMainMin = !m_isMainMin;
	}
	else if (pSender->GetTag() == E_BUTTON_TEST1)
	{
		isPickUpItem = !isPickUpItem;
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

void cUiTestScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}