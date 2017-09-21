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
	//
	, m_pInfoUi(NULL)
	, m_pSkillUi(NULL)
	, m_pQuestUi(NULL)
	, m_pInventoryUi(NULL)
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
	
//	//Ŀ�� â �Ӹ�
//	m_pCustomImageHead = cUIImageView::Create();
//	m_pCustomImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
//	m_pCustomImageHead->SetPosition(m_nX, m_nY);
//	m_pCustomImageHead->m_Alpha = 200;
//	m_pCustomUi = m_pCustomImageHead;
//	//Ŀ�� â
//	m_pCustomImage = cUIImageView::Create();
//	m_pCustomImage->SetTexture("Texture/Ui/customUiBase2.png");
//	m_pCustomImage->SetPosition(2, 48);
//	m_pCustomImage->m_Alpha = 180;
//	m_pCustomUi->AddChild(m_pCustomImage);

	//���� â �Ӹ�
	m_pInfoUiImageHead = cUIImageView::Create();
	m_pInfoUiImageHead->SetTexture("Texture/Ui/infoBaseHead1.png");
	m_pInfoUiImageHead->SetPosition(354, 20);
	m_pInfoUiImageHead->m_Alpha = 200;
	m_pInfoUi = m_pInfoUiImageHead;
	//���� ���̽� â
	m_pInfoUiImage = cUIImageView::Create();
	m_pInfoUiImage->SetTexture("Texture/Ui/Base.png");
	m_pInfoUiImage->SetPosition(2, 48);
	m_pInfoUiImage->m_Alpha = 180;
	m_pInfoUi->AddChild(m_pInfoUiImage);

	//��ų �Ӹ� â
	m_pSkillUiImageHead = cUIImageView::Create();
	m_pSkillUiImageHead->SetTexture("Texture/Ui/skillBaseHead1.png");
	m_pSkillUiImageHead->SetPosition(680, 20);
	m_pSkillUiImageHead->m_Alpha = 200;
	m_pSkillUi = m_pSkillUiImageHead;
	//��ų â ���̽�
	m_pSkillUiImage = cUIImageView::Create();
	m_pSkillUiImage->SetTexture("Texture/Ui/Base.png");
	m_pSkillUiImage->SetPosition(2, 48);
	m_pSkillUiImage->m_Alpha = 180;
	m_pSkillUi->AddChild(m_pSkillUiImage);

	//����Ʈ â �Ӹ�
	m_pQuestUiImageHead = cUIImageView::Create();
	m_pQuestUiImageHead->SetTexture("Texture/Ui/questBaseHead1.png");
	m_pQuestUiImageHead->SetPosition(500, 60);
	m_pQuestUiImageHead->m_Alpha = 200;
	m_pQuestUi = m_pQuestUiImageHead;
	//����Ʈ â
	m_pQuestUiImage = cUIImageView::Create();
	m_pQuestUiImage->SetTexture("Texture/Ui/Base.png");
	m_pQuestUiImage->SetPosition(2, 48);
	m_pQuestUiImage->m_Alpha = 180;
	m_pQuestUi->AddChild(m_pQuestUiImage);

	//�κ��丮 â �Ӹ�
	m_pInventoryUiImageHead = cUIImageView::Create();
	m_pInventoryUiImageHead->SetTexture("Texture/Ui/inventoryBaseHead1.png");
	m_pInventoryUiImageHead->SetPosition(20, 20);
	m_pInventoryUiImageHead->m_Alpha = 200;
	m_pInventoryUi = m_pInventoryUiImageHead;
	//�κ� ��ü â
	m_pInventoryUiImage = cUIImageView::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventoryBase.png");
	m_pInventoryUiImage->SetPosition(2, 48);
	m_pInventoryUiImage->m_Alpha = 180;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//��� �̹���
	m_pInventoryUiImage = cUIImageView::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventory-equip.png");
	m_pInventoryUiImage->SetPosition(10, 90);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//�κ� �ӽ� �̹�����
	int stratX = 160;
	int stratY = 90;
	int i = 24;
	//1��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
	
	//2��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 1);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//3��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 2);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//4��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;								  
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);				  
																	  
	m_pInventoryUiTempImage = cUIImageView::Create();				  
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png"); 
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;								  
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);				  
																	  
	m_pInventoryUiTempImage = cUIImageView::Create();				  
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png"); 
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;								  
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);				  
																	  
	m_pInventoryUiTempImage = cUIImageView::Create();				  
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png"); 
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;								  
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);				  
																	  
	m_pInventoryUiTempImage = cUIImageView::Create();				  
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png"); 
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 3);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//5��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 4);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//6��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 5);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//7��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 6);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	//8��
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 7);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
	

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
