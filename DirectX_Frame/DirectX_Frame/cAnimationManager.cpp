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
	//�ִϸ��̼��� ã�� ���������
	if (m_mapAnimationSet.find(szKeyName) == m_mapAnimationSet.end())
	{
		//�ִϸ��̼� �б�
		LPD3DXANIMATIONSET pAnimationSet = nullptr;
		g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, szFullPath);
		if (pAnimationSet) m_mapAnimationSet[szKeyName] = pAnimationSet;
		else return nullptr;
	}
	//�ִϸ��̼� ��ȯ
	return m_mapAnimationSet[szKeyName];
}

LPD3DXANIMATIONSET cAnimationManager::GetAnimation(LPCSTR szKeyName)
{
	//�ִϸ��̼��� ã�� ���������
	if (m_mapAnimationSet.find(szKeyName) == m_mapAnimationSet.end()) return nullptr;
	//�ִϸ��̼� ��ȯ
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
