#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()

class cMapTerrain;
//�ʿ�����Ʈ�� ����ϰ� �����ϴ� Ŭ����
class cMapObjectManager
{
public:
	enum E_OBJECT_TYPE
	{
		BUILDING,// �ǹ�
		INTERIOR,// ���׸���(��������)
		END,
	};



private:
	std::map<std::string, cBuilding*> m_mapBuilding;
	std::vector<cBuilding*> m_vecBuilding;
	cBuilding* m_pSelectBuilding;
	D3DXVECTOR3 m_vLandPos;

	cMapObjectManager(void);
	~cMapObjectManager(void);

	cMapTerrain* m_pMapTerrain;
//	cMapObjectRail* m_pMapObjects;
	//������Ʈ ������ Ŀ��
	int m_nBuildCursor;

	struct m_stMapObject
	{
		//������Ʈ Ÿ��
		E_OBJECT_TYPE type;
		//������Ʈ ���
		std::string name;
		//������Ʈ ��ġ ��Ʈ����;
		D3DXMATRIX matWorld;
	};

public:
	//�̱��� ����
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	void SetMapTerrain(cMapTerrain* map) { m_pMapTerrain = map; }


	//���Ϳ� �ǹ� Ŭ���� �߰��ϴ� �Լ�
	bool AppendBuilding(cBuilding* build);
	bool AppendBuilding(std::string& szKeyName);
	bool AppendBuilding(LPCSTR szKeyName);

	//�� �ȿ� ����ִ� ������Ʈ���� ��ȸ�ϸ鼭 ��ȯ
	cBuilding* getMapObjectRotation();


	void SetCursorIncrease();

	//���������� �߰��� �� ������Ʈ�� ��ȯ�ϴ� �Լ�(�ӽ�)
	cBuilding* GetLastMapObject();
	//�������� �� ������Ʈ�� ��ȯ�ϴ� �Լ�
	cBuilding* GetSelectObject(void) { return m_pSelectBuilding; }
	//���� ���콺 ��ġ�� �ǹ��� �����ϴ� ����ġ
	void SetupBuilding(void);
	void ResetBuilding(void) { m_pSelectBuilding = nullptr; }
	//���������� �߰��� �ʿ�����Ʈ�� �����ϴ� �Լ�
	bool PopMapObject();


//	void Update();
	void Update(cMapTerrain* map);

	void Render();
//
//	//���� ������Ʈ�� ���Ϸ� ���̺�
	void SaveCurrentObjectsState(const char* filename);
	void LoadCurrentObjectsState(const char* filename);

	void Destroy();
	void DestroyBuilding();
};