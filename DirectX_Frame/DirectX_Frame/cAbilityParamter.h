#pragma once
class cAbilityParamter
{
private:
	int nMinLife;		//최소 생명력
	int nMinMana;		//최소 마나량
	int nMinStamina;	//최소 스테미나

	int nMaxLife;		//최대 생명력
	int nMaxMana;		//최대 마나량
	int nMaxStamina;	//최대 스테미나

	int nWoumd;			//부상

	int nMinDamage;		//최소 공격력
	int nBonusDamage;	//추가 공격력
	int nMagicDamage;	//마법 공격력
	int nDefence;		//방어
	int nProtecte;		//보호
	int nMagicDefence;	//마법 방어
	int nMagicProtecte;	//마법 보호

	float fStr;			//체력
	float fInt;			//지력
	float fDex;			//솜씨
	float fWill;		//의지
	float fLuk;			//행운

	float fInjury;		//부상률
	float fBalance;		//벨런스
	float fPenetration;	//물리 관통

	float fFood;		//배고픔

	float fDownGauge;	//다운게이지 100, 120, 150

public:
	void SetStr(float nValue) { fStr = nValue; }
	int GetStr(void) { return fStr; }
	void SetInt(float nValue) { fInt = nValue; }
	int GetInt(void) { return fInt; }
	void SetDex(float nValue) { fDex = nValue; }
	int GetDex(void) { return fDex; }
	void SetWill(float nValue) { fWill = nValue; }
	int GetWill(void) { return fWill; }
	void SetLuk(float nValue) { fLuk = nValue; }
	int GetLuk(void) { return fLuk; }

	cAbilityParamter(void);
	virtual ~cAbilityParamter(void);
};

