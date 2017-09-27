#include "stdafx.h"
#include "cMapManager.h"
#include "cMapTerrain.h"

cMapManager::cMapManager(void)
{
}

cMapManager::~cMapManager(void)
{
}

cMapTerrain* cMapManager::RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN LPD3DXMATERIAL pMaterial, IN LPD3DXVECTOR3 pScale)
{
	if (m_mapTerrain.find(szKeyName) == m_mapTerrain.end())
	{
		cMapTerrain* pTerrain = cMapTerrain::Create();
		pTerrain->Setup(szHeightMapName, pMaterial, pScale);
		m_mapTerrain[szKeyName] = pTerrain;
	}

	return m_mapTerrain[szKeyName];
}

cMapTerrain* cMapManager::RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN LPCSTR szTextureKey, IN LPD3DXCOLOR pColor, IN LPD3DXVECTOR3 pScale)
{
	D3DXMATERIAL stMaterial;
	SetMatrial(&stMaterial.MatD3D, *pColor);
	stMaterial.pTextureFilename = (LPSTR)szTextureKey;
	return this->RegisterMap(szKeyName, szHeightMapName, &stMaterial, pScale);
}

cMapTerrain* cMapManager::RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN LPCSTR szTextureKey, IN D3DMATERIAL9* pColor, IN LPD3DXVECTOR3 pScale)
{
	D3DXMATERIAL stMaterial;
	stMaterial.MatD3D =  *pColor;
	stMaterial.pTextureFilename = (LPSTR)szTextureKey;
	return this->RegisterMap(szKeyName, szHeightMapName, &stMaterial, pScale);
}

cMapTerrain* cMapManager::GetMapTerrain(IN LPCSTR szKeyName)
{
	if (m_mapTerrain.find(szKeyName) == m_mapTerrain.end()) return nullptr;
	return m_mapTerrain[szKeyName];
}

void cMapManager::Destroy(void)
{
	for each (auto it in m_mapTerrain)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTerrain.clear();
}
