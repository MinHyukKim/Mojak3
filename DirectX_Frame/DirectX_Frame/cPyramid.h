#pragma once

class cPyramid : public cObject
{
private:
	vector<ST_PN_VERTEX>	m_vecVertex;
	D3DMATERIAL9			m_stMtl;
	D3DXMATRIXA16			m_matWorld;

public:
	cPyramid(void);
	~cPyramid(void);
	
	void Setup(D3DXMATRIX* pmat, D3DCOLOR c);
	void Render();
};

