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
	//프레임 해제 (아래에서 _lockFPS = 60.0f 해줘서 필요없음)
//	this->SetLockFPS();

	//하드웨어 정밀 타이머를 사용할 수 있을 경우
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//하드웨어 타이머가 사용가능하다는것을 세트
		_isHardware = true;
		//초기 시간 설정 (09/03 구문 오류 수정)
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
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
	//하드웨어 카운터를 사용할 수 있으면 현재시간을 받아옴
	//그렇지 않으면 getTickCount를 사용한다.
	if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	else _curTime = GetTickCount();

	//업데이트 간격당 걸린 시간 계산
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//이전 시간을 업데이트
	_lastTime = _curTime;
	//FPS프레임 카운트증가
	_FPSFrameCount++;
	//초당 프레임계산 변수 반영
	_FPSTimeElapsed += _timeElapsed;
	//월드 타임 증가
	_worldTime += _timeElapsed;

	//_FPSTimeElepsed가 1초가 지났다면 초당FPS를 갱신한다.
	if (_FPSTimeElapsed > 1.0f)
	{
		//초당 프레임을 갱신하고
		_frameRate = _FPSFrameCount;
		//프레임 카운트를 초기화
		_FPSFrameCount = 0.0f;
		//FPS시간 변수도 초기화
		_FPSTimeElapsed = 0.0f;
	}

}

float cTimer::GetWorldCheck(void)
{
	return 0.0f;
}
