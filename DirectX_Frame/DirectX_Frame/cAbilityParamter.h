#pragma once
class cAbilityParamter
{
private:
	DWORD m_dwUnitID;			//������ȣ
	DWORD m_dwPlayerID;			//��Ʈ�ѷ� ����
	DWORD m_dwAICodeID;			//�ΰ����� ��ȣ

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
	float m_fBalance;			//������
	float m_fPenetration;		//���� ����

	float m_fFood;				//�����
	float m_fRange;				//���ݹ���
	float m_fDownGauge;	//�ٿ������ 100(�и�), 120(�ʸ���), 150()
	float m_fMoveSpeed;			//�̵��ӵ�

	float m_fAIDelayTime;		//�ΰ����� ��ȿ�ð�
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

