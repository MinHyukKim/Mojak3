#pragma once
class cAbilityParamter
{
private:
	DWORD m_dwUnitID;			//종족번호
	DWORD m_dwPlayerID;			//컨트롤러 권한
	DWORD m_dwAICodeID;			//인공지능 번호

	int m_nLevel;				//레벨
	float m_fEXP;				//경험치
	float m_fMaxEXP;			//최대 경험치(레벨업 필요 경험치)
	int m_nAP;					//AP
	int m_nAdventureLevel;		//탐험 레벨
	float m_fAdventureEXP;		//탐험 경험치	
	float m_fMaxAdventureEXP;	//최대 탐험 경험치(레벨업 필요 경험치)

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
	float m_fCritical;			//크리티컬
	float m_fBalance;			//벨런스
	float m_fPenetration;		//물리 관통

	float m_fFood;				//배고픔
	float m_fAttackRange;		//공격범위
	float m_fDownGauge;			//다운게이지 4.5(밀림)
	float m_fPower;				//파워
	float m_fMoveSpeed;			//이동속도

	float m_fDelayTime;			//인공지능 유효시간
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
	float GetStr(void) { return m_fStr; }
	void SetInt(float nValue) { m_fInt = nValue; }
	float GetInt(void) { return m_fInt; }
	void SetDex(float nValue) { m_fDex = nValue; }
	float GetDex(void) { return m_fDex; }
	void SetWill(float nValue) { m_fWill = nValue; }
	float GetWill(void) { return m_fWill; }
	void SetLuk(float nValue) { m_fLuk = nValue; }
	float GetLuk(void) { return m_fLuk; }
	//레벨
	void SetLevel(int n) { m_nLevel = n; }
	int GetLevel(void) { return m_nLevel; }
	//경험치 
	void SetMaxEXP(float f) { m_fMaxEXP = f; }
	float GetMaxEXP(void) { return m_fMaxEXP; }
	void SetEXP(float f) { m_fEXP = f; }
	float GetEXP(void) { return m_fEXP; }
	//AP
	void SetAP(int n) { m_nAP = n; }
	int GetAP(void) { return m_nAP; }
	//탐험 레벨
	void SetAdventureLevel(int n) { m_nAdventureLevel = n; }
	int GetAdventureLevel(void) { return m_nAdventureLevel; }
	//탐험 경험치
	void SetMaxAdventureEXP(float f) { m_fMaxAdventureEXP = f; }
	float GetMaxAdventureEXP(void) { return m_fMaxAdventureEXP; }
	void SetAdventureEXP(float f) { m_fAdventureEXP = f; }
	float GetAdventureEXP(void) { return m_fAdventureEXP; }
	//피통
	void SetMaxHP(int n) { m_nMaxLife = n; }
	int GetMaxHP(void) { return m_nMaxLife; }
	void SetMinHP(int n) { m_nMinLife = n; }
	int GetMinHP(void) { return m_nMinLife; }
	//마나통
	void SetMaxMP(int n) { m_nMaxMana = n; }
	int GetMaxMP(void) { return m_nMaxMana; }
	void SetMinMP(int n) { m_nMinMana = n; }
	int GetMinMP(void) { return m_nMinMana; }
	//스테미나
	void SetMaxStamina(int n) { m_nMaxStamina = n; }
	int GetMaxStamina(void) { return m_nMaxStamina; }
	void SetMinStamina(int n) { m_nMinStamina = n; }
	int GetMinStamina(void) { return m_nMinStamina; }
	//공격력
	void SetmMinDamage(int n) { m_nMinDamage = n; }
	int GetMinDamage(void) { return m_nMinDamage; }
	void SetBonusDamage(int n) { m_nBonusDamage = n; }
	int GetBonusDamage(void) { return m_nBonusDamage; }
	//마공
	void SetMagicDamage(int n) { m_nMagicDamage = n; }
	int GetMagicDamage(void) { return m_nMagicDamage; }
	//부상률
	void SetInjury(float f) { m_fInjury = f; }
	float GetInjury(void) { return m_fInjury; }
	//크리티컬
	void SetCritical(float f) { m_fCritical = f; }
	float GetCritical(void) { return m_fCritical; }
	//벨런스
	void SetBalance(float f) { m_fBalance = f; }
	float GetBalance(void) { return m_fBalance; }
	//방어
	void SetDefence(int n) { m_nDefence = n; }
	int GetDefence(void) { return m_nDefence; }
	//보호
	void SetProtecte(int n) { m_nProtecte = n; }
	int GetProtecte(void) { return m_nProtecte; }
	//마법방어
	void SetMagicDefence(int n) { m_nMagicDefence = n; }
	int GetMagicDefence(void) { return m_nMagicDefence; }
	//마법보호
	void SetMagicProtecte(int n) { m_nMagicProtecte = n; }
	int GetMagicProtecte(void) { return m_nMagicProtecte; }
	//방어관통
	void SetPenetration(float f) { m_fPenetration = f; }
	float GetPenetration(void) { return m_fPenetration; }
	//공격범위
	void SetRange(float fValue) { m_fAttackRange = fValue; }
	float GetRange(void) { return m_fAttackRange; }
	float GetRangeSq(void) { return m_fAttackRange * m_fAttackRange; }
	//다운게이지
	void SetDownGauge(float fValue) { m_fDownGauge = fValue; }
	float GetDownGauge(void) { return m_fDownGauge; }
	//게이지 증가량
	void SetPower(float fValue) { m_fPower = fValue; }
	float GetPower(void) { return m_fPower; }
	//이동속도
	void SetMoveSpeed(float fValue) { m_fMoveSpeed = fValue; }
	float GetMoveSpeed(void) { return m_fMoveSpeed; }
	//지연시간
	void SetDelayTime(float fValue) { m_fDelayTime = fValue; }
	float GetDelayTime(void) { return m_fDelayTime; }
	bool IsDelayEnd(void) { return m_fDelayTime <= 0.0f; }

	void SetEffective(bool nValue) { m_bEffective = nValue; }
	bool IsEffective(void) { return m_bEffective; }

	cAbilityParamter(void);
	virtual ~cAbilityParamter(void);
};

