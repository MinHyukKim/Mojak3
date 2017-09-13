#pragma once

class cQuadTree;
class cMapTerrain : public cObject
{
private:
	std::vector<D3DXMATERIAL> m_vecMaterals;
	std::vector<LPDIRECT3DTEXTURE9> m_vecTextures;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBufer;
	ST_PNT_VERTEX* m_pHeightMap;
	cQuadTree* m_pQuadTree;

	D3DXVECTOR3 m_vScale;
	DWORD m_dwCol, m_dwRow;
	DWORD m_dwTriangles;


public:
	HRESULT Setup(LPCSTR szHeightMapName, D3DXMATERIAL* pMaterial, LPD3DXVECTOR3 pScale = &D3DXVECTOR3(1.0f, 16.0f, 1.0f));
	void Update(void) override;
	void Render(void) override;
	
	//버텍스 포인터
	ST_PNT_VERTEX* GetVertex(DWORD dwX, DWORD dwZ) { return &m_pHeightMap[dwX + dwZ * m_dwCol]; }
	//버텍스 높이
	float GetHeight(DWORD dwX, DWORD dwZ) { return m_pHeightMap[dwX + dwZ * m_dwCol].p.y; }
	//버텍스갯수 (가로)
	DWORD GetCol(void) { return m_dwCol; }
	//버텍스갯수 (세로)
	DWORD GetRow(void) { return m_dwRow; }
	//맵크기 x
	float GetTerrainCol(void) { return (float)m_dwCol * m_vScale.x; }
	//맵크기 z
	float GetTerrainRow(void) { return (float)m_dwRow * m_vScale.z; }

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

