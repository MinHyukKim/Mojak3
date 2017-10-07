#pragma once

#define g_pInputManager cInputManager::GetInstance()
#define KEYMAX 256

class cInputManager
{
private:
	std::bitset<KEYMAX> m_isKeyUp;
	std::bitset<KEYMAX> m_isKeyDown;
//	std::bitset<KEYMAX> m_isOnceKey;
	POINT m_ptMouseCurrent;
	POINT m_ptMouseMove;
	int m_nWheel1;	//�޽��� �������� �޾ƿ� �Ķ����(������ ���Ѿ���)
	int m_nWheel2;	//������Ʈ �������� ����� �Ķ����(DirectX ����������)

public:
	void Update(void);

	void MouseUpdate(void);

	POINT GetMousePosition(void) { return m_ptMouseCurrent; }
	int GetMousePositionX(void) { return m_ptMouseCurrent.x; }
	int GetMousePositionY(void) { return m_ptMouseCurrent.y; }
	POINT GetMouseMoving(void) { return m_ptMouseMove; }
	int GetMouseMovingX(void) { return m_ptMouseMove.x; }
	int GetMouseMovingY(void) { return m_ptMouseMove.y; }
	int GetMouseWheel(void) { return m_nWheel2; }

	bool IsOnceKeyDown(const int nKey);		//�ѹ��� Ȯ�� ���� �մϴ�
	bool IsOnceKeyUp(const int nKey);		//�ѹ��� Ȯ�� ���� �մϴ�
	bool IsStayKeyDown(const int nKey);
	bool IsToggleKey(const int nKey);

	//���콺 �� �ν� (���ν����� ���)
	void OffsetWheel(int nOffset) { m_nWheel1 += nOffset; }
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