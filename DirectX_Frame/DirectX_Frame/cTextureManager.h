#pragma once

#define g_pTexture cTextureManager::GetInstance()

struct ST_HEIGHT_MAP
{
	LPBYTE pBytes;
	DWORD dwSize;
	DWORD dwByte;
};

class cTextureManager
{
private:
	std::map<std::string, D3DXIMAGE_INFO> m_mapImageInfo;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, ST_HEIGHT_MAP> m_mapHeightMap;

public:
	LPDIRECT3DTEXTURE9 GetTexture(IN LPCSTR szKeyName);
	LPDIRECT3DTEXTURE9 GetTexture(IN std::string& sKeyName);
	LPDIRECT3DTEXTURE9 GetTextureEx(const char* szFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTextureEx(const std::string& sFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	ST_HEIGHT_MAP* GetHeightMap(IN LPCSTR szKeyName, IN DWORD dwBytes = 1);
	ST_HEIGHT_MAP* GetHeightMap(IN std::string& sKeyName, IN DWORD dwBytes = 1);
	bool GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN LPCSTR szKeyName);
	bool GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN std::string& sKeyName);


	void Destroy(void);

	//½Ì±ÛÅæ »ý¼º
	static cTextureManager* GetInstance() { static cTextureManager instance; return &instance; }
private:
	cTextureManager(void);
	virtual ~cTextureManager(void);
};

