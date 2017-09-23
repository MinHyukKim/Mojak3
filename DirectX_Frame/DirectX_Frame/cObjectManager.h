#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

#define DATA_VERSION 0.01f
#define IF_VERSION(fVersion, fMin, fMax) if(fMin < fVersion && fVersion >= fMax)
#define ELSE_IF_VERSION(fVersion, fMin, fMax) else if(fMin < fVersion && fVersion > fMax)

class cPlayer;
class cMapTerrain;
class cObjectManager
{
public:
	enum MONSTER_TYPE
	{
		MONSTER_NULL,
		MONSTER_TEXTER,
	};
private:
	cPlayer* m_pPlayer;
	cMapTerrain*  m_pTerrain;
	std::vector<cPlayer*>  m_vecMonster;
	std::vector<cPlayer*>  m_vecRelease;
public:
	void Update(void);
	void Render(void);

	//컨트롤 함수
	void Controller(void);

	//검색 함수
	cPlayer* GetMinRangeMonster(cPlayer* pCenter, float fRange);	//대상과 가까운 몬스터를 찾는다.
	void GetNextTarget(cPlayer** ppTarget, LPD3DXVECTOR3 pCenter, float fRange);

	void RegisterPlayer(IN cPlayer* pPlayer);
	void SavePlayerData(IN LPCSTR FullPath);
	void LoadPlayerData(IN LPCSTR FullPath);
	cPlayer* GetPlayer(void) { return m_pPlayer; }

	void SetTerrain(IN cMapTerrain* pTerrain);

	bool CreateMonster(IN MONSTER_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion);
	void ReleaseMonster(IN cPlayer* pMonster) { return m_vecRelease.push_back(pMonster); }
	void Destroy(void);

	static cObjectManager* GetInstance(void) { static cObjectManager instance; return &instance; }
private:
	cObjectManager(void);
	virtual ~cObjectManager(void);
};

