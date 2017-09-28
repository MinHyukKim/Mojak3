#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()

class cMapTerrain;

//�ʿ�����Ʈ ���͸� �����ϴ� Ŭ����
class cMapObjectRail
{
private:
	std::vector<cBuilding*> m_vecBuilding;
public:
	void Update(cMapTerrain* map);
	void Render();

	cMapObjectRail(void);
	~cMapObjectRail(void);

	//���Ϳ� �ǹ� Ŭ���� �߰��ϴ� �Լ�
	void AppendBuilding(cBuilding* build);

	//���������� �߰��� �� ������Ʈ�� ��ȯ�ϴ� �Լ�(�ӽ�)
	cBuilding* GetLastMapObject();
	//���������� �߰��� �ʿ�����Ʈ�� �����ϴ� �Լ�
	bool PopMapObject();
	void Destroy();


};

//�ʿ�����Ʈ�� ����ϰ� �����ϴ� Ŭ����
class cMapObjectManager
{
private:
	std::map<std::string, cBuilding*> m_mapBuilding;
	std::vector<cBuilding*> m_vecBuilding;
	cBuilding* m_pSelectBuilding;
	D3DXVECTOR3 m_vLandPos;

	cMapObjectManager(void);
	~cMapObjectManager(void);

	cMapTerrain* m_pMapTerrain;
//	cMapObjectRail* m_pMapObjects;

public:
	//�̱��� ����
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	//���Ϳ� �ǹ� Ŭ���� �߰��ϴ� �Լ�
	bool AppendBuilding(cBuilding* build);
	bool AppendBuilding(std::string& szKeyName);
	bool AppendBuilding(LPCSTR szKeyName);

	//�� �ȿ� ����ִ� ������Ʈ���� ��ȸ�ϸ鼭 ��ȯ
	cBuilding* getMapObjectRotation();


	int cur;
	//���������� �߰��� �� ������Ʈ�� ��ȯ�ϴ� �Լ�(�ӽ�)
	cBuilding* GetLastMapObject();
	//���������� �߰��� �ʿ�����Ʈ�� �����ϴ� �Լ�
	bool PopMapObject();


//	void Update();
	void Update(cMapTerrain* map);

	void Render();
//
//	//���� ������Ʈ�� ���Ϸ� ���̺�
//	void SaveCurrentObjectsState(const char* filename);
//	void LoadCurrentObjectsState(const char* filename);

	void Destroy();
};