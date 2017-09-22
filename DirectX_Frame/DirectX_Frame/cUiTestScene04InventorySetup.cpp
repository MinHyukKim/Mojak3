#include "stdafx.h"
#include "cUiTestScene.h"
//테스트용
#include "cFont.h"
//ui태스트용
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

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
	m_pInventoryUiImage = cUIImageView::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventoryBase.png");
	m_pInventoryUiImage->SetPosition(2, 47);
	m_pInventoryUiImage->m_Alpha = 180;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//장비 이미지
	m_pInventoryUiImage = cUIImageView::Create();
	m_pInventoryUiImage->SetTexture("Texture/Ui/inventory-equip.png");
	m_pInventoryUiImage->SetPosition(10, 90);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiImage);
	//인벤 임시 이미지들
	int stratX = 160;
	int stratY = 90;
	int i = 24;
	//1줄
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

	//2줄
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

	//3줄
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

	//4줄
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

	//5줄
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

	//6줄
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

	//7줄
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

	//8줄
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

	//9줄
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 8);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
	//10줄
	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 0, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 1, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 2, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 3, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 4, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);

	m_pInventoryUiTempImage = cUIImageView::Create();
	m_pInventoryUiTempImage->SetTexture("Texture/Ui/inventory1.png");
	m_pInventoryUiTempImage->SetPosition(stratX + i * 5, stratY + i * 9);
	m_pInventoryUiImage->m_Alpha = 200;
	m_pInventoryUi->AddChild(m_pInventoryUiTempImage);
}