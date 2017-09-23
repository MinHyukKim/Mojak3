#include "stdafx.h"
#include "cObjectManager.h"

#include "cPlayer.h"

cObjectManager::cObjectManager(void)
	: m_pPlayer(nullptr)
{
}

cObjectManager::~cObjectManager(void)
{
}

void cObjectManager::Update(void)
{
	SAFE_UPDATE(m_pPlayer);
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Update();
	}
	for each (auto pRelease in m_vecRelease)
	{
		for (std::vector<cPlayer*>::iterator it = m_vecMonster.begin(); it != m_vecMonster.end(); it++)
		{
			if (pRelease != *it) continue;
			(*it)->GetAbilityParamter()->SetEffective(false);
			m_vecMonster.erase(it);
			break;
		}
	}
	m_vecRelease.clear();
}

void cObjectManager::Render(void)
{
	SAFE_RENDER(m_pPlayer);
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Render();
	}
}

void cObjectManager::RegisterPlayer(IN cPlayer* pPlayer)
{
	SAFE_RELEASE(m_pPlayer);
	m_pPlayer = pPlayer;
	m_pPlayer->GetAbilityParamter()->SetPlayerID(1);
	m_pPlayer->GetAbilityParamter()->SetUnitID(0);
	m_pPlayer->AddRef();
}

void cObjectManager::SavePlayerData(IN LPCSTR FullPath)
{
	assert(false && "미구현");
}

void cObjectManager::LoadPlayerData(IN LPCSTR FullPath)
{
	assert(false && "미구현");
}

bool cObjectManager::CreateMonster(IN MONSTER_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion)
{
	cPlayer* pCreateMonster = nullptr;
	switch (eMonsterKey)
	{
	case cObjectManager::MONSTER_NULL: break;

	case cObjectManager::MONSTER_TEXTER:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("임시몬스터"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_PEACEFUL, g_pAnimationManager->GetAnimation("여성_기본01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_기본02"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_PEACEFUL, g_pAnimationManager->GetAnimation("여성_걷기01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_걷기02"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_PEACEFUL, g_pAnimationManager->GetAnimation("여성_달리기01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_달리기02"));
		pCreateMonster->GetAbilityParamter()->SetPlayerID(2);
		pCreateMonster->GetAbilityParamter()->SetUnitID(1);
	}	break;

	default: break;
	}

	if (pCreateMonster)
	{
		m_vecMonster.push_back(pCreateMonster);
		return true;
	}
	return false;
}

void cObjectManager::Destroy(void)
{
	SAFE_RELEASE(m_pPlayer);
}

