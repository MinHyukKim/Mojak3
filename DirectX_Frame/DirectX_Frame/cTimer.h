#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
private:
	//�ϵ���� Ÿ�̸� ��밡�� ����
	bool	_isHardware;
	//�ѹ� ������Ʈ�Ҷ����� �ɸ� �ð� ����.
	float	_timeElapsed;


public:
	cTimer();
	~cTimer();

	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

