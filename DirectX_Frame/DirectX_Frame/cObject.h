#pragma once

class cObject
{
private:
	int m_nReferenceCount;

public:
// 현재 레퍼런스값을 반환합니다. (자신을 관리하고 있는 횟수를 저장합니다.)
	virtual int GetReferenceCount(void) final { return m_nReferenceCount; }

// Release()를 오버로딩시 함수안에서 이 함수를 호출해 주세요.
	virtual void Release(void) final;		// Delete 대신 사용

// 이 함수는 오버로딩 하실 수 없습니다. (오토릴리즈풀 리스트에 this를 추가합니다.)	
	virtual cObject* AutoRelease(void) final;


// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cObject* Create(void);		// *외부 생성자
// 이 함수를 호출후 반드시 Release 해주세요.
	virtual cObject* AddRef(void);
protected:							// 상속받을수 있지만 생성할 수 없습니다.
	cObject(void);					//생성자 은닉
	virtual ~cObject(void);			//소멸자 은닉
};

