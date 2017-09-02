#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
private:
	//하드웨어 타이머 사용가능 여부
	bool	_isHardware;
	//한번 업데이트할때마다 걸린 시간 간격.
	float	_timeElapsed;
	//1초/업데이트되는 횟수
	float	_timeScale;

	//현재 시간
	__int64	_curTime;
	//이전 시간
	__int64 _lastTime;
	//정밀 타이머 간격
	__int64 _periodFrequency;

	//1초마다 프레임 카운트를 저장
	unsigned long _frameRate;
	//프레임마다 카운트를 1씩 증가
	unsigned long _FPSFrameCount;


public:


	//싱글톤 생성
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

private:
	cTimer(void);
	virtual ~cTimer(void);

};

