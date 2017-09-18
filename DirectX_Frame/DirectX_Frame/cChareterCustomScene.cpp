#include "stdafx.h"
#include "cChareterCustomScene.h"

#include "cPlayer.h"
#include "cCamera.h"

cChareterCustomScene::cChareterCustomScene(void)
	: m_pMainCamera(NULL)
	, m_pPlayer(NULL)
{
}

cChareterCustomScene::~cChareterCustomScene(void)
{
	this->Reset();
}

HRESULT cChareterCustomScene::Setup(void)
{
	//메시 로드 및 색상 편집
	cSkinnedMesh* pSkinMesh;
	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/Female_Hair/", "hair_female_hair02_t02.X");
	pSkinMesh->SetTextureColor("hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/DefaultPlayer/", "lisaAniTest.X");
	pSkinMesh->SetTextureColor("uni_shoes01_c.dds", &D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pSkinMesh->SetTextureColor("hair09.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pSkinMesh->SetTextureColor("bodymap01.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 1.0f));
	pSkinMesh->SetTextureColor("uni_newbie03_c.dds", &D3DXCOLOR(0.8f, 0.2f, 0.8f, 1.0f));
	pSkinMesh->SetTextureColor("uni_3rd_premium_c.dds", &D3DXCOLOR(0.5f, 0.0f, 0.1f, 1.0f));
	pSkinMesh->SetTextureColor("male_pumpkin_pants_c.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("./Chareter/Female_Face/", "basicFace.X");

	//플레이어 생성
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/Female_Hair/", "hair_female_hair02_t02.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_FACE, "mouth_0.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/Female_Body/", "basicBody.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAND, "Chareter/Female_Hand/", "basicFist.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_SHOES, "Chareter/Female_Shoes/", "basicShoes.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "Chareter/Female_Face/", "basicFace.X");

	//카메라 연결
	m_pMainCamera = m_pPlayer->GetCamera();
	m_pMainCamera->Setup();

	//애니메이션 등록
	LPD3DXANIMATIONSET pAnimationSet;
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_attack_01.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_IDLE, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_blow_away.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_2, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_blow_ground.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_3, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_run.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_4, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_stand_leftahead.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_5, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);

	//추가된 애니메이션 매니저 사용법 위에 대신 아래와 같이 사용합니다.
	g_pAnimationManager->RegisterAnimation("./Chareter/DefaultPlayer/aniTest/ani_female_attack_01.X", "공격1");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_6, g_pAnimationManager->GetAnimation("공격1"));
	g_pAnimationManager->RegisterAnimation("./Chareter/DefaultPlayer/aniTest/ani_female_run.X", "뛰기가 아니네?");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_7, g_pAnimationManager->GetAnimation("뛰기가 아니네?"));

	//애니메이션 변형
	m_pPlayer->SetAnimation(cPlayer::ANIMATION_IDLE);

	m_n = 0;

	return S_OK;
}

void cChareterCustomScene::Reset(void)
{
	SAFE_RELEASE(m_pPlayer);
}

void cChareterCustomScene::Update(void)
{
	if (g_pInputManager->IsOnceKeyDown('1')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_IDLE);
	if (g_pInputManager->IsOnceKeyDown('2')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_2);
	if (g_pInputManager->IsOnceKeyDown('3')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_3);
	if (g_pInputManager->IsOnceKeyDown('4')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_4);
	if (g_pInputManager->IsOnceKeyDown('5')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_5);
	if (g_pInputManager->IsOnceKeyDown('6')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_6);
	if (g_pInputManager->IsOnceKeyDown('7')) m_pPlayer->SetAnimation(cPlayer::ANIMATION_7);

	if (g_pInputManager->IsOnceKeyDown('8')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair01_t01.X");
	if (g_pInputManager->IsOnceKeyDown('9')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair02_t02.X");
	if (g_pInputManager->IsOnceKeyDown('0')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair22_t22.X");
	if (g_pInputManager->IsOnceKeyDown('-')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "Hair.X");

	if (g_pInputManager->IsOnceKeyDown('R')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "lisaAniTest.X");
	if (g_pInputManager->IsOnceKeyDown('T')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_adventurer01.X");
	if (g_pInputManager->IsOnceKeyDown('Y')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_adventurer01_ani.X");
	if (g_pInputManager->IsOnceKeyDown('U')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_female_armor01.X");
	if (g_pInputManager->IsOnceKeyDown('I')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/", "female_natural_stand_straight.X");

	if (g_pInputManager->IsOnceKeyDown('F')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAND, "Chareter/Female_Hand/", "basicFist.X");
	if (g_pInputManager->IsOnceKeyDown('P')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAND, "Chareter/Female_Hand/", "basicPalm.X");




	SAFE_UPDATE(m_pPlayer);
	if (m_pMainCamera)
	{
		m_pMainCamera->TestController();
		m_pMainCamera->Update();
	}
}

void cChareterCustomScene::Render(void)
{
	SAFE_RENDER(m_pPlayer);
}

cChareterCustomScene* cChareterCustomScene::Create(void)
{
	cChareterCustomScene* newClass = new cChareterCustomScene;
	newClass->AddRef();
	return newClass;
}
