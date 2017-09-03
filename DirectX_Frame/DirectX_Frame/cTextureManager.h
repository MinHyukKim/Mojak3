#pragma once

#define g_pTexture cTextureManager::GetInstance()

class cTextureManager
{
private:
	std::map<std::string, D3DXIMAGE_INFO> m_mapImageInfo;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(IN LPCSTR szKeyName);
	LPDIRECT3DTEXTURE9 GetTexture(IN std::string& szKeyName);
	bool GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN LPCSTR szKeyName);
	bool GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN std::string& szKeyName);

	void Destroy(void);

	//½Ì±ÛÅæ »ý¼º
	static cTextureManager* GetInstance() { static cTextureManager instance; return &instance; }
private:
	cTextureManager(void);
	virtual ~cTextureManager(void);
};

