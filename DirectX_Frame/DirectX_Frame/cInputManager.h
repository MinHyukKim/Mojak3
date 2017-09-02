#pragma once

#define g_pInputManager cInputManager::GetInstance()
#define KEYMAX 256

class cInputManager
{
private:
	std::bitset<KEYMAX> m_isKeyUp;
	std::bitset<KEYMAX> m_isKeyDown;

public:
	bool IsOnceKeyDown(const int nKey);
	bool IsOnceKeyUp(const int nKey);
	bool IsStayKeyDown(const int nKey);
	bool IsToggleKey(const int nKey);

	//인라인 함수들
	std::bitset<KEYMAX> GetKeyUp() { return m_isKeyUp; }
	std::bitset<KEYMAX> GetKeyDown() { return m_isKeyDown; }
	void SetKeyDown(int nKey, bool isState) { m_isKeyDown.set(nKey, isState); }
	void SetKeyUp(int nKey, bool isState) { m_isKeyUp.set(nKey, isState); }

	//싱글톤 생성
	static cInputManager* GetInstance(void) { static cInputManager instance; return &instance; }

private:
	cInputManager(void);
	virtual ~cInputManager(void);
};