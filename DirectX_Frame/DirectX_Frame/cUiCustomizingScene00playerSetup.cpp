
#include "stdafx.h"
#include "cUiCustomizingScene.h"
//��Ʈ ��
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//�÷��̾�
#include "cPlayer.h"
#include "cCamera.h"

void cUiCustomizingScene::SetupPlayer(void)
{
	//�÷��̾� ����
	//�޽� �ε� �� ���� ����pSkinMesh = g_pSkinnedMeshManager->RegisterSkinnedMesh("Chareter/Female_Hair/", "hair_female_hair02_t02.X", "�Ӹ���Ÿ��");
	//	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/Female_Hair/", "hair_female_hair02_t02.X");
	//	pSkinMesh->SetTextureColor("hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pSkinMesh = g_pSkinnedMeshManager->RegisterSkinnedMesh("Chareter/Female_Hair/", "hair_female_hair02_t02.X", "�Ӹ���Ÿ��");

	//pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh()

	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/DefaultPlayer/", "wear_female_3rd_newbie.X");
	pSkinMesh->SetTextureColor("uni_shoes01_c.dds", &D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pSkinMesh->SetTextureColor("hair09.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pSkinMesh->SetTextureColor("bodymap01.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 1.0f));
	pSkinMesh->SetTextureColor("uni_newbie03_c.dds", &D3DXCOLOR(0.8f, 0.2f, 0.8f, 1.0f));
	pSkinMesh->SetTextureColor("uni_3rd_premium_c.dds", &D3DXCOLOR(0.5f, 0.0f, 0.1f, 1.0f));
	pSkinMesh->SetTextureColor("male_pumpkin_pants_c.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/Female_Face/", "basicFace.X");
	pSkinMesh->SetTextureColor("bodymap01.dds", &D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f));
	//pSkinMesh->SetTextureColor("bodymap04.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 1.0f));

	//�÷��̾� ����
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/Female_Hair/", "hair_female_hair02_t02.X");
	//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pPlayer->SetTextureHair("hair01.dds");  //���.dds
	m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.07f, 0.07f, 0.07f, 1.0f)); //��� ��
	//m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");

	m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_female_3rd_newbie.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAND, "Chareter/Female_Hand/", "basicFist.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_SHOES, "Chareter/Female_Shoes/", "basicShoes.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "Chareter/Female_Face/", "basicFace.X");
	m_pPlayer->SetTextureMouth("mouth_0.dds");
	m_pPlayer->SetTextureMouthColor(&D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pPlayer->SetTextureEye("eye_0.dds");
	m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.07f, 0.07f, 0.07f, 0.2f));
	//ī�޶� ����
	m_pMainCamera = m_pPlayer->GetCamera();
	m_pMainCamera->Setup();
	m_pMainCamera->UpdateProjection(0.1f);
	//��ġ
	//m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.7f, -0.4f));
	m_pMainCamera->MovePositionZ(4.5f);
	//	m_pMainCamera->AxisDirectionY(D3DX_PI / 2);
	//�ִϸ��̼� ���
	LPD3DXANIMATIONSET pAnimationSet;
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_stand_leftahead.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_5, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	//�ִϸ��̼� ����
	m_pPlayer->SetAnimation(cPlayer::ANIMATION_5);
}