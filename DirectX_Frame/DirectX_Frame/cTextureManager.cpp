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

LPDIRECT3DTEXTURE9 cTextureManager::GetHeightMap(IN LPCSTR szKeyName)
{
	if (m_mapTexture.find(szKeyName) == m_mapTexture.end())
	{
		D3DXIMAGE_INFO ImageInfo = {};
		LPDIRECT3DTEXTURE9 pTexture = NULL;

		if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szKeyName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
			0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &ImageInfo, NULL, &pTexture))) return NULL;
		m_mapImageInfo[szKeyName] = ImageInfo;
		m_mapTexture[szKeyName] = pTexture;
	}

	return m_mapTexture[szKeyName];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetHeightMap(IN std::string & sKeyName)
{
	return this->GetHeightMap(sKeyName.c_str());
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
}
