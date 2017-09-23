#pragma once
#include "cMapTerrain.h"

#define g_pMapTerrain cMapManager::GetInstance()

class cMapTerrain;
class cMapManager
{
private:
	std::map<std::string, cMapTerrain*> m_mapTerrain;
	
public:
	cMapTerrain* RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN D3DXMATERIAL* pMaterial, IN LPD3DXVECTOR3 pScale = &D3DXVECTOR3(1.0f, 16.0f, 1.0f));
	cMapTerrain* GetMapTerrain(IN LPCSTR szKeyName);

	static cMapManager* GetInstance(void) { static cMapManager instance; return &instance; }
private:
	cMapManager(void);
	virtual ~cMapManager(void);
};

