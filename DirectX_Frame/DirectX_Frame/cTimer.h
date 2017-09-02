#pragma once
#define g_pTimer cTimer::GetInstance()


class cTimer
{
private:
	//하드웨어 타이머 사용가능 여부
	bool	_isHardware;

public:
	cTimer();
	~cTimer();

	//싱글톤 생성
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

