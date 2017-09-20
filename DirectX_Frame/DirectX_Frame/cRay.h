#pragma once

#define g_pRay cRay::GetInstance()

class cRay
{
private:
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matInverseView;
public:
	void RayAtViewSpace(OUT LPD3DXVECTOR3 vDir, IN LPPOINT ptScreen);
	void RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir, IN LPPOINT ptScreen);
	void RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir);

	static cRay* GetInstance(void) { cRay instance;  return &instance; }
private:
	cRay(void);
	virtual ~cRay(void);
};

