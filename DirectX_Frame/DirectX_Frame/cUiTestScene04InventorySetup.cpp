#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

void cUiTestScene::SetupInventoryUi(void)
{
	//�κ��丮 â �Ӹ�
	m_pInventoryUiImageHead = cUIImageView::Create();
	m_pInventoryUiImageHead->SetTexture("Texture/Ui/inventoryBaseHead1.png");
	m_pInventoryUiImageHead->SetPosition(invX, invY);
	m_pInventoryUiImageHead->m_Alpha = 200;
	m_pInventoryUi = m_pInventoryUiImageHead;
	//�巡�� ��ư
	m_pInventoryUiMoveing = cUIButton::Create();
	m_pInventoryUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pInventoryUiMoveing->SetPosition(0, 0);
	m_pInventoryUiMoveing->SetDelegate(this);
	m_pInventoryUiMoveing->m_Alpha = 0;
	m_pInventoryUiMoveing->SetTag(E_INVENTORY_MOVE);
	m_pInventoryUi->AddChild(m_pInventoryUiMoveing);
	//�κ� ��ü â
	m_pInventoryUiImage = cUIButton::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventoryBase.png"
	, "Texture/Ui/inventoryBase.png", "Texture/Ui/inventoryBase.png");
	m_pInventoryUiImage->SetPosition(2, 47);
	m_pInventoryUiImage->m_Alpha = 180;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//��� �̹���(��ü)
	m_pInventoryUiImage = cUIButton::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventory-equip.png",
		"Texture/Ui/inventory-equip.png", "Texture/Ui/inventory-equip.png");
	m_pInventoryUiImage->SetPosition(10, 90);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//��� ���� ĭ (����) x = 48 + 10 + 2, y = 57 + 90
	m_pInventoryUiEquipTorso = cUIButton::Create();
	m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorso.png",
		"Texture/Ui/inventoryTorsoOver.png",
		"Texture/Ui/inventoryTorsoIn.png");
	m_pInventoryUiEquipTorso->SetPosition(60, 147);
	m_pInventoryUiEquipTorso->SetDelegate(this);
//	m_pInventoryUiMoveing->m_Alpha = 0;
	m_pInventoryUiEquipTorso->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipTorso);
	//��� ���� ĭ (���� ��)
	m_pInventoryUiEquipWeaponHand = cUIButton::Create();
	m_pInventoryUiEquipWeaponHand->SetTexture("Texture/Ui/inventoryWeaponHand.png",
		"Texture/Ui/inventoryWeaponHandOver.png",
		"Texture/Ui/inventoryWeaponHandIn.png");
	m_pInventoryUiEquipWeaponHand->SetPosition(12, 155);
	m_pInventoryUiEquipWeaponHand->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipWeaponHand);
	//��� ���� ĭ (������ ��)
	m_pInventoryUiEquipSubHand = cUIButton::Create();
	m_pInventoryUiEquipSubHand->SetTexture("Texture/Ui/inventorySubWeaponHand.png",
		"Texture/Ui/inventorySubWeaponHandOver.png",
		"Texture/Ui/inventorySubWeaponHandIn.png");
	m_pInventoryUiEquipSubHand->SetPosition(109, 155);
	m_pInventoryUiEquipSubHand->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipSubHand);
	//��� ���� ĭ (��)
	m_pInventoryUiEquipShoes = cUIButton::Create();
	m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoes.png",
		"Texture/Ui/inventoryShoesOver.png",
		"Texture/Ui/inventoryShoesIn.png");
	m_pInventoryUiEquipShoes->SetPosition(60, 235);
	m_pInventoryUiEquipShoes->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipShoes);


	//�κ� �ӽ� �̹�����
	//int stratX = 160;
	//int stratY = 90;
	//int i = 24;
	//1��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//2��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 1);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//3��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 2);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//4��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 3);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//5��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 4);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//6��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 5);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//7��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 6);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//8��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 7);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	//9��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 8);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//	//10��
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
//
//	m_pInventoryUiTempImage = cUIImageView::Create();
//	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
//	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 9);
//	m_pInventoryUiImage->m_Alpha = 200;
//	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	int stratX = 160;
	int stratY = 90;
	int i = 24;
	//������ ĭ
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			m_pInventoryUiBlock[i * 6 + j] = cUIButton::Create();
			m_pInventoryUiBlock[i * 6 + j]->SetTexture("Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png");
			m_pInventoryUiBlock[i * 6 + j]->SetPosition(j* 24 + stratX, i * 24 + stratY);
			m_pInventoryUiBlock[i * 6 + j]->SetTag(E_BUTTON_NONE);
			m_pInventoryUi->AddChild(m_pInventoryUiBlock[i * 6 + j]);
		}
	}

//	m_pInventoryUiEquipShoes = cUIButton::Create();
//	m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoes.png",
//		"Texture/Ui/inventoryShoesOver.png",
//		"Texture/Ui/inventoryShoesIn.png");
//	m_pInventoryUiEquipShoes->SetPosition(60, 235);
//	m_pInventoryUiEquipShoes->SetTag(E_BUTTON_NONE);
//	m_pInventoryUi->AddChild(m_pInventoryUiEquipShoes);

	m_pTempItem = cUIButton::Create();
	m_pTempItem->SetTexture("Texture/Ui/testItem1-1.png",
		"Texture/Ui/testItem1-1.png",
		"Texture/Ui/testItem1-1.png");
	m_pTempItem->SetPosition(160, 90);
	m_pTempItem->SetTag(E_BUTTON_TEST1);
	m_pInventoryUi->AddChild(m_pTempItem);
}