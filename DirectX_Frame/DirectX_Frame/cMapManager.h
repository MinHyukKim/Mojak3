#pragma once

#define g_pMapTerrain cMapManager::GetInstance()

class cMapTerrain;
class cMapManager
{
private:
	std::map<std::string, cMapTerrain*> m_mapTerrain;
	
public:
	cMapTerrain* RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN LPD3DXMATERIAL pMaterial, IN LPD3DXVECTOR3 pScale = &D3DXVECTOR3(1.0f, 16.0f, 1.0f));
	cMapTerrain* RegisterMap(IN LPCSTR szKeyName, IN LPCSTR szHeightMapName, IN LPCSTR szTextureKey, IN LPD3DXCOLOR pColor, IN LPD3DXVECTOR3 pScale = &D3DXVECTOR3(1.0f, 16.0f, 1.0f));
	cMapTerrain* GetMapTerrain(IN LPCSTR szKeyName);

	void Destroy(void);

	static cMapManager* GetInstance(void) { static cMapManager instance; return &instance; }
private:
	cMapManager(void);
	virtual ~cMapManager(void);
};

