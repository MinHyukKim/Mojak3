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
	int m_nWheel1;	//메시지 루프에서 받아온 파라미터(프레임 제한없음)
	int m_nWheel2;	//업데이트 루프에서 사용할 파라미터(DirectX 고정프레임)

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

	bool IsOnceKeyDown(const int nKey);		//한번만 확인 가능 합니다
	bool IsOnceKeyUp(const int nKey);		//한번만 확인 가능 합니다
	bool IsStayKeyDown(const int nKey);
	bool IsToggleKey(const int nKey);

	//마우스 휠 인식 (프로시져에 사용)
	void OffsetWheel(int nOffset) { m_nWheel1 += nOffset; }
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