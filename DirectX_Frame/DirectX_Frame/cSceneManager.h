#pragma once
#include "cSceneObject.h"

class cSceneManager : public cSceneObject
{
private:

public:


	//�̱��� ����
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }

private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

