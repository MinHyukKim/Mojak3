#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
private:
	//�ϵ���� Ÿ�̸� ��밡�� ����
	bool	_isHardware;

public:
	cTimer();
	~cTimer();

	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

