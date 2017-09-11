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
	sFullPath += std::string


	return nullptr;
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}

}
