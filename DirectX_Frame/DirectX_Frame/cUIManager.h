#pragma once

#define g_pUImanager cUImanager:::GetInstance()

class cUImanager
{
private:


public:

	//�̱��� ����
	static cUImanager* GetInstance(void) { static cUImanager instance; return &instance; }

private:
	cUImanager(void);
	virtual ~cUImanager(void);
};