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

	//���� ��ȯ ��ġ ���
	int m_nMonsterCursor;
	//���õ� ����
	cPlayer* m_pSelectMonster;
	
public:
	void Update(void);
	void SelectUpdate(cMapTerrain * map);
	void Render(void);
	//���� ���� ����
	void monsterRender(void);

	//��Ʈ�� �Լ�
	void Controller(void);

	//�˻� �Լ�
	cPlayer* GetMinRangeMonster(cPlayer* pCenter, float fRange);	//���� ����� ���͸� ã�´�.
	void GetNextTarget(cPlayer** ppTarget, LPD3DXVECTOR3 pCenter, float fRange);

	void RegisterPlayer(IN cPlayer* pPlayer);
	void SavePlayerData(IN LPCSTR FullPath);
	void LoadPlayerData(IN LPCSTR FullPath);
	cPlayer* GetPlayer(void) { return m_pPlayer; }
	std::vector<cPlayer*>* GetMonsterVectorPointer(void) { return &m_vecMonster; }
	bool GetMonster(OUT cPlayer** ppMonster, IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir);
	
	//���� �����̼� ��� ����

	//�������� �� ������Ʈ�� ��ȯ�ϴ� �Լ�
	cPlayer* GetSelectObject(void) { return m_pSelectMonster; }
	void SetCursorIncrease();
	cPlayer* GetMonsterRotation();
	void ResetMobSelect(void);
	void SetupMonster();

	//�� ���� ���� �ε�
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

