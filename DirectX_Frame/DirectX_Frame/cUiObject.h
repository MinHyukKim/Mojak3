#pragma once
#include "cObject.h"

class cUiObject : public cObject
{
private:

protected:
	vector<cUiObject*>	m_vecChild;		//자식
	D3DXVECTOR2			m_vPos;			//상대위치

public:
	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUiObject* Create(void);		//메모리관리용 생성자 
protected:
	cUiObject(void);
	virtual ~cUiObject(void);
};