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

void cUiTestScene::changeInventoryImage(void)
{
	//탬칸
	RECT rc;
	for (int i = 0; i < INVMAX; i++)
	{
		//IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_vecTempPlayerItem[i]->rc))
	//	for each(auto n in m_vecTempPlayerItem)
	//	{
	//	for (int j = 0; j < m_vecTempPlayerItem.size(); j++)
	//	{
			if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &m_vecTempPlayerItem[2]->rc))
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory2.png"
					, "Texture/Ui/inventory2.png", "Texture/Ui/inventory2.png");
			}
			else
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory1.png"
					, "Texture/Ui/inventory1.png", "Texture/Ui/inventory1.png");
			}
	//	}
	//	}	
	}


	//장비칸
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

	if (m_isShoesMount)
	{
		m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoesIn.png",
			"Texture/Ui/inventoryShoesOver.png",
			"Texture/Ui/inventoryShoesIn.png");
	}
	else
	{
		m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoes.png",
			"Texture/Ui/inventoryShoes.png",
			"Texture/Ui/inventoryShoes.png");
	}
}

void cUiTestScene::changePlayerMesh(void)
{
	//매쉬 변경 테스트
	switch (m_eEquipTorso)
	{
	case E_TORSO_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("바디00"));
	}
	break;
	case E_TORSO_WEAR_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("바디01"));
	}
	break;
	case E_TORSO_WEAR_02:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("바디02"));
	}
	break;
	case E_TORSO_WEAR_03:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("바디03"));
	}
	break;
	}

	switch (m_eEquipShoes)
	{
	case E_SHOES_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("신발00"));
	}
	break;
	case E_SHOES_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("신발00"));
	}
	break;
	}

	switch (m_eEquipWeaponHand)
	{
	default:
		break;
	}
}

