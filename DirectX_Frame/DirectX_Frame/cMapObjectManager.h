#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()


class cMapTerrain;

class cMapObjectManager
{
private:
	std::map<std::string, cBuilding*> m_mapBuilding;
	std::vector<cBuilding*> m_vecBuilding;
	cMapObjectManager(void);
	~cMapObjectManager(void);

	cMapTerrain* m_pMapTerrain;


public:
	//�̱��� ����
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	//���Ϳ� �ǹ� Ŭ���� �߰��ϴ� �Լ�
	void AppendBuilding(cBuilding* build);
	//���������� �߰��� �� ������Ʈ�� ��ȯ�ϴ� �Լ�(�ӽ�)
	cBuilding* GetLastMapObject();
	//���������� �߰��� �ʿ�����Ʈ�� �����ϴ� �Լ�
	bool PopMapObject();


	void Update();
	void Update(cMapTerrain* map);

	void Render();


	void Destroy();
};