#pragma once

class cObject
{
private:
	int m_nReferenceCount;
	
//0903추가 11 : 12 추가
	cObject*				m_pParent;
	std::vector<cObject*>	m_vecChild;

public:
// 현재 레퍼런스값을 반환합니다. (자신을 관리하고 있는 횟수를 저장합니다.)
	virtual int GetReferenceCount(void) { return m_nReferenceCount; }

// 이 함수를 호출후 반드시 Release 해주세요.
	virtual void AddRef(void) { ++m_nReferenceCount; }

// Release()를 오버로딩시 함수안에서 이 함수를 호출해 주세요.
	virtual void Release(void);		// Delete 대신 사용

// 이 함수는 오버로딩 하실 수 없습니다. (오토릴리즈풀 리스트에 this를 추가합니다.)	
	virtual cObject* AutoRelease(void);

	virtual HRESULT Setup(void);

	//0903 11:12추가 내부구현 안되있습니다
	virtual HRESULT Setup(D3DXVECTOR3* pvTarget = NULL);
	virtual void Update(void);
	virtual void Render(void);
	//virtual void SetupChild(void) final;
	//virtual void UpdateChild(void) final;
	//virtual void RenderChild(void) final;
	//virtual void RelaseChild(void) final;
	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cObject* Create(void);	//메모리관리용 생성자 
protected:							//상속받을수 있지만 생성할 수 없습니다.
	cObject(void);					//생성자 은닉
	virtual ~cObject(void);			//소멸자 은닉
};

