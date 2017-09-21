#pragma once
#include "cAction.h"

class cActionMove : public cAction
{
private:
	D3DXVECTOR3 m_vFrom;
	D3DXVECTOR3 m_vTo;
	D3DXVECTOR3 m_vDir;

public:
	virtual void Play(void) override;
	virtual void Stop(void) override;
	virtual void Update(void) override;

	void SetFrom(D3DXVECTOR3& vFrom) { m_vFrom = vFrom; }
	D3DXVECTOR3& GetFrom(void) { return m_vFrom; }
	void SetTo(D3DXVECTOR3& vTo) { m_vTo = vTo; }
	D3DXVECTOR3& GetTo(void) { return m_vTo; }
	D3DXVECTOR3 GetDirection(void) { return m_vDir; };
	void SetToPlay(IN LPD3DXVECTOR3 vTo, IN float fSpeed);

	static cActionMove* Create(void);
protected:
	cActionMove(void);
	virtual ~cActionMove(void);
};

