#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

#define DATA_VERSION 0.01f
#define IF_VERSION(fVersion, fMin, fMax) if(fMin < fVersion && fVersion >= fMax)
#define ELSE_IF_VERSION(fVersion, fMin, fMax) else if(fMin < fVersion && fVersion > fMax)

class cPlayer;
class cObjectManager
{
private:
	cPlayer* m_pPlayer;

public:
	void RegisterPlayer(cPlayer* pPlayer);
	void SavePlayerData(LPCSTR FullPath);
	void LoadPlayerData(LPCSTR FullPath);
	cPlayer* GetPlayer(void) { return m_pPlayer; }

	void Destroy(void);

	static cObjectManager* GetInstance() { static cObjectManager instance; return &instance; }
private:
	cObjectManager(void);
	virtual ~cObjectManager(void);
};

