#pragma once

#define g_pFontManager cUiFontManager::GetInstance()

class cUiFontManager
{
public:
	//½Ì±ÛÅæ »ý¼º
	static cUiFontManager* GetInstance(void) { static cUiFontManager instance; return &instance; }


	enum eFontType
	{
		E_NORMAL,
		E_QUEST,
		E_INBUTTON,
		E_END,
	};

private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;

public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();

private:
	cUiFontManager(void);
	virtual ~cUiFontManager(void);
};