#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//하나만 생성
	ST_BONE*			m_pRootFrame;
	DWORD				m_dwWorkingPaletteSize;
	D3DXMATRIX*			m_pmWorkingPalette;
	LPD3DXEFFECT		m_pEffect;

	int					m_nAnimationKey;
	bool				m_isCurrentTrack;




public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);

private:
	cSkinnedMesh();
};