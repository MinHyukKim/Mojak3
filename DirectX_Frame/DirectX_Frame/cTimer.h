#pragma once
class cTimer
{
public:
	cTimer();
	~cTimer();

	//�̱��� ����
	static cTimer* GetInstance() { static cTimer instance; return &instance; }

};

