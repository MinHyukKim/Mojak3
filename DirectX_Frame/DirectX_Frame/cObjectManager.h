#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

#define DATA_VERSION 0.01f
#define IF_VERSION(fVersion, fMin, fMax) if(fMin < fVersion && fVersion >= fMax)
#define ELSE_IF_VERSION(fVersion, fMin, fMax) else if(fMin < fVersion && fVersion > fMax)

class cPlayer;
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
	std::vector<cPlayer*>  m_vecMonster;
	std::vector<cPlayer*>  m_vecRelease;
public:
	void Update(void);
	void Render(void);

	void RegisterPlayer(IN cPlayer* pPlayer);
	void SavePlayerData(IN LPCSTR FullPath);
	void LoadPlayerData(IN LPCSTR FullPath);
	cPlayer* GetPlayer(void) { return m_pPlayer; }

	bool CreateMonster(IN MONSTER_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion);
	void ReleaseMonster(cPlayer* pMonster) { return m_vecRelease.push_back(pMonster); }
	void Destroy(void);

	static cObjectManager* GetInstance(void) { static cObjectManager instance; return &instance; }
private:
	cObjectManager(void);
	virtual ~cObjectManager(void);
};

