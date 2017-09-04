#pragma once
class cSceneManager
{
private:

public:


	//½Ì±ÛÅæ »ı¼º
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }

private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

