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
	//	if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_vecTempPlayerItem[i]->rc)))
	//	{
	//		m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory2.png"
	//			, "Texture/Ui/inventory2.png", "Texture/Ui/inventory2.png");
	//	}
	//	else
	//	{
	//		m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory1.png"
	//			, "Texture/Ui/inventory1.png", "Texture/Ui/inventory1.png");
	//	}

		for (int j = 0; j < m_vecTempPlayerItem.size(); j++)
		{
		//	if (m_vecTempPlayerItem[j] == NULL) return;
			if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_vecTempPlayerItem[j]->rc)))
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory2.png"
					, "Texture/Ui/inventory2.png", "Texture/Ui/inventory2.png");
				break;
			}
			else
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory1.png"
					, "Texture/Ui/inventory1.png", "Texture/Ui/inventory1.png");
			}
	/*		if (IntersectRect(&rc, &(m_pInventoryUiBlock[i]->rc), &(m_vecTempPlayerItem[0]->rc)))
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory2.png"
					, "Texture/Ui/inventory2.png", "Texture/Ui/inventory2.png");
			}
			else
			{
				m_pInventoryUiBlock[i]->SetTexture("Texture/Ui/inventory1.png"
					, "Texture/Ui/inventory1.png", "Texture/Ui/inventory1.png");
			}*/
		}
	}


	//���ĭ
	if (m_isTorsoMount > -1)
	{
		m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorsoin.png",
			"Texture/Ui/inventoryTorsoOver.png", "Texture/Ui/inventoryTorsoin.png");
	}
	else if(m_isTorsoMount < 0)
	{
		m_pInventoryUiEquipTorso->SetTexture("Texture/Ui/inventoryTorso.png",
			"Texture/Ui/inventoryTorso.png", "Texture/Ui/inventoryTorso.png");
	}

	if (m_isShoesMount > -1)
	{
		m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoesIn.png",
			"Texture/Ui/inventoryShoesOver.png", "Texture/Ui/inventoryShoesIn.png");
	}
	else if(m_isShoesMount < 0)
	{
		m_pInventoryUiEquipShoes->SetTexture("Texture/Ui/inventoryShoes.png",
			"Texture/Ui/inventoryShoes.png", "Texture/Ui/inventoryShoes.png");
	}
}

void cUiTestScene::changePlayerMesh(void)
{
//	if (m_isTorsoMount == -1)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�00"));
//		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(7);
//	}
//	else if (m_isTorsoMount == 0)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�01")); 
//		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(10);
//	}
//	else if (m_isTorsoMount == 1)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�02"));
//		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(15);
//	}
//	else if (m_isTorsoMount == 2)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�03"));
//		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(30);
//	}
//
//	if (m_isShoesMount == -1)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, nullptr);
//	}
//	else if (m_isShoesMount == 3)
//	{
//		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("�Ź�00"));
//	}

	//�Ž� ���� �׽�Ʈ
	switch (m_eEquipTorso)
	{
	case E_TORSO_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�00"));
		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(7);
		m_nWearDef = 0;
	}
	break;
	case E_TORSO_WEAR_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�01"));
		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(9);
		m_nWearDef = 2;
	}
	break;
	case E_TORSO_WEAR_02:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�02"));
		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(12);
		m_nWearDef = 5;
	}
	break;
	case E_TORSO_WEAR_03:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("�ٵ�03"));
		g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(25);
		m_nWearDef = 10;
	}
	break;
	}

	switch (m_eEquipShoes)
	{
	case E_SHOES_EMPTY:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, nullptr);
		m_nShoesDef = 0;
	}
	break;
	case E_SHOES_01:
	{
		g_pObjectManager->GetPlayer()->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("�Ź�00"));
		m_nShoesDef = 2;
	}
	break;
	}


	g_pObjectManager->GetPlayer()->GetAbilityParamter()->SetDefence(m_nBasicDef + m_nWearDef + m_nShoesDef);
}

