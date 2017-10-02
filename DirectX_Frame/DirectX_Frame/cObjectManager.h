#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

#define DATA_VERSION 0.01f
#define IF_VERSION(fVersion, fMin, fMax) if(fMin < fVersion && fVersion >= fMax)
#define ELSE_IF_VERSION(fVersion, fMin, fMax) else if(fMin < fVersion && fVersion > fMax)

#define FOX_BROWN	D3DXCOLOR(0.5f, 0.25f, 0.25f, 1.0f)
#define FOX_GRAY	D3DXCOLOR(0.33f, 0.33f, 0.33f, 1.0f)
#define FOX_RED		D3DXCOLOR(0.75f, 0.25f, 0.25f, 1.0f)
#define BEAR_BROWN	D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f)
#define BEAR_WHITE  D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
#define BEAR_BLACK  D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)

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
		MONSTER_BEAR,
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
	//선택된 몬스터
	cPlayer* m_pSelectMonster;
	
public:
	void Update(void);
	void SelectUpdate(cMapTerrain * map);
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

	//선택중인 맵 오브젝트를 반환하는 함수
	cPlayer* GetSelectObject(void) { return m_pSelectMonster; }
	void SetCursorIncrease();
	cPlayer* GetMonsterRotation();
	void ResetMobSelect(void);
	void SetupMonster();

	//맵 몬스터 저장 로드
	bool SaveMonsterObjectState(const char* filename);
	bool LoadMonsterObjectState(const char* filename);

	void SetTerrain(IN cMapTerrain* pTerrain);

	cPlayer* CreateMonster(IN UNIT_TYPE eMonsterKey, IN LPD3DXVECTOR3 pPostion, IN LPD3DXCOLOR pColor = nullptr);
	bool CreateNPC(IN UNIT_TYPE eNPCKey, IN LPD3DXVECTOR3 pPostion);
	void ReleaseMonster(IN cPlayer* pMonster) { return m_vecRelease.push_back(pMonster); }
	void Destroy(void);

	static cObjectManager* GetInstance(void) { static cObjectManager instance; return &instance; }

private:
	cObjectManager(void);
	virtual ~cObjectManager(void);
};

