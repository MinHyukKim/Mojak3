#pragma once
class cAbilityParamter
{
private:
	DWORD m_dwUnitID;			//종족번호
	DWORD m_dwPlayerID;			//컨트롤러 권한
	DWORD m_dwAICodeID;			//인공지능 번호

	int m_nMinLife;				//최소 생명력
	int m_nMinMana;				//최소 마나량
	int m_nMinStamina;			//최소 스테미나

	int m_nMaxLife;				//최대 생명력
	int m_nMaxMana;				//최대 마나량
	int m_nMaxStamina;			//최대 스테미나

	int m_nWoumd;				//부상

	int m_nMinDamage;			//최소 공격력
	int m_nBonusDamage;			//추가 공격력
	int m_nMagicDamage;			//마법 공격력
	int m_nDefence;				//방어
	int m_nProtecte;			//보호
	int m_nMagicDefence;		//마법 방어
	int m_nMagicProtecte;		//마법 보호

	float m_fStr;				//체력
	float m_fInt;				//지력
	float m_fDex;				//솜씨
	float m_fWill;				//의지
	float m_fLuk;				//행운

	float m_fInjury;			//부상률
	float m_fBalance;			//벨런스
	float m_fPenetration;		//물리 관통

	float m_fFood;				//배고픔
	float m_fRange;				//공격범위
	float m_fDownGauge;	//다운게이지 100(밀림), 120(너머짐), 150()
	float m_fMoveSpeed;			//이동속도

	float m_fAIDelayTime;		//인공지능 유효시간
	bool m_bEffective;			//캐릭터 생존여부

public:
	void Update(void);

	void SetUnitID(DWORD dwValue) { m_dwUnitID = dwValue; }
	DWORD GetUnitID(void) { return m_dwUnitID; }
	void SetPlayerID(DWORD dwValue) { m_dwPlayerID = dwValue; }
	DWORD GetPlayerID(void) { return m_dwPlayerID; }
	void SetAICodeID(DWORD dwValue) { m_dwAICodeID = dwValue; }
	DWORD GetAICodeID(void) { return m_dwAICodeID; }

	void SetStr(float nValue) { m_fStr = nValue; }
	int GetStr(void) { return m_fStr; }
	void SetInt(float nValue) { m_fInt = nValue; }
	int GetInt(void) { return m_fInt; }
	void SetDex(float nValue) { m_fDex = nValue; }
	int GetDex(void) { return m_fDex; }
	void SetWill(float nValue) { m_fWill = nValue; }
	int GetWill(void) { return m_fWill; }
	void SetLuk(float nValue) { m_fLuk = nValue; }
	int GetLuk(void) { return m_fLuk; }

	void SetMoveSpeed(float fValue) { m_fMoveSpeed = fValue; }
	float GetMoveSpeed(void) { return m_fMoveSpeed; }
	void SetDelayTime(float fValue) { m_fAIDelayTime = fValue; }
	float GetDelayTime(void) { return m_fAIDelayTime; }
	bool IsDelayTime(void) { return m_fAIDelayTime <= 0.0f; }
	void SetEffective(bool nValue) { m_bEffective = nValue; }
	bool IsEffective(void) { return m_bEffective; }

	cAbilityParamter(void);
	virtual ~cAbilityParamter(void);
};

