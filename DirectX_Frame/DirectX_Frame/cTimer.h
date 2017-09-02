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

	//���� �ð�
	__int64	_curTime;
	//���� �ð�
	__int64 _lastTime;


public:


	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

private:
	cTimer(void);
	virtual ~cTimer(void);

};

