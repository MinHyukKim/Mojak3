#include "stdafx.h"
#include "cInputManager.h"

cInputManager::cInputManager(void)
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->SetKeyUp(i, false);
		this->SetKeyDown(i, false);
	}
}

cInputManager::~cInputManager(void)
{
}

void cInputManager::MouseUpdate(void)
{
	m_ptMouseMove = m_ptMouseCurrent;				//이전 좌표 저장

	GetCursorPos(&m_ptMouseCurrent);				//마우스 좌표(맴버변수 포인터)
	ScreenToClient(g_hWnd, &m_ptMouseCurrent);		//마우스 좌표(맴버변수 포인터)

	m_ptMouseMove.x = (m_ptMouseCurrent.x - m_ptMouseMove.x); //현재 좌표 - 이전 좌표 (음직인 양)
	m_ptMouseMove.y = (m_ptMouseCurrent.y - m_ptMouseMove.y); //현재 좌표 - 이전 좌표 (음직인 양)
}

bool cInputManager::IsOnceKeyDown(const int nKey)
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

bool cInputManager::IsOnceKeyUp(const int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000) this->SetKeyUp(nKey, true);
	else
	{
		if (this->GetKeyUp()[nKey])
		{
			this->SetKeyUp(nKey, false);
			return true;
		}
	}
	return false;
}

bool cInputManager::IsStayKeyDown(const int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000) return true;
	return false;
}

bool cInputManager::IsToggleKey(const int nKey)
{
	if (GetKeyState(nKey) & 0x0001) return true;
	return false;
}
