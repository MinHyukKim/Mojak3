#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
{
}

cPyramid::~cPyramid(void)
{
	int a = 0;
}

void cPyramid::Setup(D3DXMATRIX* pmat, D3DCOLOR c)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = m_stMtl.Diffuse = m_stMtl.Specular = D3DXCOLOR(c);

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 0, 0, 0)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1,-1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1,-1)));

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 0, 0, 0)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1, 1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1,-1)));

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 0, 0, 0)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1, 1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1, 1)));

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 0, 0, 0)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1,-1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1, 1)));

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1, 1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1,-1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1,-1)));

	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3(-1,-1, 1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1,-1)));
	m_vecVertex.push_back(ST_PN_VERTEX(D3DXVECTOR3( 1,-1, 1)));

	if(pmat)
	{
		for (size_t i = 0; i < m_vecVertex.size(); ++i)
		{
			D3DXVec3TransformCoord(&m_vecVertex[i].position,
				&m_vecVertex[i].position,
				pmat);
		}
	}

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i].position;
		D3DXVECTOR3 v1 = m_vecVertex[i + 1].position;
		D3DXVECTOR3 v2 = m_vecVertex[i + 2].position;
		D3DXVECTOR3 v01 = v1 - v0;
		D3DXVECTOR3 v02 = v2 - v0;
		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);
		m_vecVertex[i].normal = m_vecVertex[i + 1].normal = m_vecVertex[i + 2].normal = n;
	}
	D3DXMatrixIdentity(&m_matWorld);
}

void cPyramid::Render()
{
	g_pD3DDevice->SetMaterial(&m_stMtl);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}
