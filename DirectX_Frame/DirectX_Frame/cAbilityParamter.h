#pragma once
class cAbilityParamter
{
private:
	int nMinLife;		//�ּ� �����
	int nMinMana;		//�ּ� ������
	int nMinStamina;	//�ּ� ���׹̳�

	int nMaxLife;		//�ִ� �����
	int nMaxMana;		//�ִ� ������
	int nMaxStamina;	//�ִ� ���׹̳�

	int nWoumd;			//�λ�

	int nMinDamage;		//�ּ� ���ݷ�
	int nBonusDamage;	//�߰� ���ݷ�
	int nMagicDamage;	//���� ���ݷ�
	int nDefence;		//���
	int nProtecte;		//��ȣ
	int nMagicDefence;	//���� ���
	int nMagicProtecte;	//���� ��ȣ

	float fStr;			//ü��
	float fInt;			//����
	float fDex;			//�ؾ�
	float fWill;		//����
	float fLuk;			//���

	float fInjury;		//�λ��
	float fBalance;		//������
	float fPenetration;	//���� ����

	float fFood;		//�����

	float fDownGauge;	//�ٿ������ 100, 120, 150

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

