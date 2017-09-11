#include "stdafx.h"
#include "cUITextView.h"

cUITextView::cUITextView(void)
	: m_dwDT(DT_LEFT | DT_TOP | DT_NOCLIP)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
	, m_eFontType(cUiFontManager::E_NORMAL)
{
}

cUITextView::~cUITextView(void)
{
}

cUITextView * cUITextView::Create(void)
{
	cUITextView* newClass = new cUITextView;
	newClass->AddRef();
	return newClass;
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;
	rc.left = m_matWorld._41;
	rc.top = m_matWorld._42;
	rc.right = m_matWorld._41 + m_stSize.fWidth;
	rc.bottom = m_matWorld._42 + m_stSize.fHeight;

	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);
	pFont->DrawTextA(NULL, m_sText.c_str(), m_sText.length(),
		&rc, m_dwDT, m_dwColor);
}

