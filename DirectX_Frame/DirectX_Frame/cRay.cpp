#include "stdafx.h"
#include "cRay.h"

cRay::cRay(void)
{
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

	vDir->x = (((2.0f * (float)ptScreen->x) / (float)vp.Width) - 1.0f) / matProj._11;
	vDir->y = (1.0f - ((2.0f * (float)ptScreen->y) / (float)vp.Height)) / matProj._22;
	vDir->z = 1.0f;
}

void cRay::RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir, IN LPPOINT ptScreen)
{
	this->RayAtViewSpace(vDir, ptScreen);

	D3DXMATRIXA16 matView, matInverseView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInverseView, nullptr, &matView);

	D3DXVec3TransformCoord(vPos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &matInverseView);
	D3DXVec3TransformNormal(vDir, vDir, &matInverseView);
	D3DXVec3Normalize(vDir, vDir);
}

void cRay::RayAtWorldSpace(OUT LPD3DXVECTOR3 vPos, OUT LPD3DXVECTOR3 vDir)
{
	POINT ptPoint;
	GetCursorPos(&ptPoint);
	ScreenToClient(g_hWnd, &ptPoint);

	this->RayAtWorldSpace(vPos, vDir, &ptPoint);
}
