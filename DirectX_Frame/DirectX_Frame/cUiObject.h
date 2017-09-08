#pragma once
#include "cObject.h"

class cUiObject : public cObject
{
private:

protected:
	vector<cUiObject*>	m_vecChild;		//�ڽ�
	D3DXVECTOR3			m_vPos;			//�����ġ
	cUiObject*			m_pParent;		//�θ�?
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


	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUiObject* Create(void);		//�޸𸮰����� ������ 
protected:
	cUiObject(void);
	virtual ~cUiObject(void);
};