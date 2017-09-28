#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()

class cMapTerrain;

//맵오브젝트 백터를 관리하는 클래스
class cMapObjectRail
{
private:
	std::vector<cBuilding*> m_vecBuilding;
public:
	void Update(cMapTerrain* map);
	void Render();

	cMapObjectRail(void);
	~cMapObjectRail(void);

	//백터에 건물 클래스 추가하는 함수
	void AppendBuilding(cBuilding* build);

	//마지막으로 추가된 맵 오브젝트를 반환하는 함수(임시)
	cBuilding* GetLastMapObject();
	//마지막으로 추가된 맵오브젝트를 삭제하는 함수
	bool PopMapObject();
	void Destroy();


};

//맵오브젝트를 등록하고 관리하는 클래스
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
	//싱글톤 생성
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	//백터에 건물 클래스 추가하는 함수
	bool AppendBuilding(cBuilding* build);
	bool AppendBuilding(std::string& szKeyName);
	bool AppendBuilding(LPCSTR szKeyName);

	//맵 안에 들어있는 오브젝트들을 순회하면서 반환
	cBuilding* getMapObjectRotation();


	int cur;
	//마지막으로 추가된 맵 오브젝트를 반환하는 함수(임시)
	cBuilding* GetLastMapObject();
	//마지막으로 추가된 맵오브젝트를 삭제하는 함수
	bool PopMapObject();


//	void Update();
	void Update(cMapTerrain* map);

	void Render();
//
//	//현재 오브젝트들 파일로 세이브
//	void SaveCurrentObjectsState(const char* filename);
//	void LoadCurrentObjectsState(const char* filename);

	void Destroy();
};