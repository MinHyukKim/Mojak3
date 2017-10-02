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
	void HalfClone(void);
	void HalfDestroy(void);

	LPD3DXFRAME GetRootFrame(void) { return (LPD3DXFRAME)m_pRootFrame; }

	D3DXVECTOR3 getPosition() { return m_vPosition; };
	void setPosition(D3DXVECTOR3 value) { m_vPosition = value; };

	void UpdateAndRender();
	void UpdateAndRender(LPD3DXMATRIX pMatrix);
	void SetAnimationIndex(int nIndex);
	void SetBlendingAnimation(int nAnimationKey, float fTravelTime = 0.1f);

	bool FrameClone(OUT LPD3DXFRAME* ppClone, IN LPD3DXFRAME pOrigin);
	DWORD AddAnimationSet(LPD3DXANIMATIONSET pAnimation);
	void SetAnimationController(LPD3DXANIMATIONCONTROLLER pAnimationController);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimController; }
	void SetRandomTrackPosition();

	void UpdateSkinnedMesh(LPD3DXFRAME pFrame, D3DXMATRIX* pPMat);
	void FrameChange(LPD3DXFRAME pFrame);
	void SetTrack(bool ibTrack) { m_isCurrentTrack = ibTrack; }
	void SetTextureColor(LPCSTR szTextureName, LPD3DXCOLOR pColor);
	void SetTextureColor(LPCSTR szTextureName, D3DMATERIAL9* pMaterial);
	void SetTextureDiffuse(LPCSTR szTextureName, LPD3DXCOLOR pDiffuse);
	void SetTextureAmbient(LPCSTR szTextureName, LPD3DXCOLOR pAmbient);
	void SetTextureSpecular(LPCSTR szTextureName, LPD3DXCOLOR pSpecular);
	void SetTextureChange(LPCSTR szPrevTextureName, LPCSTR szNextTextureName);


	static void SetTextureDiffuse(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pDiffuse);
	static void SetTextureAmbient(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pAmbient);
	static void SetTextureSpecular(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pSpecular);
	static void SetTextureColor(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pColor);
	static void SetTextureColor(LPD3DXFRAME pRoot, LPCSTR szTextureName, D3DMATERIAL9* pMaterial);
	static void SetTextureChange(LPD3DXFRAME pRoot, LPCSTR szPrevTextureName, LPCSTR szNextTextureName);
	static void AddTexture(LPD3DXFRAME pRoot, LPCSTR szFrameName, LPCSTR szTextureName);

	cSkinnedMesh(char* szFolder, char* szFilename);
	cSkinnedMesh(cSkinnedMesh* pSkinnedMesh);
	virtual ~cSkinnedMesh(void);

private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void _Update(ST_BONE* pCurrent, D3DXMATRIX* pmatParent);
	void _Render(ST_BONE* pBone = NULL);
	void ShaderRender(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void _HalfClone(LPD3DXFRAME* ppRoot);
	void _HalfDestroy(LPD3DXFRAME* ppRoot);
	void Destroy();
	static HRESULT CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin);

};