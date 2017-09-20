#include "stdafx.h"
#include "cRay.h"

cRay::cRay(void)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matInverseView);
}

cRay::~cRay(void)
{
}

void cRay::RayAtViewSpace(OUT LPD3DXVECTOR3 vDir, IN LPPOINT ptScreen)
{
	if (!vDir) return;
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	vDir->x = ((2.0f * (*ptScreen).x) / vp.Width - 1) / matProj._11;
	vDir->y = ((-2.0f * (*ptScreen).y) / vp.Height + 1) / matProj._22;
	vDir->z = 1.0f;
}

void cRay::RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir, IN LPPOINT ptScreen)
{
	if (!vPos || !vDir) return;
	this->RayAtViewSpace(vDir, ptScreen);

	D3DXMATRIXA16 matView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	if (m_matView != matView)
	{
		m_matView = matView;
		D3DXMatrixInverse(&m_matInverseView, 0, &matView);
	}

	D3DXVec3TransformCoord(vPos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &m_matInverseView);
	D3DXVec3TransformNormal(vDir, vDir, &m_matInverseView);
}

void cRay::RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	this->RayAtWorldSpace(vPos, vDir, &pt);
}
