#include "StdAfx.h"
#include "cMapObjectManager.h"
#include "cBuilding.h"
#include "cMapTerrain.h"


cMapObjectManager::cMapObjectManager(void)
	:cur(0)
{
	m_pMapObjects = new cMapObjectRail();
	m_iMapBuilding = m_mapBuilding.begin();
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

bool cMapObjectManager::AppendBuilding(cBuilding * build)
{
	if (build == NULL) return false;
	m_pMapObjects->AppendBuilding(build);

	return true;
}

bool cMapObjectManager::AppendBuilding(std::string & szKeyName)
{
	return this->AppendBuilding(szKeyName.c_str());
}

bool cMapObjectManager::AppendBuilding(LPCSTR szKeyName)
{
	if (m_mapBuilding.find(szKeyName) == m_mapBuilding.end()) return false;
	cBuilding* temp = new cBuilding;
	temp->LoadModel(szKeyName);
	m_pMapObjects->AppendBuilding(temp);
	return true;
}

cBuilding * cMapObjectManager::getMapObjectRotation()
{
	m_iMapBuilding = m_mapBuilding.begin();
	for (int i = 0; i < cur; i++) m_iMapBuilding++;
	if (m_iMapBuilding == m_mapBuilding.end())
	{
		m_iMapBuilding = m_mapBuilding.begin();
		cur = 0;
	}

	cBuilding* temp = new cBuilding;
	temp->AddRef();
	temp->LoadModel(m_iMapBuilding->first.c_str());


	cur++;
	return temp;
	//cBuilding* temp = (*m_iMapBuilding).first
}

cBuilding * cMapObjectManager::GetLastMapObject()
{
	return m_pMapObjects->GetLastMapObject();
}

bool cMapObjectManager::PopMapObject()
{
	m_pMapObjects->PopMapObject();
	return true;
}

void cMapObjectManager::Update()
{
	//if (m_vecBuilding.size() > 0)
	//{
	//	for (int i = 0; i < m_vecBuilding.size(); i++)
	//	{
	//		m_vecBuilding[i]->Update();
	//	}
	//}
}

void cMapObjectManager::Update(cMapTerrain * map)
{
	m_pMapObjects->Update(map);
}

void cMapObjectManager::Render()
{
	m_pMapObjects->Render();
}

void cMapObjectManager::Destroy()
{
	for each(auto it in m_mapBuilding)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}

	m_pMapObjects->Destroy();
}

void cMapObjectRail::Update(cMapTerrain * map)
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

void cMapObjectRail::Render()
{
	if (m_vecBuilding.size() > 0)
	{
		for (int i = 0; i < m_vecBuilding.size(); i++)
		{
			SAFE_RENDER(m_vecBuilding[i]);
		}
	}
}

cMapObjectRail::cMapObjectRail(void)
{
}

cMapObjectRail::~cMapObjectRail(void)
{
}

void cMapObjectRail::AppendBuilding(cBuilding * build)
{
	m_vecBuilding.push_back(build);
}

cBuilding * cMapObjectRail::GetLastMapObject()
{
	if (m_vecBuilding.size() > 0)
	{
		return m_vecBuilding[m_vecBuilding.size() - 1];
	}
	else return nullptr;
}

bool cMapObjectRail::PopMapObject()
{
	DEBUG_TEXT(m_vecBuilding.size());
	if (m_vecBuilding.size() > 0)
	{
		//m_vecBuilding.back()->Destroy();
		m_vecBuilding.pop_back();
		return true;
	}

	return false;
}

void cMapObjectRail::Destroy()
{
	for each(auto it in m_vecBuilding)
	{
		it->Destroy();
		SAFE_DELETE(it);
	}
}
