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
	LPD3DXFRAME GetRootFrame(void) { return (LPD3DXFRAME)m_pRootFrame; }

	D3DXVECTOR3 getPosition() { return m_vPosition; };
	void setPosition(D3DXVECTOR3 value) { m_vPosition = value; };

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);
	void SetBlendingAnimation(int nAnimationKey, float fTravalTime = 0.1f);

	DWORD AddAnimationSet(LPD3DXANIMATIONSET pAnimation);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimController; }
	void SetRandomTrackPosition();
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame, D3DXMATRIX* pPMat);


	static void SetTextureDiffuse(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pDiffuse);
	static void SetTextureAmbient(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pAmbient);
	static void SetTextureColor(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pColor);
	static void SetTextureChange(LPD3DXFRAME pRoot, LPCSTR szPrevTextureName, LPCSTR szNextTextureName);

	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);

private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void ShaderRender(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
	static HRESULT CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin);

};