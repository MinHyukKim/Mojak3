#pragma once

#define g_pInputManager cInputManager::GetInstance()
#define KEYMAX 256

class cInputManager
{
private:
	std::bitset<KEYMAX> m_isKeyUp;
	std::bitset<KEYMAX> m_isKeyDown;
	POINT m_ptMouseCurrent;
	POINT m_ptMouseMove;

public:
	void MouseUpdate(void);

	int GetMousePositionX(void) { return m_ptMouseCurrent.x; }
	int GetMousePositionY(void) { return m_ptMouseCurrent.y; }
	int GetMouseMovingX(void) { return m_ptMouseMove.x; }
	int GetMouseMovingY(void) { return m_ptMouseMove.y; }
	bool IsOnceKeyDown(const int nKey);		//�ѹ��� Ȯ�� ���� �մϴ�
	bool IsOnceKeyUp(const int nKey);		//�ѹ��� Ȯ�� ���� �մϴ�
	bool IsStayKeyDown(const int nKey);
	bool IsToggleKey(const int nKey);

	//�ζ��� �Լ���
	std::bitset<KEYMAX> GetKeyUp() { return m_isKeyUp; }
	std::bitset<KEYMAX> GetKeyDown() { return m_isKeyDown; }
	void SetKeyDown(int nKey, bool isState) { m_isKeyDown.set(nKey, isState); }
	void SetKeyUp(int nKey, bool isState) { m_isKeyUp.set(nKey, isState); }

	//�̱��� ����
	static cInputManager* GetInstance(void) { static cInputManager instance; return &instance; }

private:
	cInputManager(void);
	virtual ~cInputManager(void);
};