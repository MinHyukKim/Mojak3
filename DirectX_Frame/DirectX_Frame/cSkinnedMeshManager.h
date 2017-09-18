#pragma once
#include "cSkinnedMesh.h"

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

//class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;
	cSkinnedMeshManager(void);
	~cSkinnedMeshManager(void);

public:
	//½Ì±ÛÅæ »ý¼º
	static cSkinnedMeshManager* GetInstance() { static cSkinnedMeshManager instance; return &instance; }

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename);
	cSkinnedMesh* RegisterSkinnedMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cSkinnedMesh* RegisterSkinnedMesh(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cSkinnedMesh* GetSkinnedMesh(LPCSTR szKeyName);
	cSkinnedMesh* GetSkinnedMesh(std::string& szKeyName);
	

	void Destroy();
};