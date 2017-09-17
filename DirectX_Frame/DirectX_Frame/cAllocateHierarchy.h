#pragma once

#define g_pAllocateHierarchy cAllocateHierarchy::GetInstance()

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
private:
	DWORD m_dwDefaultPalette;
	DWORD m_dwNumMaxPalette;
	std::string m_sFolder;


public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name, CONST D3DXMESHDATA *pMeshData, CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;

	//HRESULT CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin);
	HRESULT CloneFrame(OUT LPD3DXFRAME* ppClone, IN LPD3DXFRAME pOrigin);
	bool ChangeFrame(LPD3DXFRAME* ppRoot, LPD3DXFRAME pOrigin);
	HRESULT CloneHierarchy(OUT LPD3DXFRAME * ppRoot, IN LPD3DXFRAME pOrigin);

	void setDefaultPaletteSize(DWORD value) { m_dwDefaultPalette = value; };
	DWORD getDefaultPaletteSize() { return m_dwDefaultPalette; }

	void setMaxPaletteSize(DWORD value) { m_dwNumMaxPalette = value; };
	DWORD getMaxPaletteSize() { return m_dwNumMaxPalette; };

	void setFolder(std::string value) { m_sFolder = value; };
	std::string getFolder() { return m_sFolder; };
	
	void Reset(void);

	static cAllocateHierarchy* GetInstance(void) { static cAllocateHierarchy instance; return &instance; }
private:
	cAllocateHierarchy(void);
	virtual ~cAllocateHierarchy(void);
};

