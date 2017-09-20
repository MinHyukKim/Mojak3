#include "stdafx.h"
#include "cDataLoder.h"

cDataLoder::cDataLoder(void)
	:m_dwCount(0)
{
}

cDataLoder::~cDataLoder(void)
{
	m_dwCount = 0;
	m_vecData.clear();
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

	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, "", nullptr, pMaterial));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR color)
{
	D3DMATERIAL9 materal;
	ZeroMemory(&materal, sizeof(D3DMATERIAL9));
	materal.Ambient = materal.Diffuse = materal.Specular = *color;
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, nullptr, nullptr, &materal));
}

bool cDataLoder::RegisterData(LPCSTR FullPath)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FullPath, "r");
	if (!fp) return false;
	while (!feof(fp))
	{
		char szPathData[1024] = {};
		fgets(szPathData, 1024, fp);
		char* pToken = nullptr;
		pToken = strtok(szPathData, ":");

		if (!pToken || strstr(pToken, "//")) continue;
		else if (strstr(pToken, "Mesh") || strstr(pToken, "형상"))
		{
			std::string sPath = strtok(nullptr, ",");
			std::string sFile = strtok(nullptr, ",");
			std::string sKey = strtok(nullptr, ";");
			//등록
			this->RegisterMesh(sPath.c_str(), sFile.c_str(), sKey.c_str());
		}
		else if (strstr(pToken, "Color") || strstr(pToken, "색상"))
		{
			std::string sMeshKey = strtok(nullptr, ",");
			std::string sTexture = strtok(nullptr, ",");
			D3DMATERIAL9 stColor;
			stColor.Diffuse.r = atof(strtok(nullptr, ","));
			stColor.Diffuse.g = atof(strtok(nullptr, ","));
			stColor.Diffuse.b = atof(strtok(nullptr, ","));
			stColor.Diffuse.a = atof(strtok(nullptr, ","));
			pToken = strtok(nullptr, ",");
			if (pToken)
			{
				stColor.Ambient.r = atof(pToken);
				stColor.Ambient.g = atof(strtok(nullptr, ","));
				stColor.Ambient.b = atof(strtok(nullptr, ","));
				stColor.Ambient.a = atof(strtok(nullptr, ","));
				stColor.Specular.r = atof(strtok(nullptr, ","));
				stColor.Specular.g = atof(strtok(nullptr, ","));
				stColor.Specular.b = atof(strtok(nullptr, ","));
				stColor.Specular.a = atof(strtok(nullptr, ","));
			}
			else stColor.Ambient = stColor.Specular = stColor.Diffuse;
			//등록
			this->RegisterMeshColor(sMeshKey.c_str(), sTexture.c_str(), &stColor);
		}
		else if (strstr(pToken, "Animation") || strstr(pToken, "애니"))
		{
			std::string sPath = strtok(nullptr, ",");
			std::string sFile = strtok(nullptr, ",");
			std::string sAnimationKey = strtok(nullptr, ",");
			this->RegisterAnimation(sPath.c_str(), sFile.c_str(), sAnimationKey.c_str());
		}

	}
	fclose(fp);
}

bool cDataLoder::LoaderData(void)
{

	if (m_dwCount >= m_vecData.size())
	{
		m_vecData.clear();
		m_dwCount = 0;
		return false;
	}
	ST_DATA* pData = &m_vecData[m_dwCount];
	switch (pData->dwType)
	{
	case cDataLoder::DATA_NULL: break;

	case cDataLoder::DATA_MESH: g_pSkinnedMeshManager->RegisterSkinnedMesh(pData->str1, pData->str2, pData->str3); break;

	case cDataLoder::DATA_MESH_COLOR:
		if (g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1))
		{
			g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1)->SetTextureColor(pData->str2.c_str(), &pData->material);
		}
		break;

	case cDataLoder::DATA_ANIMATION: g_pAnimationManager->RegisterAnimation(pData->str1.c_str(), pData->str2.c_str()); break;

	default: break;

	}
	++m_dwCount;
	return true;
}

void cDataLoder::LoadCallBack(THIS_ LPVOID pDataLoder)
{
	cDataLoder* pThis = (cDataLoder*)pDataLoder;
	while (pThis->LoaderData());
}

cDataLoder* cDataLoder::Create(void)
{
	cDataLoder* newClass = new cDataLoder;
	newClass->AddRef();
	return newClass;
}

