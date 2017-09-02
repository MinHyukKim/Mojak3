#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer(void)
{
	//������ ���ÿ� ����
	this->Setup();
}

cTimer::~cTimer(void)
{
}

void cTimer::Setup(void)
{
	//������ ����
	this->SetLockFPS();

	//�ϵ���� ���� Ÿ�̸Ӹ� ����� �� ���� ���
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//�ϵ���� Ÿ�̸Ӱ� ��밡���ϴٴ°��� ��Ʈ
		_isHardware = true;
		//�ʱ� �ð� ����
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime));
		//�ʴ� �󵵼� ����
		_timeScale = 1.0f / _periodFrequency;
	}//�ϵ���� ���� Ÿ�̸Ӹ� ����� �� ���� ���
	else
	{
		//�ϵ���� Ÿ�̸� ��� �Ұ� ��Ʈ
		_isHardware = false;
		//�ʱ� �ð��� getTickCount���� �޾ƿ´�
		_lastTime = GetTickCount(); 
		//Ÿ�ӽ������� 0.001f�� ����
		_timeScale = 0.001f;
	}

	//���� �ʱⰪ ��Ʈ
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;
	_lockFPS = 60.0f;

}

void cTimer::Update(void)
{
}

float cTimer::GetWorldCheck(void)
{
	return 0.0f;
}
