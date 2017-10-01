#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

#define DATA_VERSION 0.01f
#define IF_VERSION(fVersion, fMin, fMax) if(fMin < fVersion && fVersion >= fMax)
#define ELSE_IF_VERSION(fVersion, fMin, fMax) else if(fMin < fVersion && fVersion > fMax)

#define MONSTERCOLOR_BROWN D3DXCOLOR(0.5f, 0.25f, 0.25f, 1.0f)
#define MONSTERCOLOR_GRAY D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
#define MONSTERCOLOR_RED D3DXCOLOR(0.75f, 0.25f, 0.25f, 1.0f)

class cPlayer;
class cMapTerrain;
class cObjectManager
{
public:
	enum UNIT_TYPE
	{
		MONSTER_NULL,
		MONSTER_TEXTER,
		MONSTER_FOX,
		MONSTER_END,
		NPC_NAO,
	};

private:
	cPlayer* m_pPlayer;
	cMapTerrain*  m_pTerrain;
	std::vector<cPlayer*>  m_vecMonster;
	std::vector<cPlayer*>  m_vecNPC;
	std::vector<cPlayer*>  m_vecRelease;

	//몬스터 소환 위치 기록
	int m_nMonsterCursor;
	
public:
	void Update(void);
	void Render(void);
	//몹만 따로 렌더
	void monsterRender(void);

	//컨트롤 함수
	void Controller(void);

	//검색 함수
	cPlayer* GetMinRangeMonster(cPlayer* pCenter, float fRange);	//대상과 가까운 몬스터를 찾는다.
	void GetNextTarget(cPlayer** ppTarget, LPD3DXVECTOR3 pCenter, float fRange);

	void RegisterPlayer(IN cPlayer* pPlayer);
	void SavePlayerData(IN LPCSTR FullPath);
	void LoadPlayerData(IN LPCSTR FullPath);
	cPlayer* GetPlayer(void) { return m_pPlayer; }
	std::vector<cPlayer*>* GetMonsterVectorPointer(void) { return &m_vecMonster; }
	bool GetMonster(OUT cPlayer** ppMonster, IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir);
	
	//몬스터 로테이션 출력 관련
	void SetCursorIncrease();
	cPlayer* GetMonsterRotation();


	void SetTerrain(IN cMapTerrain* pTerrain);

	bool CreateMonster(IN UNIT_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion, IN LPD3DXCOLOR pColor = nullptr);
	bool CreateNPC(IN UNIT_TYPE eNPCKey, IN LPD3DXVECTOR3 pPostion);
	void ReleaseMonster(IN cPlayer* pMonster) { return m_vecRelease.push_back(pMonster); }
	void Destroy(void);

	static cObjectManager* GetInstance(void) { static cObjectManager instance; return &instance; }
private:
	cObjectManager(void);
	virtual ~cObjectManager(void);
};

