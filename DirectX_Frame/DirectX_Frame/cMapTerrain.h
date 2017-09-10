#pragma once

class cQuadTree;
class cMapTerrain : public cObject
{
private:
	std::vector<LPDIRECT3DTEXTURE9> m_vecTexture;
	std::vector<ST_PNT_VERTEX> m_vecMapVertex;
	D3DXVECTOR3 m_vScale;
	DWORD m_dwCol, m_dwRow;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBufer;
	cQuadTree* m_pQuadTree;

public:
	HRESULT Setup(void) override;
	void Update(void) override;
	void Render(void) override;

	static cMapTerrain* Create(void);
protected:
	cMapTerrain(void);
	virtual ~cMapTerrain(void);

private:
	//臭捞甘 积己
	inline HRESULT _BuildHeightMap(LPCSTR szMapName);
	//乞瘤甘 积己
	inline HRESULT _BuildHeightMap(DWORD dwCol, DWORD dwRow);
};

