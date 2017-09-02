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
	//���� Ÿ�̸� ����
	__int64 _periodFrequency;

	//1�ʸ��� ������ ī��Ʈ�� ����
	unsigned long _frameRate;
	//�����Ӹ��� ī��Ʈ�� 1�� ����
	unsigned long _FPSFrameCount;
	//1�ʰ� �ɶ����� ī��Ʈ�� �����ϴ� ����
	float _FPSTimeElapsed;
	//���α׷��� �����ϰ� ���������� ���� �ð�
	float _worldTime;
	//���� ������ ���� ����
	float _lockFPS;

public:
	//�¾� �Լ�
	virtual void Setup(void);
	//������Ʈ �Լ�
	virtual void Update(void);
	
	//���� �Լ�(���� �ۼ�)
	//virtual void Render(void);



	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

private:
	cTimer(void);
	virtual ~cTimer(void);

};

