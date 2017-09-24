#pragma once
#include "cBuilding.h"

#define g_pMapObjectManager cMapObjectManager::GetInstance()

class cMapObjectManager
{
private:
	std::map<std::string, cBuilding*> m_mapBuilding;
	cMapObjectManager(void);
	~cMapObjectManager(void);

public:
	//½Ì±ÛÅæ »ý¼º
	static cMapObjectManager* GetInstance() { static cMapObjectManager instance; return &instance; }

	cBuilding* GetMapObject(char* szFolder, char* szFilename);
	cBuilding* RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName);
	cBuilding* RegisterMapObject(std::string& szFolder, std::string& szFilename, std::string& szKeyName);
	cBuilding* GetMapObject(LPCSTR szKeyName);
	cBuilding* GetMapObject(std::string& szKeyName);


	void Destroy();
};