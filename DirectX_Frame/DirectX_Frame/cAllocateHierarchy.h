#pragma once

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;

	ST_BONE(void) : D3DXFRAME({})
	{
		D3DXMatrixIdentity(&TransformationMatrix);
		D3DXMatrixIdentity(&CombinedTransformationMatrix);
	}
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	//형상
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
	LPD3DXMESH pWorkingMesh;
	//애니메이션
	D3DXMATRIXA16**			ppBoneMatrixPtrs;
	D3DXMATRIXA16*			pBoneOffsetMatrices;
	//셰이더
	LPD3DXBUFFER			pBufBoneCombos;
	DWORD					dwNumPaletteEntries;
	DWORD					dwMaxNumFaceInfls;
	DWORD					dwNumAttrGroups;

	ST_BONE_MESH(void) : D3DXMESHCONTAINER({}), pWorkingMesh(nullptr), ppBoneMatrixPtrs(nullptr), pBoneOffsetMatrices(nullptr)
		, pBufBoneCombos(nullptr), dwNumPaletteEntries(0), dwMaxNumFaceInfls(0), dwNumAttrGroups(0)
	{
	}
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
private:
	DWORD m_dwDefaultPalette;
	DWORD m_dwNumMaxPalette;

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name, CONST D3DXMESHDATA *pMeshData, CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;

	static HRESULT CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin);

	cAllocateHierarchy(void);
	virtual ~cAllocateHierarchy(void);
};

