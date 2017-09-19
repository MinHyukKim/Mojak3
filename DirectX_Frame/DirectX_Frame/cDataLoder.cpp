#include "stdafx.h"
#include "cDataLoder.h"

cDataLoder::cDataLoder(void)
	:m_dwCount(0)
{
}

cDataLoder::~cDataLoder(void)
{
}

void cDataLoder::RegisterMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH, szFolder, szFilename, szKeyName));
}

void cDataLoder::RegisterAnimation(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_ANIMATION, szFolder, szFilename, szKeyName));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, D3DMATERIAL9* pMaterial)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, nullptr, nullptr, pMaterial));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR color)
{
	D3DMATERIAL9 materal;
	ZeroMemory(&materal, sizeof(D3DMATERIAL9));
	materal.Ambient = materal.Diffuse = materal.Specular = *color;
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, nullptr, nullptr, &materal));
}

bool cDataLoder::LoaderData(void)
{
	if (m_dwCount >= m_vecData.size()) return false;
	ST_DATA* pData = &m_vecData[m_dwCount];
	switch (pData->dwType)
	{
	case cDataLoder::DATA_NULL: break;
	case cDataLoder::DATA_MESH: g_pSkinnedMeshManager->RegisterSkinnedMesh(pData->str1, pData->str2, pData->str3); break;
	case cDataLoder::DATA_MESH_COLOR: g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1)->SetTextureColor(pData->str2.c_str(), &pData->material); break;
	case cDataLoder::DATA_ANIMATION: g_pAnimationManager->RegisterAnimation(pData->str1.c_str(), pData->str2.c_str()); break;
	default: break;
	}
	return true;
}

