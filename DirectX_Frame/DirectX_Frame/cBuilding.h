/*빌딩 모델을 불러와 렌더하는 클래스*/
#pragma once

class cBuilding
{
private:
	//월드의 위치와 회전 값
	D3DXMATRIXA16 m_matWorld, m_matRot, m_matScale;
	LPD3DXMESH m_pBuild;
	LPD3DXEFFECT m_pEffect;

	//LPD3DXMESH m_pMesh;
	D3DMATERIAL9*       m_pMeshMaterials;
	LPDIRECT3DTEXTURE9* m_pMeshTextures;
	DWORD               m_dwNumMaterials;

	float angleX;
	float angleY;
	float angleZ;
	
	//바닥에서 얼마나 떨어져있는지 결정하는 변수
	float m_fOffsetY;

public:
	virtual HRESULT Setup(void);
	LPD3DXMESH LoadModel(const char * filename);
	LPD3DXMESH LoadModel(char * szFolder, char * szFilename);

	void Reset(void);
	virtual void Update(void);
	virtual void Render(void);

	//좌표 함수
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	void SetAngleX(float fX) { D3DXMatrixRotationX(&m_matRot, fX); m_matWorld = m_matRot*m_matWorld; }
	void SetAngleY(float fY) { D3DXMatrixRotationY(&m_matRot, fY); m_matWorld = m_matRot*m_matWorld; }
	void SetAngleZ(float fZ) { D3DXMatrixRotationZ(&m_matRot, fZ); m_matWorld = m_matRot*m_matWorld; }
	float GetAngleX() { return angleX; }
	float GetAngleY() { return angleY; }
	float GetAngleZ() { return angleZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }

	float GetOffsetY() { return m_fOffsetY; }
	void SetOffsetY(float offset) { m_fOffsetY = offset; }
	void SetScale(float scale) { D3DXMatrixScaling(&m_matScale, scale, scale, scale); m_matWorld = m_matScale*m_matWorld;}

	//static cBuilding* Create(void);
	void Destroy();

	LPD3DXEFFECT LoadEffect(char * szFilename);
	cBuilding(void);
	virtual ~cBuilding(void);

};