#include "stdafx.h"
#include "cTile.h"

cTile::cTile(void)
	: m_vPosition(0.0f, 0.0f, 0.0f)
	, m_dwNumTexture(0)
	, m_dwData(0)
{
}

cTile::cTile(D3DXVECTOR3 & vPosition, DWORD dwNumTexture, DWORD dwData)
	: m_vPosition(vPosition)
	, m_dwNumTexture(dwNumTexture)
	, m_dwData(dwData)
{
}

cTile::~cTile(void)
{
}


