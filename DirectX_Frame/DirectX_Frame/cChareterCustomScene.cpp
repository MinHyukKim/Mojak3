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
	//플레이어 생성
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "Hair.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "lisaAniTest.X");

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

	//애니메이션 변형
	m_pPlayer->SetAnimation(cPlayer::ANIMATION_IDLE);


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

	if (g_pInputManager->IsOnceKeyDown('6')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair01_t01.X");
	if (g_pInputManager->IsOnceKeyDown('7')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair02_t02.X");
	if (g_pInputManager->IsOnceKeyDown('8')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair22_t22.X");
	if (g_pInputManager->IsOnceKeyDown('9')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "Hair.X");

	if (g_pInputManager->IsOnceKeyDown('R')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "lisaAniTest.X");
	if (g_pInputManager->IsOnceKeyDown('T')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_adventurer01.X");
	if (g_pInputManager->IsOnceKeyDown('Y')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_adventurer01_ani.X");
	if (g_pInputManager->IsOnceKeyDown('U')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "wear_female_armor01.X");
	if (g_pInputManager->IsOnceKeyDown('I')) m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/", "female_natural_stand_straight.X");


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
