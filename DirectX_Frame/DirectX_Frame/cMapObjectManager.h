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
	//싱글톤 생성
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);

	//백터에 건물 클래스 추가하는 함수
	void AppendBuilding(cBuilding* build);
	//마지막으로 추가된 맵 오브젝트를 반환하는 함수(임시)
	cBuilding* GetLastMapObject();
	//마지막으로 추가된 맵오브젝트를 삭제하는 함수
	bool PopMapObject();


	void Update();
	void Update(cMapTerrain* map);

	void Render();


	void Destroy();
};