#pragma once
class cAbilityParamter
{
private:
	DWORD m_dwUnitID;			//������ȣ
	DWORD m_dwPlayerID;			//��Ʈ�ѷ� ����
	DWORD m_dwAICodeID;			//�ΰ����� ��ȣ

	int m_nLevel;				//����
	float m_fEXP;				//����ġ
	float m_fMaxEXP;			//�ִ� ����ġ(������ �ʿ� ����ġ)
	int m_nAP;					//AP
	int m_nAdventureLevel;		//Ž�� ����
	float m_fAdventureEXP;		//Ž�� ����ġ	
	float m_fMaxAdventureEXP;	//�ִ� Ž�� ����ġ(������ �ʿ� ����ġ)

	int m_nMinLife;				//�ּ� �����
	int m_nMinMana;				//�ּ� ������
	int m_nMinStamina;			//�ּ� ���׹̳�

	int m_nMaxLife;				//�ִ� �����
	int m_nMaxMana;				//�ִ� ������
	int m_nMaxStamina;			//�ִ� ���׹̳�

	int m_nWoumd;				//�λ�

	int m_nMinDamage;			//�ּ� ���ݷ�
	int m_nBonusDamage;			//�߰� ���ݷ�
	int m_nMagicDamage;			//���� ���ݷ�
	int m_nDefence;				//���
	int m_nProtecte;			//��ȣ
	int m_nMagicDefence;		//���� ���
	int m_nMagicProtecte;		//���� ��ȣ

	float m_fStr;				//ü��
	float m_fInt;				//����
	float m_fDex;				//�ؾ�
	float m_fWill;				//����
	float m_fLuk;				//���

	float m_fInjury;			//�λ��
	float m_fCritical;			//ũ��Ƽ��
	float m_fBalance;			//������
	float m_fPenetration;		//���� ����

	float m_fFood;				//�����
	float m_fAttackRange;		//���ݹ���
	float m_fDownGauge;			//�ٿ������ 4.5(�и�)
	float m_fPower;				//�Ŀ�
	float m_fMoveSpeed;			//�̵��ӵ�

	float m_fDelayTime;			//�ΰ����� ��ȿ�ð�
	bool m_bEffective;			//ĳ���� ��������

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
	//����
	void SetLevel(int n) { m_nLevel = n; }
	int GetLevel(void) { return m_nLevel; }
	//����ġ 
	void SetMaxEXP(float f) { m_fMaxEXP = f; }
	float GetMaxEXP(void) { return m_fMaxEXP; }
	void SetEXP(float f) { m_fEXP = f; }
	float GetEXP(void) { return m_fEXP; }
	//AP
	void SetAP(int n) { m_nAP = n; }
	int GetAP(void) { return m_nAP; }
	//Ž�� ����
	void SetAdventureLevel(int n) { m_nAdventureLevel = n; }
	int GetAdventureLevel(void) { return m_nAdventureLevel; }
	//Ž�� ����ġ
	void SetMaxAdventureEXP(float f) { m_fMaxAdventureEXP = f; }
	float GetMaxAdventureEXP(void) { return m_fMaxAdventureEXP; }
	void SetAdventureEXP(float f) { m_fAdventureEXP = f; }
	float GetAdventureEXP(void) { return m_fAdventureEXP; }
	//����
	void SetMaxHP(int n) { m_nMaxLife = n; }
	int GetMaxHP(void) { return m_nMaxLife; }
	void SetMinHP(int n) { m_nMinLife = n; }
	int GetMinHP(void) { return m_nMinLife; }
	//������
	void SetMaxMP(int n) { m_nMaxMana = n; }
	int GetMaxMP(void) { return m_nMaxMana; }
	void SetMinMP(int n) { m_nMinMana = n; }
	int GetMinMP(void) { return m_nMinMana; }
	//���׹̳�
	void SetMaxStamina(int n) { m_nMaxStamina = n; }
	int GetMaxStamina(void) { return m_nMaxStamina; }
	void SetMinStamina(int n) { m_nMinStamina = n; }
	int GetMinStamina(void) { return m_nMinStamina; }
	//���ݷ�
	void SetmMinDamage(int n) { m_nMinDamage = n; }
	int GetMinDamage(void) { return m_nMinDamage; }
	void SetBonusDamage(int n) { m_nBonusDamage = n; }
	int GetBonusDamage(void) { return m_nBonusDamage; }
	//����
	void SetMagicDamage(int n) { m_nMagicDamage = n; }
	int GetMagicDamage(void) { return m_nMagicDamage; }
	//�λ��
	void SetInjury(float f) { m_fInjury = f; }
	float GetInjury(void) { return m_fInjury; }
	//ũ��Ƽ��
	void SetCritical(float f) { m_fCritical = f; }
	float GetCritical(void) { return m_fCritical; }
	//������
	void SetBalance(float f) { m_fBalance = f; }
	float GetBalance(void) { return m_fBalance; }
	//���
	void SetDefence(int n) { m_nDefence = n; }
	int GetDefence(void) { return m_nDefence; }
	//��ȣ
	void SetProtecte(int n) { m_nProtecte = n; }
	int GetProtecte(void) { return m_nProtecte; }
	//�������
	void SetMagicDefence(int n) { m_nMagicDefence = n; }
	int GetMagicDefence(void) { return m_nMagicDefence; }
	//������ȣ
	void SetMagicProtecte(int n) { m_nMagicProtecte = n; }
	int GetMagicProtecte(void) { return m_nMagicProtecte; }
	//������
	void SetPenetration(float f) { m_fPenetration = f; }
	float GetPenetration(void) { return m_fPenetration; }
	//���ݹ���
	void SetRange(float fValue) { m_fAttackRange = fValue; }
	float GetRange(void) { return m_fAttackRange; }
	float GetRangeSq(void) { return m_fAttackRange * m_fAttackRange; }
	//�ٿ������
	void SetDownGauge(float fValue) { m_fDownGauge = fValue; }
	float GetDownGauge(void) { return m_fDownGauge; }
	//������ ������
	void SetPower(float fValue) { m_fPower = fValue; }
	float GetPower(void) { return m_fPower; }
	//�̵��ӵ�
	void SetMoveSpeed(float fValue) { m_fMoveSpeed = fValue; }
	float GetMoveSpeed(void) { return m_fMoveSpeed; }
	//�����ð�
	void SetDelayTime(float fValue) { m_fDelayTime = fValue; }
	float GetDelayTime(void) { return m_fDelayTime; }
	bool IsDelayEnd(void) { return m_fDelayTime <= 0.0f; }

	void SetEffective(bool nValue) { m_bEffective = nValue; }
	bool IsEffective(void) { return m_bEffective; }

	cAbilityParamter(void);
	virtual ~cAbilityParamter(void);
};

