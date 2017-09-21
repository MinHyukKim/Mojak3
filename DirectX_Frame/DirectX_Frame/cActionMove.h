#pragma once
#include "cAction.h"

class cActionMove : public cAction
{
private:
	D3DXVECTOR3 m_vFrom;
	D3DXVECTOR3 m_vTo;

public:
	virtual void Play(void) override;
	virtual void Update(void) override;

	virtual void SetFrom(D3DXVECTOR3& vFrom)  final { m_vFrom = vFrom; }
	virtual D3DXVECTOR3& GetFrom(void) final { return m_vFrom; }
	virtual void SetTo(D3DXVECTOR3& vTo) final { m_vTo = vTo; }
	virtual D3DXVECTOR3& GetTo(void) final { return m_vTo; }
	virtual D3DXVECTOR3 GetDirection(void) final { return m_vTo - m_vFrom; };

//	virtual cActionMove* AddRef(void) override;
	static cActionMove* Create(void);
protected:
	cActionMove(void);
	virtual ~cActionMove(void);
};

