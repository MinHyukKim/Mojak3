#include "stdafx.h"
#include "cInputManager.h"

cInputManager::cInputManager(void)
{

}

cInputManager::~cInputManager(void)
{
}

bool cInputManager::IsOnceKeyDown(const int nKey)
{
	return false;
}

bool cInputManager::IsOnceKeyUp(const int nKey)
{
	return false;
}

bool cInputManager::IsStayKeyDown(const int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000)
	{
		if (!this->GetKeyDown()[nKey])
		{
			this->SetKeyDown(nKey, true);
			return true;
		}
	}
	else this->SetKeyDown(nKey, false);
	return false;
}

bool cInputManager::IsToggleKey(const int nKey)
{
	return false;
}
