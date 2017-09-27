#include "StdAfx.h"
#include "cMapObjectManager.h"
#include "cBuilding.h"
#include "cMapTerrain.h"


cMapObjectManager::cMapObjectManager(void)
{
}

cMapObjectManager::~cMapObjectManager(void)
{
}

cBuilding * cMapObjectManager::GetMapObject(char * szFolder, char * szFilename)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapBuilding.find(sFullPath) == m_mapBuilding.end())
	{
		cBuilding* pBuilding = new cBuilding();
		pBuilding->LoadModel(szFolder, szFilename);
		m_mapBuilding[sFullPath] = pBuilding;
	}
	return m_mapBuilding[sFullPath];
}

cBuilding* cMapObjectManager::RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{

	if (m_mapBuilding.find(szKeyName) == m_mapBuilding.end())
	{
		cBuilding* pBuilding = new cBuilding();
		pBuilding->LoadModel((LPSTR)szFolder, (LPSTR)szFilename);
		m_mapBuilding[szKeyName] = pBuilding;
	}
	return m_mapBuilding[szKeyName];
}

cBuilding * cMapObjectManager::RegisterMapObject(std::string & szFolder, std::string & szFilename, std::string & szKeyName)
{
	return this->RegisterMapObject(szFolder.c_str(), szFilename.c_str(), szKeyName.c_str());
}

cBuilding* cMapObjectManager::GetMapObject(LPCSTR szKeyName)
{
	if (m_mapBuilding.find(szKeyName) == m_mapBuilding.end()) return nullptr;

	return m_mapBuilding[szKeyName];
}

cBuilding * cMapObjectManager::GetMapObject(std::string & szKeyName)
{
	return this->GetMapObject(szKeyName.c_str());
}

void cMapObjectManager::AppendBuilding(cBuilding * build)
{
	m_vecBuilding.push_back(build);
}

cBuilding * cMapObjectManager::GetLastMapObject()
{
	if (m_vecBuilding.size() > 0)
	{
		return m_vecBuilding[m_vecBuilding.size() - 1];
	}
	else return nullptr;
}

bool cMapObjectManager::PopMapObject()
{
	DEBUG_TEXT(m_vecBuilding.size());
	if (m_vecBuilding.size() > 0)
	{
		m_vecBuilding.back()->Destroy();
		m_vecBuilding.pop_back();
		return true;
	}
	
	return false;
}

void cMapObjectManager::Update()
{
	if (m_vecBuilding.size() > 0)
	{
		for (int i = 0; i < m_vecBuilding.size(); i++)
		{
			m_vecBuilding[i]->Update();
		}
	}
}

void cMapObjectManager::Update(cMapTerrain * map)
{
	if (m_vecBuilding.size() > 0)
	{
		for (int i = 0; i < m_vecBuilding.size(); i++)
		{
			//건물 바닥 높이 결정
			float test_build_height = m_vecBuilding[i]->GetPosY();
			map->GetHeight(&test_build_height, m_vecBuilding[i]->GetPosX(), m_vecBuilding[i]->GetPosZ());
			m_vecBuilding[i]->SetPosY(test_build_height + m_vecBuilding[i]->GetOffsetY());

			m_vecBuilding[i]->Update();
		}
	}

}

void cMapObjectManager::Render()
{
	if (m_vecBuilding.size() > 0)
	{
		for (int i = 0; i < m_vecBuilding.size(); i++)
		{
			m_vecBuilding[i]->Render();
		}
	}
}

void cMapObjectManager::Destroy()
{
	//for each(auto it in m_mapBuilding)
	//{
	//	it.second->Destroy();
	//	SAFE_DELETE(it.second);
	//}
	for each(auto it in m_vecBuilding)
	{
		it->Destroy();
		SAFE_DELETE(it);
	}
}
