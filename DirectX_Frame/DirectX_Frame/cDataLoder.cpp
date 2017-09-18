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

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXMATRIX pMatrix)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR1, szMeshName, szTextureName, nullptr, pMatrix));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR color)
{
	D3DXMATRIXA16 mat;
	mat._11 = mat._21 = mat._31 = color->r;
	mat._12 = mat._22 = mat._32 = color->g;
	mat._13 = mat._23 = mat._33 = color->b;
}

bool cDataLoder::LoaderData(void)
{
	if (m_dwCount >= m_vecData.size()) return false;
	ST_DATA* pData = &m_vecData[m_dwCount];
	switch (pData->dwType)
	{
	case cDataLoder::DATA_NULL: break;
	case cDataLoder::DATA_MESH: g_pSkinnedMeshManager->RegisterSkinnedMesh(pData->str1, pData->str2, pData->str3); break;
	case cDataLoder::DATA_MESH_COLOR1: g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1)->SetTextureColor(pData->str2.c_str(), &pData->mat1); break;
	case cDataLoder::DATA_MESH_COLOR2: break;
	case cDataLoder::DATA_ANIMATION: break;
	default: break;
	}
	return true;
}

