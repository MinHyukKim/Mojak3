#pragma once

class cDataLoder : public cObject
{
public:
	enum DATA_TYPE
	{
		DATA_NULL,
		DATA_MESH,
		DATA_MESH_COLOR,
		DATA_ANIMATION,
		DATA_BUILDING,
		DATA_TERRAIN,
	};
private:
	std::vector<ST_DATA> m_vecData;
	DWORD m_dwCount;

public:
	void RegisterMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	void RegisterAnimation(LPCSTR szFullPath, LPCSTR szKeyName);
	void RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, D3DMATERIAL9* pMaterial);
	void RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR pColor);
	void RegisterTerrain(LPCSTR szHighMapKey, LPCSTR szTextureKey, LPCSTR szTerrainKey, D3DMATERIAL9* pMaterial);
	void RegisterTerrain(LPCSTR szHighMapKey, LPCSTR szTextureKey, LPCSTR szTerrainKey, LPD3DXCOLOR pColor);
	void RegisterBuild(LPCSTR szstring1);

	bool RegisterData(LPCSTR FullPath);

	void LoaderData(void);
	void LoaderDataLoop(void);
	float GetLodingGauge(void) { if (m_vecData.empty()) return 1.0f; return (float)m_dwCount / (float)m_vecData.size(); }

	static void LoadCallBack(THIS_ LPVOID pDataLoder);
	static cDataLoder* Create(void);
protected:
	cDataLoder(void);
	virtual ~cDataLoder(void);
};

// 사용법 ()
// 메시를 메시매니저에 등록시킵니다. 키를 사용하여 가져올수 있습니다.
//Mesh:경로,파일,키;
// 메시의 텍스쳐 색상을 설정합니다. 메시가 미리 등록되어 있어야 사용가능합니다.
//Color:메시키,텍스쳐, 1.0f, 1.0f, 1.0f, 0.5f;
//Color:메시키,텍스쳐, 1.0f, 1.0f, 1.0f, 0.5f, 0.2f,
//애니메이션셋을 애니메이션매니저에 등록시킵니다. 키를 사용하여 가져올수 있습니다.
//Animation : 경로,파일,키;