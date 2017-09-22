#include "stdafx.h"
#include "cMapManager.h"

cMapManager::cMapManager(void)
{
}

cMapManager::~cMapManager(void)
{
}

cMapTerrain* cMapManager::RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN D3DXMATERIAL* pMaterial, IN LPD3DXVECTOR3 pScale)
{
	if (m_mapTerrain.find(szKeyName) == m_mapTerrain.end())
	{
		cMapTerrain* pTerrain = cMapTerrain::Create();
		pTerrain->Setup(szHeightMapName, pMaterial, pScale);
		m_mapTerrain[szKeyName] = pTerrain;
	}

	return m_mapTerrain[szKeyName];
}

cMapTerrain* cMapManager::GetMapTerrain(IN LPCSTR szKeyName)
{
	if (m_mapTerrain.find(szKeyName) == m_mapTerrain.end()) return nullptr;
	return m_mapTerrain[szKeyName];
}
