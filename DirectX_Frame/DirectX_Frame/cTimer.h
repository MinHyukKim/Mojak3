#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
public:
	cTimer();
	~cTimer();

	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

