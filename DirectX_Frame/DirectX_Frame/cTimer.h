#pragma once
class cTimer
{
public:
	cTimer();
	~cTimer();

	//½Ì±ÛÅæ »ý¼º
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

