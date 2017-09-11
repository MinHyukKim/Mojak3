#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;
	cSkinnedMeshManager(void);
	~cSkinnedMeshManager(void);

public:
	//½Ì±ÛÅæ »ı¼º
	static cSkinnedMeshManager* GetInstance() { static cSkinnedMeshManager instance; return &instance; }

	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename);
	

	void Destroy();
};