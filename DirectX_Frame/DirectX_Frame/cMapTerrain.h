#pragma once

class cQuadTree;
class cMapTerrain : public cObject
{
private:
	std::vector<D3DXMATERIAL> m_vecMaterals;
	std::vector<LPDIRECT3DTEXTURE9> m_vecTextures;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBufer;
	std::vector<ST_PNT_VERTEX> m_vecPosition;
	std::vector<DWORD> m_vecIndex;
	cQuadTree* m_pQuadTree;

	D3DXVECTOR3 m_vScale;
	DWORD m_dwCol, m_dwRow;
	DWORD m_dwTriangles;
	float m_fMaxTerrainX;
	float m_fMaxTerrainZ;


public:
	HRESULT Setup(IN LPCSTR szHeightMapName, IN D3DXMATERIAL* pMaterial, IN LPD3DXVECTOR3 pScale = &D3DXVECTOR3(1.0f, 16.0f, 1.0f));
	void Update(void) override;
	void Render(void) override;
	
	//버텍스 포인터
	ST_PNT_VERTEX* GetVertex(IN DWORD dwX, IN DWORD dwZ) { return &m_vecPosition[dwX + dwZ * m_dwCol]; }
	//버텍스 높이
	//float GetHeight(IN DWORD dwX, IN DWORD dwZ) { return m_vecPosition[dwX + dwZ * m_dwCol].p.y; }
	bool GetHeight(OUT float* fY, IN float fX, IN float fZ);
	//버텍스갯수 (가로)
	DWORD GetCol(void) { return m_dwCol; }
	//버텍스갯수 (세로)
	DWORD GetRow(void) { return m_dwRow; }
	//맵크기 x
	float GetTerrainCol(void) { return m_fMaxTerrainX; }
	//맵크기 z
	float GetTerrainRow(void) { return m_fMaxTerrainZ; }

	bool IsCollision(OUT LPD3DXVECTOR3 pPos, IN LPD3DXVECTOR3 pOrg, IN LPD3DXVECTOR3 pDir);

	static cMapTerrain* Create(void);
protected:
	cMapTerrain(void);
	virtual ~cMapTerrain(void);

private:
	//메모리 제거
	inline HRESULT _Destroy(void);
	//텍스쳐 로드
	inline HRESULT _LoadTexture(D3DXMATERIAL* pMaterial);
	//높이맵 생성
	inline HRESULT _BuildHeightMap(LPCSTR szMapName);
	//평지맵 생성
	inline HRESULT _BuildHeightMap(DWORD dwCol, DWORD dwRow);
	//쿼드트리 생성
	inline HRESULT _BuilldQuadTree(void);
	//버텍스 버퍼 생성
	inline HRESULT _CreateVertexBuffer(void);
	//인덱스 버퍼 생성
	inline HRESULT _CreateIndexBuffer(void);
	//출력
	inline HRESULT _Draw(void);

};

