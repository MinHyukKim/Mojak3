#include "stdafx.h"
#include "cAnimationManager.h"

cAnimationManager::cAnimationManager(void)
{
}

cAnimationManager::~cAnimationManager(void)
{
}

LPD3DXANIMATIONSET cAnimationManager::RegisterAnimation(LPCSTR szFullPath, LPCSTR szKeyName)
{
	//애니메이션을 찾지 못했을경우
	if (m_mapAnimationSet.find(szKeyName) == m_mapAnimationSet.end())
	{
		//애니메이션 읽기
		LPD3DXANIMATIONSET pAnimationSet = nullptr;
		g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, szFullPath);
		if (pAnimationSet) m_mapAnimationSet[szKeyName] = pAnimationSet;
		else return nullptr;
	}
	//애니메이션 반환
	return m_mapAnimationSet[szKeyName];
}

LPD3DXANIMATIONSET cAnimationManager::GetAnimation(LPCSTR szKeyName)
{
	//애니메이션을 찾지 못했을경우
	if (m_mapAnimationSet.find(szKeyName) == m_mapAnimationSet.end()) return nullptr;
	//애니메이션 반환
	return m_mapAnimationSet[szKeyName];
}

LPD3DXANIMATIONSET cAnimationManager::GetAnimation(std::string & sKeyName)
{
	return GetAnimation(sKeyName.c_str());
}

void cAnimationManager::Destroy(void)
{
	for each (auto it in m_mapAnimationSet) SAFE_RELEASE(it.second);
}
