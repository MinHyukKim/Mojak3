#pragma once
class cTile
{
private:
	D3DXVECTOR3 m_vPosition;
	DWORD m_dwNumTexture;
	DWORD m_dwData;

public:
	void SetPosition(D3DXVECTOR3& vPosition) { m_vPosition = vPosition; }
	const D3DXVECTOR3& GetPosition(void) { return m_vPosition; }
	void SetNumTexture(DWORD dwNumTexture) { m_dwNumTexture = dwNumTexture; }
	DWORD GetNumTexture(void) { return m_dwNumTexture; }
	void SetData(DWORD dwData) { m_dwData = dwData; }
	DWORD GetDara(void) { return m_dwData; }

	cTile(void);
	cTile(D3DXVECTOR3& vPosition, DWORD dwNumTexture, DWORD dwData);
	virtual ~cTile(void);
};

