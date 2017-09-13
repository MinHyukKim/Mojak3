#include "stdafx.h"
#include "cTextureManager.h"

cTextureManager::cTextureManager(void)
{
}

cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(IN LPCSTR szKeyName)
{
	if (m_mapTexture.find(szKeyName) == m_mapTexture.end())
	{
		D3DXIMAGE_INFO ImageInfo = {};
		LPDIRECT3DTEXTURE9 pTexture = NULL;

		if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szKeyName, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
			0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &ImageInfo, NULL, &pTexture))) return NULL;

		m_mapImageInfo[szKeyName] = ImageInfo;
		m_mapTexture[szKeyName] = pTexture;
	}

	return m_mapTexture[szKeyName];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(IN std::string& sKeyName)
{
	return this->GetTexture(sKeyName.c_str());
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTextureEx(const char * szFullPath, OUT D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]);
	}
	else if (m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		assert(true && "이전에 로드된적 있습니다");
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[szFullPath];
	}

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTextureEx(const string & sFullPath, OUT D3DXIMAGE_INFO * pImageInfo)
{
	return GetTextureEx(sFullPath.c_str(), pImageInfo);
}

ST_HEIGHT_MAP* cTextureManager::GetHeightMap(IN LPCSTR szKeyName, IN DWORD dwBytes)
{
	if (m_mapHeightMap.find(szKeyName) == m_mapHeightMap.end())
	{
		ST_HEIGHT_MAP pHeightMap = {};
		pHeightMap.dwByte = dwBytes;

		FILE* fp = nullptr;
		fopen_s(&fp, szKeyName, "rb");
		if (!fp) return NULL;
		fseek(fp, 0, SEEK_END);
		pHeightMap.dwSize = ftell(fp);

		pHeightMap.pBytes = new BYTE[pHeightMap.dwSize];
		fseek(fp, 0, SEEK_SET);
		for (DWORD i = 0; i < pHeightMap.dwSize; i++)
		{
			pHeightMap.pBytes[i] = fgetc(fp);
		}

		fclose(fp);
		m_mapHeightMap[szKeyName] = pHeightMap;
	}

	return &m_mapHeightMap[szKeyName];
}

ST_HEIGHT_MAP* cTextureManager::GetHeightMap(IN std::string & sKeyName, IN DWORD dwBytes)
{
	return this->GetHeightMap(sKeyName.c_str(), dwBytes);
}

bool cTextureManager::GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN LPCSTR szKeyName)
{
	if (m_mapTexture.find(szKeyName) == m_mapTexture.end())
	{
		D3DXIMAGE_INFO ImageInfo = {};
		LPDIRECT3DTEXTURE9 pTexture = NULL;

		if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szKeyName, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
			0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &ImageInfo, NULL, &pTexture))) return false;

		m_mapImageInfo[szKeyName] = ImageInfo;
		m_mapTexture[szKeyName] = pTexture;
	}

	(*pImageInfo) = m_mapImageInfo[szKeyName];
	return true;
}

bool cTextureManager::GetImageInfo(OUT D3DXIMAGE_INFO* pImageInfo, IN std::string& sKeyName)
{
	return this->GetImageInfo(pImageInfo, sKeyName.c_str());
}

void cTextureManager::Destroy(void)
{
	for each(auto it in m_mapTexture) SAFE_RELEASE(it.second);
	m_mapTexture.clear();

	for each(auto it in m_mapHeightMap) SAFE_DELETE_ARRAY(it.second.pBytes);
	m_mapHeightMap.clear();
}
