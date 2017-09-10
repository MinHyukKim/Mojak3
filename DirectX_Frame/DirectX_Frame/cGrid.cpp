#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
{
}

cGrid::~cGrid(void)
{
	for each(auto p in m_vecPyramid)
	{
		SAFE_RELEASE(p);
	}
}

void cGrid::Setup( int nNumLine, float fInterval )
{
	int nHalfNumLine = nNumLine / 2;

	float fMax = fabs(nHalfNumLine * fInterval);

	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
	for (int i = 1; i <= nHalfNumLine; ++i)
	{
		if( i % 5 == 0 )
			c = D3DCOLOR_XRGB(255, 255, 255);
		else 
			c = D3DCOLOR_XRGB(155, 155, 155);

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0,  i * fInterval), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0,  i * fInterval), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, -i * fInterval), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0, -i * fInterval), c));
		
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( i * fInterval, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( i * fInterval, 0,  fMax), c));
		
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fInterval, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fInterval, 0,  fMax), c));
	}

	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0, 0), c));

	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0,-fMax, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, fMax, 0), c));

	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0,-fMax), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, fMax), c));

	D3DXMATRIX matS, matR, mat;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	
	cPyramid* pPyramid = cPyramid::Create();
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(&mat, D3DCOLOR_XRGB(255, 0, 0));
	m_vecPyramid.push_back(pPyramid);

	pPyramid = cPyramid::Create();
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	mat = matS * matR;
	pPyramid->Setup(&mat, D3DCOLOR_XRGB(0, 255, 0));
	m_vecPyramid.push_back(pPyramid);

	pPyramid = cPyramid::Create();
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(&mat, D3DCOLOR_XRGB(0, 0, 255));
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	DWORD dwPrev;
	g_pD3DDevice->GetRenderState(D3DRS_LIGHTING, &dwPrev);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, (bool)dwPrev);
}

cGrid* cGrid::Create(void)
{
	cGrid* newClass = new cGrid;
	newClass->AddRef();
	return newClass;
}
