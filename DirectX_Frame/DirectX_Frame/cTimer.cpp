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
	//������ ���� (�Ʒ����� _lockFPS = 60.0f ���༭ �ʿ����)
//	this->SetLockFPS();

	//�ϵ���� ���� Ÿ�̸Ӹ� ����� �� ���� ���
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//�ϵ���� Ÿ�̸Ӱ� ��밡���ϴٴ°��� ��Ʈ
		_isHardware = true;
		//�ʱ� �ð� ���� (09/03 ���� ���� ����)
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
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
	//�ϵ���� ī���͸� ����� �� ������ ����ð��� �޾ƿ�
	//�׷��� ������ getTickCount�� ����Ѵ�.
	if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	else _curTime = GetTickCount();

	//������Ʈ ���ݴ� �ɸ� �ð� ���
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//���� �ð��� ������Ʈ
	_lastTime = _curTime;
	//FPS������ ī��Ʈ����
	_FPSFrameCount++;
	//�ʴ� �����Ӱ�� ���� �ݿ�
	_FPSTimeElapsed += _timeElapsed;
	//���� Ÿ�� ����
	_worldTime += _timeElapsed;

	//_FPSTimeElepsed�� 1�ʰ� �����ٸ� �ʴ�FPS�� �����Ѵ�.
	if (_FPSTimeElapsed > 1.0f)
	{
		//�ʴ� �������� �����ϰ�
		_frameRate = _FPSFrameCount;
		//������ ī��Ʈ�� �ʱ�ȭ
		_FPSFrameCount = 0.0f;
		//FPS�ð� ������ �ʱ�ȭ
		_FPSTimeElapsed = 0.0f;
	}

}

float cTimer::GetWorldCheck(void)
{
	return 0.0f;
}
