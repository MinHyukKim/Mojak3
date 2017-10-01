#include "stdafx.h"
#include "cObjectManager.h"

#include "cPlayer.h"
#include "cMapTerrain.h"

cObjectManager::cObjectManager(void)
	: m_pPlayer(nullptr)
	, m_pTerrain(nullptr)
{
}

cObjectManager::~cObjectManager(void)
{
}

void cObjectManager::Update(void)
{
	SAFE_UPDATE(m_pTerrain);
	SAFE_UPDATE(m_pPlayer);
	if (m_pTerrain)
	{
		float fHeight = m_pPlayer->GetPosY();
		m_pTerrain->GetHeight(&fHeight, m_pPlayer->GetPosX(), m_pPlayer->GetPosZ());
		m_pPlayer->SetPosY(fHeight);
	}
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Update();
		if (m_pTerrain)
		{
			float fHeight = pMonster->GetPosY();
			m_pTerrain->GetHeight(&fHeight, pMonster->GetPosX(), pMonster->GetPosZ());
			pMonster->SetPosY(fHeight);
		}
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
	SAFE_RENDER(m_pTerrain);
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Render();
	}
}

void cObjectManager::Controller(void)
{
}

cPlayer* cObjectManager::GetMinRangeMonster(cPlayer* pCenter, float fRange)
{
	D3DXVECTOR3 vCenter = pCenter->GetPosition();
	float fDirectionSq = fRange * fRange;
	cPlayer* pTarget = nullptr;
	for each (auto pMonster in m_vecMonster)
	{
		float fLengthSq = D3DXVec3LengthSq(&(pMonster->GetPosition() - vCenter));
		if (fDirectionSq <= fLengthSq) continue;
		pTarget = pMonster;
		fDirectionSq = fLengthSq;
	}
	return pTarget;
}

void cObjectManager::GetNextTarget(cPlayer ** ppTarget, LPD3DXVECTOR3 pCenter, float fRange)
{
	float fDirectionSq, fMinRangeSq, fMaxRangeSq;
	fDirectionSq = fMinRangeSq = D3DXVec3LengthSq(&((*ppTarget)->GetPosition() - (*pCenter)));
	fMaxRangeSq = fRange * fRange;

	cPlayer* pMinTarget = nullptr;
	cPlayer* pNextTarget = nullptr;

	for each (auto pMonster in m_vecMonster)
	{
		if (*ppTarget == pMonster) continue;
		float fLengthSq = D3DXVec3LengthSq(&(pMonster->GetPosition() - (*pCenter)));
		if (fMaxRangeSq <= fLengthSq) continue;
		if (pNextTarget)
		{
			if (fMinRangeSq < fLengthSq)
			{
				pNextTarget = pMonster;
				fMaxRangeSq = fLengthSq;
			}
		}
		else
		{
			if (fMinRangeSq < fLengthSq)
			{
				pNextTarget = pMonster;
				fMaxRangeSq = fLengthSq;
			}
			else if (fDirectionSq > fLengthSq)
			{
				pMinTarget = pMonster;
				fDirectionSq = fLengthSq;
			}

		}
	}

	if (pNextTarget)
	{
		SAFE_RELEASE(*ppTarget);
		(*ppTarget) = pNextTarget;
		pNextTarget->AddRef();
	}
	else if	(pMinTarget)
	{
		SAFE_RELEASE(*ppTarget);
		(*ppTarget) = pMinTarget;
		pMinTarget->AddRef();
	}
}

