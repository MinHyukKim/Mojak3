#include "stdafx.h"
#include "cObjectManager.h"

#include "cPlayer.h"
#include "cMapTerrain.h"

cObjectManager::cObjectManager(void)
	: m_pPlayer(nullptr)
	, m_pTerrain(nullptr)
	, m_nMonsterCursor(UNIT_TYPE::MONSTER_NULL+1)
{
}

cObjectManager::~cObjectManager(void)
{
}

void cObjectManager::Update(void)
{
	SAFE_UPDATE(m_pTerrain);
	SAFE_UPDATE(m_pPlayer);
	//높이 세팅하는 부분 함수로 뺌.
	m_pPlayer->SetPosY(GetMapHeight(m_pPlayer));
	
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Update();
		pMonster->SetPosY(GetMapHeight(pMonster));
	}
	//NPC
	for each (auto pNPC in m_vecNPC)
	{
		pNPC->Update();
		pNPC->SetPosY(GetMapHeight(pNPC));
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

void cObjectManager::SelectUpdate(cMapTerrain* map)
{
	if (!m_pSelectMonster) return;
	D3DXVECTOR3 vPos, vOrg, vDir;
	g_pRay->RayAtWorldSpace(&vOrg, &vDir);
	map->IsCollision(&vPos, &vOrg, &vDir);
	m_pSelectMonster->SetPosition(&vPos);
}

void cObjectManager::Render(void)
{
	SAFE_RENDER(m_pPlayer);
	SAFE_RENDER(m_pTerrain);
	monsterRender();
}
void cObjectManager::monsterRender(void)
{
	SAFE_RENDER(m_pSelectMonster);
	for each (auto pMonster in m_vecMonster)
	{
		pMonster->Render();
	}
	for each (auto pNPC in m_vecNPC)
	{
		pNPC->Render();
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
	m_pPlayer->GetAbilityParamter()->SetPower(2.25f);
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

bool cObjectManager::GetNPC(OUT cPlayer ** ppNPC, IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir)
{
	cPlayer* pTarget = nullptr;
	float fDist = 1000.0f;

	for each (auto pNPC in m_vecNPC)
	{
		if (!pNPC->IsCollision(pRay, pDir)) continue;
		float fLength = D3DXVec3Length(&(pNPC->GetPosition() - (*pRay)));
		if (fLength >= fDist) continue;
		pTarget = pNPC;
		fDist = fLength;
	}
	*ppNPC = pTarget;
	return pTarget;
}


float cObjectManager::GetMapHeight(cPlayer* player)
{
	float fHeight = player->GetPosY();
	if (m_pTerrain)
	{
		m_pTerrain->GetHeight(&fHeight, player->GetPosX(), player->GetPosZ());
	}
	return fHeight;
}

void cObjectManager::SetCursorIncrease()
{
	//백터 내에 몹이 없으면 카운터를 올려줄 필요가 없다.
	if (m_vecMonster.size() < 1 && m_pSelectMonster == nullptr) return;
	m_nMonsterCursor++;
	if (m_nMonsterCursor == UNIT_TYPE::MONSTER_END)
		m_nMonsterCursor = UNIT_TYPE::MONSTER_NULL + 1;
}

cPlayer * cObjectManager::GetMonsterRotation()
{
	D3DXVECTOR3 vPos, vOrg, vDir;
	g_pRay->RayAtWorldSpace(&vOrg, &vDir);
	m_pTerrain->IsCollision(&vPos, &vOrg, &vDir);

	CreateMonster((UNIT_TYPE)m_nMonsterCursor, &vPos);
	SAFE_RELEASE(m_pSelectMonster);
	m_pSelectMonster = m_vecMonster.back();
	m_vecMonster.pop_back();

	return m_pSelectMonster;
}

void cObjectManager::ResetMobSelect(void)
{
	SAFE_RELEASE(m_pSelectMonster);
	m_pSelectMonster = nullptr;
}

void cObjectManager::SetupMonster()
{
	if (this->GetSelectObject() == NULL) return;
	m_vecMonster.push_back(m_pSelectMonster);

	D3DXVECTOR3 vPos, vOrg, vDir;
	g_pRay->RayAtWorldSpace(&vOrg, &vDir);
	m_pTerrain->IsCollision(&vPos, &vOrg, &vDir);
	
	int dice = g_pMath->GetFromIntTo(0, 1);
	if (dice == 0)
	{
		CreateMonster((UNIT_TYPE)m_nMonsterCursor, &vPos);
		
	}
	else
	{
		CreateMonster((UNIT_TYPE)m_nMonsterCursor, &vPos, &D3DXCOLOR(0.6f, 0.2f, 0.2f, 1.0f));
	}
	m_pSelectMonster = m_vecMonster.back();
	m_vecMonster.pop_back();
}

bool cObjectManager::SaveMonsterObjectState(const char * filename)
{
	//저장할 빌딩이 없으면 리턴
	if (m_vecMonster.size() < 1) return false;
	FILE *fp;
	fp = fopen(filename, "w");
	for each(auto v in m_vecMonster)
	{
		//오브젝트 타입 추가예정.
		//위치 저장
		D3DXVECTOR3 vPos = v->GetPosition();
		//오브젝트 타입
		DWORD unitID = v->GetAbilityParamter()->GetUnitID();
		fprintf(fp, "%ld\n", unitID);
		//오브젝트 컬러
		LPD3DXCOLOR color = v->GetMeshColor();
		//컬러값이 있으면 넣고 없으면 문자열 null을 넣음
		if (color != nullptr)
		{
			fprintf(fp, "%f %f %f %f\n", color->a, color->r, color->g, color->b);
		}
		else
		{
			fprintf(fp, "null\n");
		}
		fprintf(fp, "%f %f %f\n", vPos.x, vPos.y, vPos.z);
	}
	fclose(fp);
	return true;
}

bool cObjectManager::LoadMonsterObjectState(const char * filename)
{
	//현재 존재하는 오브젝트들 청소
	ResetMobSelect();
	for each(auto p in m_vecMonster)
	{
		SAFE_RELEASE(p);
	}
	m_vecMonster.clear();
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) return false;

	while (!feof(fp))
	{
		//오브젝트 타입
		DWORD unitID;
		//위치 저장
		D3DXVECTOR3 vPos;
		//오브젝트 컬러
		D3DXCOLOR color;
		int r = fscanf(fp, "%ld\n", &unitID);
		bool result;
		result = fscanf(fp, "%f %f %f %f\n", &color.a, &color.r, &color.g, &color.b);
		//result값이 null이라면 파싱이 제대로 안됐다=컬러값이 없다는 의미임으로 한줄 스킵해줌.
		if (!result)
		{
			char cTemp[255];
			fgets(cTemp, 255, fp);
		}
		fscanf(fp, "%f %f %f\n", &vPos.x, &vPos.y, &vPos.z);
		//컬러값이 없으면 컬러값을 넣어주지 않음.
		if (!result)
		{
			CreateMonster((UNIT_TYPE)unitID, &vPos);
		}
		else
		{
			CreateMonster((UNIT_TYPE)unitID, &vPos, &color);
		}
	}
	fclose(fp);



	return true;
}

void cObjectManager::SetTerrain(IN cMapTerrain* pTerrain)
{
	SAFE_RELEASE(m_pTerrain);
	m_pTerrain = pTerrain;
	m_pTerrain->AddRef();
}

cPlayer* cObjectManager::CreateMonster(IN UNIT_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion, IN LPD3DXCOLOR pColor)
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
		pCreateMonster->GetAbilityParamter()->SetPower(2.25f);
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
		pCreateMonster->GetAbilityParamter()->SetUnitID(eMonsterKey);
		pCreateMonster->OrderFriendly();
	}	break;

	case cObjectManager::MONSTER_FOX:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->Setup();
		pCreateMonster->SetRadius(0.3f);
		pCreateMonster->GetAbilityParamter()->SetPower(3.0f);
		pCreateMonster->SetupAnimationController("여우00");
		pCreateMonster->GetAbilityParamter()->SetMoveSpeed(1.5f);
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
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_FRIENDLY, g_pAnimationManager->GetAnimation("여우_걷기"), 1.5f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE, g_pAnimationManager->GetAnimation("여우_걷기"), 1.5f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_FRIENDLY, g_pAnimationManager->GetAnimation("여우_달리기"), 1.5f);
		pCreateMonster->RegisterAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE, g_pAnimationManager->GetAnimation("여우_달리기"), 1.5f);
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
		pCreateMonster->GetAbilityParamter()->SetUnitID(eMonsterKey);
		pCreateMonster->OrderFriendly();
	}	break;

	case cObjectManager::MONSTER_BEAR:
	{
		pCreateMonster = cPlayer::Create();
		pCreateMonster->Setup();
		pCreateMonster->SetRadius(0.5f);
		pCreateMonster->GetAbilityParamter()->SetPower(2.45f);
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
		pCreateMonster->GetAbilityParamter()->SetUnitID(eMonsterKey);
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
		case cObjectManager::NPC_NAO:
		{
			pCreateNPC = cPlayer::Create();
			pCreateNPC->Setup();
			pCreateNPC->SetupAnimationController("나오더미");
			pCreateNPC->ChangeMeshPart(cPlayer::MESH_SHOES, g_pSkinnedMeshManager->GetSkinnedMesh("나오스타킹"));
			pCreateNPC->ChangeMeshPart(cPlayer::MESH_BODY, g_pSkinnedMeshManager->GetSkinnedMesh("나오메시"));
			pCreateNPC->RegisterAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY, g_pAnimationManager->GetAnimation("나오_기본01"));

			pCreateNPC->GetAbilityParamter()->SetPlayerID(3);
			pCreateNPC->GetAbilityParamter()->SetUnitID(cObjectManager::NPC_NAO);
			pCreateNPC->OrderFriendly();
		}
	}

	if (pCreateNPC)
	{
		pCreateNPC->SetPosition(pPostion);
		m_vecNPC.push_back(pCreateNPC);
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
	//NPC
	for each(auto pNPC in m_vecNPC)
	{
		pNPC->SetTarget(nullptr);
		pNPC->GetAbilityParamter()->SetEffective(false);
		pNPC->Release();
	}
	SAFE_RELEASE(m_pSelectMonster);
	m_vecMonster.clear();
	m_vecNPC.clear();
}

