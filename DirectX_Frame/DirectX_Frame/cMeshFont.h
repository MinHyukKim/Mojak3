#pragma once

class cMeshFont : public cObject
{
private:
//	cActionMove* m_pActionMove;
	LPD3DXMESH m_pTextMesh;
	LOGFONT m_lf;
	D3DXMATRIXA16 m_matTranslation;
	D3DXMATRIXA16 m_matWolrd;
	D3DMATERIAL9 m_stMaterial;

public:
	virtual HRESULT Setup(LPCSTR szText = "1", LPD3DXCOLOR pColor = &D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetText(LPCSTR pText);
	void SetColor(LPD3DXCOLOR pColor = &D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	void SetBillboard(void);
	void SetBillboard(LPD3DXMATRIX pInverseView);

	void SetPosition(LPD3DXVECTOR3 pPosition);
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(&m_matWolrd._41); }

	static cMeshFont* Create(void);
	static cMeshFont* Create(LPD3DXVECTOR3 pPosition);
protected:
	cMeshFont(void);
	virtual ~cMeshFont(void);
};

