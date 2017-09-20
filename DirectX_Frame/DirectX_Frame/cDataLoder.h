#pragma once

struct ST_DATA
{
	DWORD dwType;
	std::string str1;
	std::string str2;
	std::string str3;
	D3DXMATRIXA16 mat1;
	D3DMATERIAL9 material;

	ST_DATA(DWORD _dwType = 0, std::string _str1 = "", std::string _str2 = "", std::string _str3 = "", LPD3DXMATRIX _mat1 = nullptr, D3DMATERIAL9* _material = nullptr)
		: dwType(_dwType), str1(_str1), str2(_str2), str3(_str3)
	{
		if (_mat1) mat1 = *_mat1;
		if (_material) material = *_material;
	}
};

class cDataLoder : public cObject
{
public:
	enum DATA_TYPE
	{
		DATA_NULL,
		DATA_MESH,
		DATA_MESH_COLOR,
		DATA_ANIMATION,
	};
private:
	std::vector<ST_DATA> m_vecData;
	DWORD m_dwCount;

public:
	void RegisterMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	void RegisterAnimation(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	void RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, D3DMATERIAL9* pMaterial);
	void RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR color);

	bool RegisterData(LPCSTR FullPath);
	bool LoaderData(void);
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