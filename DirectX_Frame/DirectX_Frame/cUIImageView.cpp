#include "stdafx.h"
#include "cUIImageView.h"

cUIImageView::cUIImageView(void)
{
}

cUIImageView::~cUIImageView(void)
{
}


void cUIImageView::SetTexture(std::string sFullPath)
{
	m_sTexture = sFullPath;
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXIMAGE_INFO stImageInfo;
	LPDIRECT3DTEXTURE9 pTexture = g_pTexture->GetTextureEx(m_sTexture, &stImageInfo);
}