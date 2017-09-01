#include "Timer.h"
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")



Timer::Timer(void)
{

}


Timer::~Timer(void)
{

}


HRESULT Timer::Init(void)
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;
	_lockFPS = 60.0f;

	return S_OK;
}

void Timer::Release(void)
{

}

void Timer::Update(void)
{
	if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	else _curTime = timeGetTime();

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (_lockFPS > 0.0f) while (_timeElapsed < (1.0f / _lockFPS))
	{
		if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
		else _curTime = timeGetTime();

		_timeElapsed = (_curTime - _lastTime) * _timeScale;
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::GetFPS(TCHAR* str) const
{
	if (str != NULL) wsprintf(str, "FPS : %d", _frameRate);
	return _frameRate;
}
