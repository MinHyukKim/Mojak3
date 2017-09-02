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




public:
	cTimer();
	~cTimer();

	//싱글톤 생성
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

