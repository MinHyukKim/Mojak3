#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer(void)
{
	//생성과 동시에 설정
	this->Setup();
}

cTimer::~cTimer(void)
{
}

void cTimer::Setup(void)
{
	//프레임 해제
	this->SetLockFPS();

	//하드웨어 정밀 타이머를 사용할 수 있을 경우
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//하드웨어 타이머가 사용가능하다는것을 세트
		_isHardware = true;
		//초기 시간 설정
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime));
		//초당 빈도수 설정
		_timeScale = 1.0f / _periodFrequency;
	}//하드웨어 정밀 타이머를 사용할 수 없을 경우
	else
	{
		//하드웨어 타이머 사용 불가 세트
		_isHardware = false;
		//초기 시간을 getTickCount에서 받아온다
		_lastTime = GetTickCount(); 
		//타임스케일은 0.001f로 설정
		_timeScale = 0.001f;
	}

	//변수 초기값 세트
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
