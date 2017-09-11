#pragma once

#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;

public:
	//�̱��� ����
	static cSkinnedMeshManager* GetInstance() { static cSkinnedMeshManager instance; return &instance; }

//	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename);

	//void Destroy();

private:
	cSkinnedMeshManager(void);
	virtual ~cSkinnedMeshManager(void);
};