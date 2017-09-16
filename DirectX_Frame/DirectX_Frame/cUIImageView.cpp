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
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXIMAGE_INFO stImageInfo;
	LPDIRECT3DTEXTURE9 pTexture = g_pTexture->GetTextureEx(m_sTexture, &stImageInfo);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, stImageInfo.Width, stImageInfo.Height);
	pSprite->Draw(pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));

	pSprite->End();

	cUiObject::Render(pSprite);

}