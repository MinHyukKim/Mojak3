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

	//객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	D3DXVECTOR3 m_vPosition;
	//SYNTHESIZE(ST_SPHERE, m_stSphere, BoundingSphere);


public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);

	D3DXVECTOR3 getPosition() { return m_vPosition; };
	void setPosition(D3DXVECTOR3 value) { m_vPosition = value; };

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);
	void SetBlendingAnimation(int nAnimationKey, float fTravalTime = 0.1f);


	void SetRandomTrackPosition();
	//컬러값 변경 임시
	void SetColorChild(LPD3DXFRAME pFrame, D3DXCOLOR & stColor);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame, D3DXMATRIX* pPMat);

	//SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);


private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();

};