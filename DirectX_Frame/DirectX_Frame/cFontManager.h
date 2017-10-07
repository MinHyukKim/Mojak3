#pragma once

#define g_pMeshFontManager cFontManager::GetInstance()

class cMeshFont;

struct ST_FONTCONTAINER
{
	D3DXVECTOR3 vDir;
	float fDelayTime;
	cMeshFont* pFont;

	ST_FONTCONTAINER(LPD3DXVECTOR3 _pDir, float _fDelayTime, cMeshFont* _pFont)
		: vDir(*_pDir), fDelayTime(_fDelayTime), pFont(_pFont) {}
};


typedef std::vector<ST_FONTCONTAINER>::iterator vecFontIter;
class cFontManager
{
private:
	std::vector<ST_FONTCONTAINER> m_vecFont;
	D3DXMATRIXA16 m_matInverseView;

public:
	void Update(void);
	void Render(void);

	void Destroy(void);

	void AddFont(LPCSTR szText, LPD3DXVECTOR3 pPos, LPD3DXVECTOR3 pDir = &D3DXVECTOR3(0.0f,1.0f,0.0f), float fTime = 2.0f, float fSpeed = 0.1f);
	LPD3DXMATRIXA16 GetInverseView(void) { return &m_matInverseView; }

	static cFontManager* GetInstance(void) { static cFontManager instance; return &instance; }
private:
	cFontManager(void);
	virtual ~cFontManager(void);
};

