#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()

class cMapTerrain;
//맵오브젝트를 등록하고 관리하는 클래스
class cMapObjectManager
{
public:
	enum E_OBJECT_TYPE
	{
		BUILDING,// 건물
		INTERIOR,// 인테리어(나무같은)
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
	//오브젝트 프리셋 커서
	int m_nBuildCursor;

	struct m_stMapObject
	{
		//오브젝트 타입
		E_OBJECT_TYPE type;
		//오브젝트 경로
		std::string name;
		//오브젝트 위치 매트릭스;
		D3DXMATRIX matWorld;
	};

public:
	//싱글톤 생성
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	void SetMapTerrain(cMapTerrain* map) { m_pMapTerrain = map; }


	//백터에 건물 클래스 추가하는 함수
	bool AppendBuilding(cBuilding* build);
	bool AppendBuilding(std::string& szKeyName);
	bool AppendBuilding(LPCSTR szKeyName);

	//맵 안에 들어있는 오브젝트들을 순회하면서 반환
	cBuilding* getMapObjectRotation();


	void SetCursorIncrease();

	//마지막으로 추가된 맵 오브젝트를 반환하는 함수(임시)
	cBuilding* GetLastMapObject();
	//선택중인 맵 오브젝트를 반환하는 함수
	cBuilding* GetSelectObject(void) { return m_pSelectBuilding; }
	//현재 마우스 위치에 건물을 빌딩하는 스위치
	void SetupBuilding(void);
	void ResetBuilding(void) { m_pSelectBuilding = nullptr; }
	//마지막으로 추가된 맵오브젝트를 삭제하는 함수
	bool PopMapObject();


//	void Update();
	void Update(cMapTerrain* map);

	void Render();
//
//	//현재 오브젝트들 파일로 세이브
	void SaveCurrentObjectsState(const char* filename);
	void LoadCurrentObjectsState(const char* filename);

	void Destroy();
	void DestroyBuilding();
};