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

void cUiTestScene::changeInventoryImage(void)
{
	for (int i = 0; i < 60; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_pTempItem->rc)))
		{
			m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory2.png"
				, "Texture/Ui/inventory2.png"
				, "Texture/Ui/inventory2.png");
		}
		else
		{
			m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png"
				, "Texture/Ui/inventory1.png");
		}
	}

	if (m_isTorsoMount)
	{
		m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorsoin.png",
			"Texture/Ui/inventoryTorsoOver.png",
			"Texture/Ui/inventoryTorsoin.png");
	}
	else
	{
		m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorso.png",
			"Texture/Ui/inventoryTorso.png",
			"Texture/Ui/inventoryTorso.png");
	}
}

