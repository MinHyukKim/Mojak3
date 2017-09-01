#pragma once
#include "GameNode.h"

typedef class Timer : public GameNode
{
private:
	bool	_isHardware;
	float	_timeElapsed;
	float	_timeScale;

	__int64	_curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;
	float _lockFPS;
public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);

	void SetLockFPS(float lockFPS) { _lockFPS = lockFPS; }

	unsigned long GetFPS(TCHAR* str = NULL) const;

	Timer(void);
	virtual ~Timer(void);

}_Timer, *LPTIMER;

