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
	if (szKeyName) m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH, szFolder, szFilename, szKeyName));
	else m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH, szFolder, szFilename, ""));
}

void cDataLoder::RegisterAnimation(LPCSTR szFullPath, LPCSTR szKeyName)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_ANIMATION, szFullPath, szKeyName));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, D3DMATERIAL9* pMaterial)
{

	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, "", nullptr, pMaterial));
}

void cDataLoder::RegisterMeshColor(LPCSTR szMeshName, LPCSTR szTextureName, LPD3DXCOLOR pColor)
{
	D3DMATERIAL9 materal;
	ZeroMemory(&materal, sizeof(D3DMATERIAL9));
	materal.Ambient = materal.Diffuse = materal.Specular = *pColor;
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH_COLOR, szMeshName, szTextureName, "", nullptr, &materal));
}

void cDataLoder::RegisterTerrain(LPCSTR szHighMapKey, LPCSTR szTextureKey, LPCSTR szTerrainKey, D3DMATERIAL9 * pMaterial)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_TERRAIN, szHighMapKey, szTextureKey, szTerrainKey, nullptr, pMaterial));
}

void cDataLoder::RegisterTerrain(LPCSTR szHighMapKey, LPCSTR szTextureKey, LPCSTR szTerrainKey, LPD3DXCOLOR pColor)
{
	D3DMATERIAL9 materal;
	ZeroMemory(&materal, sizeof(D3DMATERIAL9));
	materal.Ambient = materal.Diffuse = materal.Specular = *pColor;
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_TERRAIN, szHighMapKey, szTextureKey, szTerrainKey, nullptr, &materal));
}

void cDataLoder::RegisterSound(LPCSTR szSoundKey, LPCSTR szFilename, bool bBGM, bool bLoop)
{
	int nParam = (bBGM << 1) + bLoop;
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_SOUND, szSoundKey, szFilename, "", nullptr, nullptr, nParam));
}

void cDataLoder::RegisterBuild(LPCSTR szstring1)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_BUILDING, szstring1));


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
			std::string sKey;
			pToken = strtok(nullptr, ";");
			if (pToken[0] != '\n') this->RegisterMesh(sPath.c_str(), sFile.c_str(), pToken);
			else this->RegisterMesh(sPath.c_str(), sFile.c_str(), nullptr);
			//등록
		}
		else if (strstr(pToken, "Color") || strstr(pToken, "색상"))
		{
			std::string sMeshKey = strtok(nullptr, ",");
			std::string sTexture = strtok(nullptr, ",");
			D3DMATERIAL9 stColor = {};
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
			std::string FullPath = strtok(nullptr, ",");
			std::string sAnimationKey = strtok(nullptr, ";");
			this->RegisterAnimation(FullPath.c_str(), sAnimationKey.c_str());
		}
		else if (strstr(pToken, "Field") || strstr(pToken, "맵"))
		{
			std::string sHightMap = strtok(nullptr, ",");
			std::string sTexture = strtok(nullptr, ",");
			std::string sMapKey = strtok(nullptr, ",");

			D3DMATERIAL9 stColor = {};
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
			this->RegisterTerrain(sHightMap.c_str(), sTexture.c_str(), sMapKey.c_str(), &stColor);
			//Field:HighMap,Texture,MapKey, 0.75f, 0.75f, 0.75f, 1.0f;
		}

	}
	fclose(fp);
}

void cDataLoder::LoaderData(void)
{

	if (m_dwCount >= m_vecData.size())
	{
		m_vecData.clear();
		m_dwCount = 0;
	}
	ST_DATA* pData = &m_vecData[m_dwCount];
	switch (pData->dwType)
	{
	case cDataLoder::DATA_NULL: break;

	case cDataLoder::DATA_MESH:
		if (pData->str3.empty()) g_pSkinnedMeshManager->CloneSkinnedMesh(pData->str1, pData->str2);
		else g_pSkinnedMeshManager->RegisterSkinnedMesh(pData->str1, pData->str2, pData->str3);
		break;

	case cDataLoder::DATA_MESH_COLOR:
		if (g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1))
		{
			g_pSkinnedMeshManager->GetSkinnedMesh(pData->str1)->SetTextureColor(pData->str2.c_str(), &pData->material);
		}
		break;

	case cDataLoder::DATA_ANIMATION: g_pAnimationManager->RegisterAnimation(pData->str1.c_str(), pData->str2.c_str()); break;

	case cDataLoder::DATA_TERRAIN: g_pMapTerrain->RegisterMap(pData->str3.c_str(), pData->str1.c_str(), pData->str2.c_str(), &pData->material); break;

	case cDataLoder::DATA_BUILDING: g_pMapObjectManager->RegisterMapObject("", pData->str1.c_str(), pData->str1.c_str()); break;
	
	case cDataLoder::DATA_SOUND: g_pSoundManager->AddSound(pData->str1, pData->str2,pData->nParam&2, pData->nParam&1);

	default: break;
	}
	++m_dwCount;
}

void cDataLoder::LoaderDataLoop(void)
{
	while (1.0f > this->GetLodingGauge())
	{
		DEBUG_TEXT(this->GetLodingGauge());
		this->LoaderData();
	}
}

void cDataLoder::LoadCallBack(THIS_ LPVOID pDataLoder)
{
	cDataLoder* pThis = (cDataLoder*)pDataLoder;
	while (1.0f <= pThis->GetLodingGauge())
	{
		pThis->LoaderData();
	}
}

cDataLoder* cDataLoder::Create(void)
{
	cDataLoder* newClass = new cDataLoder;
	newClass->AddRef();
	return newClass;
}

