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
	
	//���ؽ� ������
	ST_PNT_VERTEX* GetVertex(DWORD dwX, DWORD dwZ) { return &m_vecMapVertex[dwX + dwZ * m_dwCol]; }
	//���ؽ� ����
	float GetHeight(DWORD dwX, DWORD dwZ) { return m_vecMapVertex[dwX + dwZ * m_dwCol].p.y; }
	//���ؽ����� (����)
	DWORD GetCol(void) { return m_dwCol; }
	//���ؽ����� (����)
	DWORD GetRow(void) { return m_dwRow; }
	//��ũ�� x
	float GetTerrainCol(void) { return (float)m_dwCol * m_vScale.x; }
	//��ũ�� z
	float GetTerrainRow(void) { return (float)m_dwRow * m_vScale.z; }

	static cMapTerrain* Create(void);
protected:
	cMapTerrain(void);
	virtual ~cMapTerrain(void);

private:
	//�޸� ����
	inline HRESULT _Destroy(void);
	//�ؽ��� �ε�
	inline HRESULT _LoadTexture(LPSTR szTexFileName);
	//���̸� ����
	inline HRESULT _BuildHeightMap(LPCSTR szMapName);
	//������ ����
	inline HRESULT _BuildHeightMap(DWORD dwCol, DWORD dwRow);
	//����Ʈ�� ����
	inline HRESULT _BuilldQuadTree(void);
	//�ε��� ���� ����
	inline HRESULT _CreateIndexBuffer(void);
	//���
	inline HRESULT _Draw(void);

};

