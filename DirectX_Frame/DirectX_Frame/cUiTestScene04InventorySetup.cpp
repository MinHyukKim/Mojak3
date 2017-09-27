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
	//택스트
	m_pInventoryUiText = cUITextView::Create();
	m_pInventoryUiText->SetText("인벤토리");
	m_pInventoryUiText->SetFontType(g_pFontManager->E_INBUTTON);
	m_pInventoryUiText->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pInventoryUiText->SetSize(ST_SIZE(200, 100));
	m_pInventoryUiText->SetPosition(-30, -30);
	m_pInventoryUiText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pInventoryUiText->SetTag(E_BUTTON_NONE);
	m_pInventoryUi->AddChild(m_pInventoryUiText);
	//닫기 버튼
//	m_pInventoryCloseButton = cUIButton::Create();
//	m_pInventoryCloseButton->SetTexture("Texture/Ui/button_close_up.png"
//		, "Texture/Ui/button_close_over.png", "Texture/Ui/button_close_up.png");
//	m_pInventoryCloseButton->SetPosition(290, 10);
//	m_pInventoryCloseButton->SetDelegate(this);
//	m_pInventoryCloseButton->SetTag(E_BUTTON_INVENTORY_CLOSE);
//	m_pInventoryCloseButton->m_Alpha = 180;
//	m_pInventoryUi->AddChild(m_pInventoryCloseButton);

	//장비 이미지(전체)
	m_pInventoryUiEquipImage = cUIButton::Create();
	m_pInventoryUiEquipImage->SetTexture("Texture/Ui/inventory-equip.png",
		"Texture/Ui/inventory-equip.png", "Texture/Ui/inventory-equip.png");
	m_pInventoryUiEquipImage->SetPosition(10, 90);
	m_pInventoryUiEquipImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiEquipImage);
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

//	int x = 6, y = 10;
//	for each (auto p in m_vecInventoryUiBlock)
//	{
//		m_vecInventoryUiBlock[y * 6 + x] = cUIButton::Create();
//		m_vecInventoryUiBlock[y * 6 + x]->SetTexture("Texture/Ui/inventory1.png"
//			, "Texture/Ui/inventory1.png"
//			, "Texture/Ui/inventory1.png");
//		m_vecInventoryUiBlock[y * 6 + x]->SetPosition(x * 24 + stratX, y * 24 + stratY);
//		m_vecInventoryUiBlock[y * 6 + x]->SetTag(E_BUTTON_NONE);
//		m_pInventoryUi->AddChild(m_vecInventoryUiBlock[y * 6 + x]);
//	}


}