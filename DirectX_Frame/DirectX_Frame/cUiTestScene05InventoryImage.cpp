#include "stdafx.h"
#include "cUiTestScene.h"
//�׽�Ʈ��
#include "cFont.h"
//ui�½�Ʈ��
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//�÷��̾�
#include "cPlayer.h"
#include "cCamera.h"
//�̹���
#include "cImage.h"

void cUiTestScene::changeInventoryImage(void)
{
	//��ĭ
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


	//���ĭ
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
	//�Ž� ���� �׽�Ʈ
	switch (m_eEquipTorso)
	{
	case E_TORSO_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�00"));
	}
	break;
	case E_TORSO_WEAR_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�01"));
	}
	break;
	case E_TORSO_WEAR_02:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�02"));
	}
	break;
	case E_TORSO_WEAR_03:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�03"));
	}
	break;
	}

	switch (m_eEquipShoes)
	{
	case E_SHOES_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("�Ź�00"));
	}
	break;
	case E_SHOES_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("�Ź�00"));
	}
	break;
	}

	switch (m_eEquipWeaponHand)
	{
	default:
		break;
	}
}

