#pragma once
#include "cObject.h"

class cUiObject : public cObject
{
private:

protected:
	vector<cUiObject*>	m_vecChild;		//자식
	D3DXVECTOR3			m_vPos;			//상대위치
	cUiObject*			m_pParent;		//부모?
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	virtual HRESULT Setup(void) override;	
	virtual void Update(void) override;
	virtual void Render(void) override;
	void AddChild(cUiObject* pChild);
	void Render(LPD3DXSPRITE pSprite);
	void SetPosition(float x, float y);
	cUiObject* GetChildByTag(int nTag);


	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUiObject* Create(void);		//메모리관리용 생성자 
protected:
	cUiObject(void);
	virtual ~cUiObject(void);
};