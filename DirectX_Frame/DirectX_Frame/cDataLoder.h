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

// ���� ()
// �޽ø� �޽øŴ����� ��Ͻ�ŵ�ϴ�. Ű�� ����Ͽ� �����ü� �ֽ��ϴ�.
//Mesh:���,����,Ű;
// �޽��� �ؽ��� ������ �����մϴ�. �޽ð� �̸� ��ϵǾ� �־�� ��밡���մϴ�.
//Color:�޽�Ű,�ؽ���, 1.0f, 1.0f, 1.0f, 0.5f;
//Color:�޽�Ű,�ؽ���, 1.0f, 1.0f, 1.0f, 0.5f, 0.2f,
//�ִϸ��̼Ǽ��� �ִϸ��̼ǸŴ����� ��Ͻ�ŵ�ϴ�. Ű�� ����Ͽ� �����ü� �ֽ��ϴ�.
//Animation : ���,����,Ű;