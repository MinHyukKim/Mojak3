#pragma once

#define MAX 1024

class cHeightMapLoader
{
private:
	LPD3DXMESH				m_pMesh;
	std::string				m_sTexture;
	D3DMATERIAL9			m_stMtl;
	int						m_nTile;
	vector<D3DXVECTOR3>		m_vecVertex;

public:
	virtual void Load(char* szFolder, char* szFile, 
		char* szTexture,
		DWORD dwBytesPerPixel = 1);
	virtual bool GetHeight(IN float x, OUT float& y, IN float z);
	virtual void Render();

	cHeightMapLoader(void);
	virtual ~cHeightMapLoader(void);
};