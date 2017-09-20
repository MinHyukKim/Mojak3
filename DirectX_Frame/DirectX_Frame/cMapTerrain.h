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
	
	//���ؽ� ������
	ST_PNT_VERTEX* GetVertex(IN DWORD dwX, IN DWORD dwZ) { return &m_vecPosition[dwX + dwZ * m_dwCol]; }
	//���ؽ� ����
	//float GetHeight(IN DWORD dwX, IN DWORD dwZ) { return m_vecPosition[dwX + dwZ * m_dwCol].p.y; }
	bool GetHeight(OUT float* fY, IN float fX, IN float fZ);
	//���ؽ����� (����)
	DWORD GetCol(void) { return m_dwCol; }
	//���ؽ����� (����)
	DWORD GetRow(void) { return m_dwRow; }
	//��ũ�� x
	float GetTerrainCol(void) { return m_fMaxTerrainX; }
	//��ũ�� z
	float GetTerrainRow(void) { return m_fMaxTerrainZ; }

	bool IsCollision(OUT LPD3DXVECTOR3 pPos, IN LPD3DXVECTOR3 pOrg, IN LPD3DXVECTOR3 pDir);

	static cMapTerrain* Create(void);
protected:
	cMapTerrain(void);
	virtual ~cMapTerrain(void);

private:
	//�޸� ����
	inline HRESULT _Destroy(void);
	//�ؽ��� �ε�
	inline HRESULT _LoadTexture(D3DXMATERIAL* pMaterial);
	//���̸� ����
	inline HRESULT _BuildHeightMap(LPCSTR szMapName);
	//������ ����
	inline HRESULT _BuildHeightMap(DWORD dwCol, DWORD dwRow);
	//����Ʈ�� ����
	inline HRESULT _BuilldQuadTree(void);
	//���ؽ� ���� ����
	inline HRESULT _CreateVertexBuffer(void);
	//�ε��� ���� ����
	inline HRESULT _CreateIndexBuffer(void);
	//���
	inline HRESULT _Draw(void);

};

