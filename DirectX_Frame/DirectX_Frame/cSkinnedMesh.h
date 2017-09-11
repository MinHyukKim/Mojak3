#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//�ϳ��� ����
	ST_BONE*			m_pRootFrame;
	DWORD				m_dwWorkingPaletteSize;
	D3DXMATRIX*			m_pmWorkingPalette;
	LPD3DXEFFECT		m_pEffect;

	int					m_nAnimationKey;
	bool				m_isCurrentTrack;

	//��ü���� ����
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	D3DXVECTOR3 m_vPosition;
	//SYNTHESIZE(ST_SPHERE, m_stSphere, BoundingSphere);


public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);

	D3DXVECTOR3 getPosition() { return m_vPosition; };
	void setPosition(D3DXVECTOR3 value) { m_vPosition = value; };

private:
	cSkinnedMesh();
};