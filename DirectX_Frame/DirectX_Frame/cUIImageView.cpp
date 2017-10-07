#include "stdafx.h"
#include "cUIImageView.h"

cUIImageView::cUIImageView(void)
	:m_Alpha(255)
{
}

cUIImageView::~cUIImageView(void)
{
}

cUIImageView * cUIImageView::Create(void)
{
	cUIImageView* newClass = new cUIImageView;
	newClass->AddRef();
	return newClass;
}

void cUIImageView::SetTexture(std::string sFullPath)
{
	m_sTexture = sFullPath;
	g_pTexture->GetTextureEx(m_sTexture, &stImageInfo);
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	//D3DXIMAGE_INFO stImageInfo;
	LPDIRECT3DTEXTURE9 pTexture = g_pTexture->GetTextureEx(m_sTexture, &stImageInfo);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	//RECT rc;
	SetRect(&m_rc, 0, 0, stImageInfo.Width, stImageInfo.Height);
//	SetRect(&m_conRECT, 0, 0, stImageInfo.Width, stImageInfo.Height);
	pSprite->Draw(pTexture, &m_rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));

	pSprite->End();

	cUiObject::Render(pSprite);
}



cUIImageViewTemp::cUIImageViewTemp(void)
	:m_Alpha(255)
{
}

cUIImageViewTemp::~cUIImageViewTemp(void)
{
}

cUIImageViewTemp * cUIImageViewTemp::Create(void)
{
	cUIImageViewTemp* newClass = new cUIImageViewTemp;
	newClass->AddRef();
	return newClass;
}

void cUIImageViewTemp::SetTexture(std::string sFullPath)
{
	m_sTexture = sFullPath;
}

void cUIImageViewTemp::SetRectSize()
{
	pTexture = g_pTexture->GetTextureEx(m_sTexture, &stImageInfo);
	SetRect(&m_rc, 0, 0, stImageInfo.Width, stImageInfo.Height);
}

void cUIImageViewTemp::Render(LPD3DXSPRITE pSprite)
{
	//D3DXIMAGE_INFO stImageInfo;
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(pTexture, &m_rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));

	pSprite->End();

	cUiObject::Render(pSprite);
}
