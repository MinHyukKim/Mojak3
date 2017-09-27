#include "StdAfx.h"
#include "cSkinnedMeshManager.h"
#include "cSkinnedMesh.h"

cSkinnedMeshManager::cSkinnedMeshManager(void)
{
}

cSkinnedMeshManager::~cSkinnedMeshManager(void)
{
}


cSkinnedMesh * cSkinnedMeshManager::GetSkinnedMesh(char * szFolder, char * szFilename)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFilename);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}
	return m_mapSkinnedMesh[sFullPath];
}

cSkinnedMesh* cSkinnedMeshManager::CloneSkinnedMesh(LPCSTR szOriginKey, LPCSTR szCloneKey)
{
	if (m_mapCloneMesh.find(szCloneKey) == m_mapCloneMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh(this->GetSkinnedMesh(szOriginKey));
		m_mapCloneMesh[szCloneKey] = pSkinnedMesh;
	}
	return m_mapCloneMesh[szCloneKey];
}

cSkinnedMesh* cSkinnedMeshManager::CloneSkinnedMesh(std::string & sOriginKey, std::string & sCloneKey)
{
	return this->CloneSkinnedMesh(sOriginKey.c_str(), sCloneKey.c_str());
}

cSkinnedMesh* cSkinnedMeshManager::RegisterSkinnedMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{

	if (m_mapSkinnedMesh.find(szKeyName) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load((LPSTR)szFolder, (LPSTR)szFilename);
		m_mapSkinnedMesh[szKeyName] = pSkinnedMesh;
	}
	return m_mapSkinnedMesh[szKeyName];
}

cSkinnedMesh * cSkinnedMeshManager::RegisterSkinnedMesh(std::string & szFolder, std::string & szFilename, std::string & szKeyName)
{
	return this->RegisterSkinnedMesh(szFolder.c_str(), szFilename.c_str(), szKeyName.c_str());
}

cSkinnedMesh* cSkinnedMeshManager::GetSkinnedMesh(LPCSTR szKeyName)
{
	if (m_mapSkinnedMesh.find(szKeyName) == m_mapSkinnedMesh.end())
	{
		if (m_mapCloneMesh.find(szKeyName) == m_mapCloneMesh.end()) return nullptr;
		else return m_mapCloneMesh[szKeyName];
	}

	return m_mapSkinnedMesh[szKeyName];
}

cSkinnedMesh * cSkinnedMeshManager::GetSkinnedMesh(std::string & szKeyName)
{
	return this->GetSkinnedMesh(szKeyName.c_str());
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}
	for each(auto it in m_mapCloneMesh)
	{
		SAFE_DELETE(it.second);
	}

}
