#include "stdafx.h"
#include "cInputManager.h"

cInputManager::cInputManager(void)
	: m_nWheel1(0)
	, m_nWheel2(0)
	, m_ptMouseMove({})
{
	GetCursorPos(&m_ptMouseCurrent);
	ScreenToClient(g_hWnd, &m_ptMouseCurrent);

	for (int i = 0; i < KEYMAX; i++)
	{
		this->SetKeyUp(i, false);
		this->SetKeyDown(i, false);
	}
}

cInputManager::~cInputManager(void)
{
}

void cInputManager::Update(void)
{
	this->MouseUpdate();
}

void cInputManager::MouseUpdate(void)
{
	m_ptMouseMove = m_ptMouseCurrent;				//���� ��ǥ ����

	GetCursorPos(&m_ptMouseCurrent);				//���콺 ��ǥ(�ɹ����� ������)
	ScreenToClient(g_hWnd, &m_ptMouseCurrent);		//���콺 ��ǥ(�ɹ����� ������)

	m_ptMouseMove.x = (m_ptMouseCurrent.x - m_ptMouseMove.x); //���� ��ǥ - ���� ��ǥ (������ ��)
	m_ptMouseMove.y = (m_ptMouseCurrent.y - m_ptMouseMove.y); //���� ��ǥ - ���� ��ǥ (������ ��)

	//��
	m_nWheel2 = m_nWheel1;
	m_nWheel1 = 0;
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
