#pragma once
#include "cObject.h"

class cSceneObject : public cObject
{
private:

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void);					//릴리즈 대용
	virtual void Update(void) override;
	virtual void Render(void) override;	

	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cSceneObject* Create(void);		//메모리관리용 생성자 
protected:									//상속받을수 있지만 생성할 수 없습니다.
	cSceneObject(void);						//생성자 은닉
	virtual ~cSceneObject(void);			//소멸자 은닉
};
