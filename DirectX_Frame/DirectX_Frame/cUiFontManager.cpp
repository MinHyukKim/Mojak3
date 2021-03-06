#include "stdafx.h"
#include "cUiFontManager.h"


cUiFontManager::cUiFontManager(void)
{
}

cUiFontManager::~cUiFontManager(void)
{
}

LPD3DXFONT cUiFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) == m_mapFont.end())
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

		if (e == E_NORMAL)
		{
			fd.Height = 24;
			fd.Width = 12;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "����ü");
		}
		else if (e == E_QUEST)
		{
			fd.Height = 50;
			fd.Width = 25;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_CHARACTER_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "����ü");
		}
		else if (e == E_INBUTTON)
		{
			fd.Height = 24;
			fd.Width = 8;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_CHARACTER_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "TeamViewer12");
		}
		else if (e == E_TEMP_INBUTTON)
		{
			fd.Height = 12;
			fd.Width = 6;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_CHARACTER_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "��������");
		}
		else if (e == E_TEMP_IN_SMALL)
		{
			fd.Height = 11;
			fd.Width = 5.5f;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_CHARACTER_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "��������");
		}
		
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	}

	return m_mapFont[e];
}

void cUiFontManager::Destroy()
{
	for each(auto p in m_mapFont)
	{
		SAFE_RELEASE(p.second);
	}
}
