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

void cUiTestScene::SetupInventoryUi(void)
{
	//인벤토리 창 머리
	m_pInventoryUiImageHead = cUIImageView::Create();
	m_pInventoryUiImageHead->SetTexture("Texture/Ui/inventoryBaseHead1.png");
	m_pInventoryUiImageHead->SetPosition(invX, invY);
	m_pInventoryUiImageHead->m_Alpha = 200;
	m_pInventoryUi = m_pInventoryUiImageHead;
	//드래그 버튼
	m_pInventoryUiMoveing = cUIButton::Create();
	m_pInventoryUiMoveing->SetTexture("Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png",
		"Texture/Ui/inventoryBaseHead1.png");
	m_pInventoryUiMoveing->SetPosition(0, 0);
	m_pInventoryUiMoveing->SetDelegate(this);
	m_pInventoryUiMoveing->m_Alpha = 0;
	m_pInventoryUiMoveing->SetTag(E_INVENTORY_MOVE);
	m_pInventoryUi->AddChild(m_pInventoryUiMoveing);
	//인벤 전체 창
	m_pInventoryUiImage = cUIButton::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventoryBase.png"
	, "Texture/Ui/inventoryBase.png", "Texture/Ui/inventoryBase.png");
	m_pInventoryUiImage->SetPosition(2, 47);
	m_pInventoryUiImage->m_Alpha = 180;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//장비 이미지(전체)
	m_pInventoryUiImage = cUIButton::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventory-equip.png",
		"Texture/Ui/inventory-equip.png", "Texture/Ui/inventory-equip.png");
	m_pInventoryUiImage->SetPosition(10, 90);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//장비 장착 칸 (몸통) x = 48 + 10 + 2, y = 57 + 90
	m_pInventoryUiEquipTorso = cUIButton::Create();
	m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorso.png",
		"Texture/Ui/inventoryTorso.png",
		"Texture/Ui/inventoryTorso.png");
	m_pInventoryUiEquipTorso->SetPosition(60, 147);
	m_pInventoryUiEquipTorso->SetDelegate(this);
//	m_pInventoryUiMoveing->m_Alpha = 0;
	m_pInventoryUiEquipTorso->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipTorso);
	//장비 장착 칸 (무기 손)
	m_pInventoryUiEquipWeaponHand = cUIButton::Create();
	m_pInventoryUiEquipWeaponHand->SetTexture("Texture/Ui/inventoryWeaponHand.png",
		"Texture/Ui/inventoryWeaponHand.png",
		"Texture/Ui/inventoryWeaponHand.png");
	m_pInventoryUiEquipWeaponHand->SetPosition(12, 155);
	m_pInventoryUiEquipWeaponHand->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipWeaponHand);
	//장비 장착 칸 (나머지 손)
	m_pInventoryUiEquipSubHand = cUIButton::Create();
	m_pInventoryUiEquipSubHand->SetTexture("Texture/Ui/inventorySubWeaponHand.png",
		"Texture/Ui/inventorySubWeaponHand.png",
		"Texture/Ui/inventorySubWeaponHand.png");
	m_pInventoryUiEquipSubHand->SetPosition(109, 155);
	m_pInventoryUiEquipSubHand->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipSubHand);
	//장비 장착 칸 (발)
	m_pInventoryUiEquipShoes = cUIButton::Create();
	m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoes.png",
		"Texture/Ui/inventoryShoes.png",
		"Texture/Ui/inventoryShoes.png");
	m_pInventoryUiEquipShoes->SetPosition(60, 235);
	m_pInventoryUiEquipShoes->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiEquipShoes);


	int stratX = 160;
	int stratY = 90;
	int i = 24;
	//아이탬 칸
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			m_pInventoryUiBlock[i * 6 + j] = cUIButton::Create();
			m_pInventoryUiBlock[i * 6 + j]->SetTexture("Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png");
			m_pInventoryUiBlock[i * 6 + j]->SetPosition(j * 24 + stratX, i * 24 + stratY);
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

	//임시
//	m_pTempItem = cUIButton::Create();
//	m_pTempItem->SetTexture("Texture/Ui/testItem1-1.png",
//		"Texture/Ui/testItem1-1.png",
//		"Texture/Ui/testItem1-1.png");
//	m_pTempItem->SetPosition(160, 90);
//	m_pTempItem->SetTag(E_BUTTON_TEST1);
//	m_pInventoryUi->AddChild(m_pTempItem);
	//임시2
	//m_pTempItemArr
//	for (int i = 0; i < 5; i++)
//	{
		m_pTempItemArr[0] = cUIButton::Create();
		m_pTempItemArr[0]->SetTexture("Texture/Ui/testItem1-2.png"
			, "Texture/Ui/testItem1-2.png"
			, "Texture/Ui/testItem1-2.png");
		m_pTempItemArr[0]->SetPosition(160, 90);
		m_pTempItemArr[0]->SetDelegate(this);
		m_pTempItemArr[0]->SetTag(E_ITEM_WEAR1);
		m_pInventoryUi->AddChild(m_pTempItemArr[0]);

//		m_pTempItemArr[1] = cUIButton::Create();
//		m_pTempItemArr[1]->SetTexture("Texture/Ui/testItem2-1.png"
//			, "Texture/Ui/testItem2-1.png"
//			, "Texture/Ui/testItem2-1.png"); //60, 147
//	//	m_pTempItemArr[1]->SetPosition(160 + 48, 90);
//		m_pTempItemArr[1]->SetPosition(60, 147);
//		m_pTempItemArr[1]->SetDelegate(this);
//		m_pTempItemArr[1]->SetTag(E_ITEM_WEAR1);
//		m_pInventoryUi->AddChild(m_pTempItemArr[1]);
//	}
}