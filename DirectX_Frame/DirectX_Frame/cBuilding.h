/*���� ���� �ҷ��� �����ϴ� Ŭ����*/
#pragma once

class cBuilding
{
private:
	//������ ��ġ�� ȸ�� ��
	D3DXMATRIXA16 m_matWorld;
	LPD3DXMESH m_pBuild;
	LPD3DXEFFECT m_pEffect;

	//LPD3DXMESH m_pMesh;
	D3DMATERIAL9*       m_pMeshMaterials;
	LPDIRECT3DTEXTURE9* m_pMeshTextures;
	DWORD               m_dwNumMaterials;

public:
	virtual HRESULT Setup(void);
	LPD3DXMESH LoadModel(const char * filename);
	LPD3DXMESH LoadModel(char * szFolder, char * szFilename);

	void Reset(void);
	virtual void Update(void);
	virtual void Render(void);

	//��ǥ �Լ�
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }

	//static cBuilding* Create(void);
	void Destroy();

	LPD3DXEFFECT LoadEffect(char * szFilename);
	cBuilding(void);
	virtual ~cBuilding(void);

};