void cObjectManager::RegisterPlayer(IN cPlayer* pPlayer)
{
	SAFE_RELEASE(m_pPlayer);
	m_pPlayer = pPlayer;
	m_pPlayer->SetRadius(0.3f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_기본02"));
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_WALK_FRIENDLY, g_pAnimationManager->GetAnimation("여성_걷기01"), 3.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_걷기02"), 3.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_RUN_FRIENDLY, g_pAnimationManager->GetAnimation("여성_달리기01"), 3.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_달리기02"), 3.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_ATTACK_01, g_pAnimationManager->GetAnimation("여성_공격01"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_ATTACK_02, g_pAnimationManager->GetAnimation("여성_공격02"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_HIT_01, g_pAnimationManager->GetAnimation("여성_피격01"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_HIT_02, g_pAnimationManager->GetAnimation("여성_피격02"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_ENDURE_01, g_pAnimationManager->GetAnimation("여성_밀려남01"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_ENDURE_02, g_pAnimationManager->GetAnimation("여성_밀려남02"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_SMASH, g_pAnimationManager->GetAnimation("여성_스매시"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_SPIN, g_pAnimationManager->GetAnimation("여성_스핀"), 2.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_GROGGY, g_pAnimationManager->GetAnimation("여성_그로기"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_DOWND, g_pAnimationManager->GetAnimation("여성_다운드"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_DOWN_TO_STAND, g_pAnimationManager->GetAnimation("여성_다운투스텐드"), 5.0f);
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_COUNTER, g_pAnimationManager->GetAnimation("여성_카운터"), 2.0f);
	
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

bool cObjectManager::GetMonster(OUT cPlayer** ppMonster, IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir)
{
	cPlayer* pTarget = nullptr;
	float fDist = 1000.0f;
	for each (auto pMonster in m_vecMonster)
	{
		if (!pMonster->IsCollision(pRay, pDir)) continue;
		float fLength = D3DXVec3Length(&(pMonster->GetPosition() - (*pRay)));
		if (fLength >= fDist) continue;
		pTarget = pMonster;
		fDist = fLength;
	}
	*ppMonster = pTarget;
	return pTarget;
}

void cObjectManager::SetTerrain(IN cMapTerrain* pTerrain)
{
	SAFE_RELEASE(m_pTerrain);
	m_pTerrain = pTerrain;
	m_pTerrain->AddRef();
}

bool cObjectManager::CreateMonster(IN UNIT_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion, IN LPD3DXCOLOR pColor)
{
	cPlayer* pCreateMonster = nullptr;
	switch (eMonsterKey)
	{
	case cObjectManager::MONSTER_NULL: break;

	case cObjectManager::MONSTER_TEXTER:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->Setup();
		pCreateMonster->SetRadius(0.3f);
		pCreateMonster->SetupAnimationController();
		pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("임시몬스터"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY, g_pAnimationManager->GetAnimation("여성_기본01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_기본02"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_FRIENDLY, g_pAnimationManager->GetAnimation("여성_걷기01"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_걷기02"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_FRIENDLY, g_pAnimationManager->GetAnimation("여성_달리기01"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여성_달리기02"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_01, g_pAnimationManager->GetAnimation("여성_공격01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_02, g_pAnimationManager->GetAnimation("여성_공격02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_01, g_pAnimationManager->GetAnimation("여성_피격01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_02, g_pAnimationManager->GetAnimation("여성_피격02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_01, g_pAnimationManager->GetAnimation("여성_밀려남01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_02, g_pAnimationManager->GetAnimation("여성_밀려남02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SMASH, g_pAnimationManager->GetAnimation("여성_스매시"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SPIN, g_pAnimationManager->GetAnimation("여성_스핀"), 2.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_GROGGY, g_pAnimationManager->GetAnimation("여성_그로기"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWND, g_pAnimationManager->GetAnimation("여성_다운드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWN_TO_STAND, g_pAnimationManager->GetAnimation("여성_다운투스텐드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_COUNTER, g_pAnimationManager->GetAnimation("여성_카운터"), 2.0f);
		pCreateMonster->GetAbilityParamter()->SetPlayerID(2);
		pCreateMonster->GetAbilityParamter()->SetUnitID(cObjectManager::MONSTER_TEXTER);
		pCreateMonster->OrderFriendly();
	}	break;

	case cObjectManager::MONSTER_FOX:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->Setup();
		pCreateMonster->SetRadius(0.3f);
		pCreateMonster->SetupAnimationController("여우00");
		if (pColor)
		{
			char szText[1024] = {};
			sprintf_s(szText, "여우(%1.2f,%1.2f,%1.2f,%1.2f)", pColor->r, pColor->g, pColor->b, pColor->a);
			pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->CloneSkinnedMesh("여우01", szText));
			pCreateMonster->ChangeMeshPartColor(cPlayer::MESH_BODY, "mon_fox02.dds", pColor);
		}
		else pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("여우01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY, g_pAnimationManager->GetAnimation("여우_기본01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("여우_기본02"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_FRIENDLY, g_pAnimationManager->GetAnimation("여우_걷기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여우_걷기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_FRIENDLY, g_pAnimationManager->GetAnimation("여우_달리기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여우_달리기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_01, g_pAnimationManager->GetAnimation("여우_공격"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_02, g_pAnimationManager->GetAnimation("여우_공격"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_01, g_pAnimationManager->GetAnimation("여우_피격01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_02, g_pAnimationManager->GetAnimation("여우_피격02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_01, g_pAnimationManager->GetAnimation("여우_밀려남"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_02, g_pAnimationManager->GetAnimation("여우_밀려남"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SMASH, g_pAnimationManager->GetAnimation("여우_스매시"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SPIN, g_pAnimationManager->GetAnimation("여우_스핀"), 4.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_GROGGY, g_pAnimationManager->GetAnimation("여우_그로기"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWND, g_pAnimationManager->GetAnimation("여우_다운드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWN_TO_STAND, g_pAnimationManager->GetAnimation("여우_다운투스텐드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_COUNTER, g_pAnimationManager->GetAnimation("여우_카운터"), 2.0f);

		pCreateMonster->GetAbilityParamter()->SetPlayerID(2);
		pCreateMonster->GetAbilityParamter()->SetUnitID(cObjectManager::MONSTER_FOX);
		pCreateMonster->OrderFriendly();
	}	break;

	case cObjectManager::MONSTER_BEAR:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->Setup();
		pCreateMonster->SetRadius(0.5f);
		pCreateMonster->SetupAnimationController("사골");
		if (pColor)
		{
			char szText[1024] = {};
			sprintf_s(szText, "곰(%1.2f,%1.2f,%1.2f,%1.2f)", pColor->r, pColor->g, pColor->b, pColor->a);
			pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->CloneSkinnedMesh("곰탕", szText));
			pCreateMonster->ChangeMeshPartColor(cPlayer::MESH_BODY, "mon_bear02.dds", pColor);
		}
		else pCreateMonster->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("곰탕"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY, g_pAnimationManager->GetAnimation("곰_기본01"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE, g_pAnimationManager->GetAnimation("곰_기본02"));
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_FRIENDLY, g_pAnimationManager->GetAnimation("곰_걷기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("곰_걷기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_FRIENDLY, g_pAnimationManager->GetAnimation("곰_달리기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("곰_달리기"), 3.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_01, g_pAnimationManager->GetAnimation("곰_공격01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ATTACK_02, g_pAnimationManager->GetAnimation("곰_공격02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_01, g_pAnimationManager->GetAnimation("곰_피격01"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_HIT_02, g_pAnimationManager->GetAnimation("곰_피격02"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_01, g_pAnimationManager->GetAnimation("곰_밀려남"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_ENDURE_02, g_pAnimationManager->GetAnimation("곰_밀려남"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SMASH, g_pAnimationManager->GetAnimation("곰_스매시"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_SPIN, g_pAnimationManager->GetAnimation("곰_스핀"), 4.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_GROGGY, g_pAnimationManager->GetAnimation("곰_그로기"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWND, g_pAnimationManager->GetAnimation("곰_다운드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_DOWN_TO_STAND, g_pAnimationManager->GetAnimation("곰_다운투스텐드"), 5.0f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_COUNTER, g_pAnimationManager->GetAnimation("곰_카운터"), 2.0f);

		pCreateMonster->GetAbilityParamter()->SetPlayerID(2);
		pCreateMonster->GetAbilityParamter()->SetUnitID(cObjectManager::MONSTER_BEAR);
		pCreateMonster->OrderFriendly();
	}	break;

	default: break;
	}

	if (pCreateMonster)
	{
		pCreateMonster->SetPosition(pPostion);
		m_vecMonster.push_back(pCreateMonster);
	}
	return pCreateMonster;
}

bool cObjectManager::CreateNPC(IN UNIT_TYPE eNPCKey, IN LPD3DXVECTOR3 pPostion)
{
	cPlayer* pCreateNPC = nullptr;
	switch (eNPCKey)
	{
	case cObjectManager::MONSTER_NULL: break;
	}

	return false;
}

void cObjectManager::Destroy(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->SetTarget(nullptr);
		m_pPlayer->Release();
	}
	SAFE_RELEASE(m_pTerrain);
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->SetTarget(nullptr);
		pMonster->GetAbilityParamter()->SetEffective(false);
		pMonster->Release();
	}
	m_vecMonster.clear();
}

