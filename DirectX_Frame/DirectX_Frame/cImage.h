#pragma once

class cImage : public cObject
{
private:
	D3DXIMAGE_INFO m_stImageInfo;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DCOLOR m_dwColor;
	RECT	m_rc;

public:
	virtual void Setup(const D3DXIMAGE_INFO& _stImageInfo, const LPDIRECT3DTEXTURE9 _pTexture);
	virtual void SetImageInfo(const D3DXIMAGE_INFO& _stImageInfo) { m_stImageInfo = _stImageInfo; }
	virtual D3DXIMAGE_INFO& GetImageInfo(void) { return m_stImageInfo; }
	virtual void SetTexture(const LPDIRECT3DTEXTURE9 _pTexture) { m_pTexture = _pTexture; }
	virtual LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }

	virtual void SetSize(int _nWidth, int nHeight) { SetRect(&m_rc, 0, 0, _nWidth, nHeight); }
	virtual void SetColor(D3DCOLOR _dwColor) { m_dwColor = _dwColor; }

	virtual void Draw(LPD3DXSPRITE pSprite);
	virtual void Draw(LPD3DXSPRITE pSprite, D3DCOLOR dwColor, LPD3DXVECTOR3 pPostion = &D3DXVECTOR3(0.0f, 0.0f, 0.0f), LPD3DXVECTOR2 pAnchor = &D3DXVECTOR2(0.5f, 0.5f));


	static cImage* Create(void);
private:
	cImage(void);
	virtual~cImage(void);
};

