#pragma once
#include "cObject.h"

class cUiObject : public cObject
{
private:

protected:
	vector<cUiObject*>	m_vecChild;		//�ڽ�
	D3DXVECTOR3			m_vPosition;			//�����ġ
	cUiObject*			m_pParent;		//�θ�?
	D3DXMATRIX			m_matWorld;		//���� ��Ʈ����
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	//���� �̱���
	virtual void AddChild(cUiObject* pChild);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void SetPosition(float x, float y);
	virtual void GetRect(RECT* pRect);
	virtual cUiObject* GetChildByTag(int nTag);


	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUiObject* Create(void);		//�޸𸮰����� ������ 
protected:
	cUiObject(void);
	virtual ~cUiObject(void);
};