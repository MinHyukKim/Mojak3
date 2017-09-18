#pragma once

struct ST_DATA
{
	DWORD dwType;
	std::string str1;
	std::string str2;
	std::string str3;
	D3DXMATRIXA16 mat1;
	D3DXMATRIXA16 mat2;

	ST_DATA(DWORD _dwType = 0, std::string _str1 = nullptr, std::string _str2 = nullptr, std::string _str3 = nullptr, LPD3DXMATRIX _mat1 = nullptr, LPD3DXMATRIX _mat2 = nullptr)
		: dwType(_dwType), str1(_str1), str2(_str2), str3(_str3), mat1(*_mat1), mat2(*_mat2)
	{

	}
};

class cDataLoder
{
public:
	enum DATA_TYPE
	{
		DATA_NULL,
		DATA_MESH,
		DATA_TEXTURE_COLOR,
		DATA_ANIMATION,
	};
private:
	std::vector<ST_DATA> m_vecData;
public:
	void RegisterMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	void RegisterAnimation(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	void RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXMATRIX pMatrix);



	cDataLoder(void);
	virtual ~cDataLoder(void);
};

