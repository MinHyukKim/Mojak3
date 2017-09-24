#include "StdAfx.h"
#include "cMapObjectManager.h"
#include "cBuilding.h"

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

void cMapObjectManager::Destroy()
{
	for each(auto it in m_mapBuilding)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}

}
