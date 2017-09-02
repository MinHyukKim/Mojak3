#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
private:
	//�ϵ���� Ÿ�̸� ��밡�� ����
	bool	_isHardware;
	//�ѹ� ������Ʈ�Ҷ����� �ɸ� �ð� ����.
	float	_timeElapsed;
	//1��/������Ʈ�Ǵ� Ƚ��
	float	_timeScale;




public:
	cTimer();
	~cTimer();

	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

