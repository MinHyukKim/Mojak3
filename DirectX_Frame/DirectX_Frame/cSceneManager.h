#pragma once
class cSceneManager
{
private:

public:


	//�̱��� ����
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }

private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

