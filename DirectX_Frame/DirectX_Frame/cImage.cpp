#include "stdafx.h"
#include "cImage.h"

cImage::cImage(void)
	: m_pTexture(nullptr)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
	ZeroMemory(&m_stImageInfo, sizeof(D3DXIMAGE_INFO));
	D3DXMatrixIdentity(&m_matWorld);
}

cImage::~cImage(void)
{
}

void cImage::Update()
{
}

void cImage::Setup(const D3DXIMAGE_INFO & _stImageInfo, const LPDIRECT3DTEXTURE9 _pTexture)
{
	m_stImageInfo = _stImageInfo;
	m_pTexture = _pTexture;
	m_dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	SetRect(&m_rc, 0, 0, _stImageInfo.Width, _stImageInfo.Height);
}

void cImage::Draw(LPD3DXSPRITE pSprite)
{
	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_pTexture, &m_rc, &D3DXVECTOR3(m_rc.right * 0.5f, m_rc.bottom * 0.5f, 0.0f), &D3DXVECTOR3(0, 0, 0), m_dwColor);
}

void cImage::Draw(LPD3DXSPRITE pSprite, D3DCOLOR dwColor, LPD3DXVECTOR3 pPostion, LPD3DXVECTOR2 pAnchor)
{
	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_pTexture, &m_rc, &D3DXVECTOR3(m_rc.right * pAnchor->x, m_rc.bottom * pAnchor->y, 0.0f), pPostion, dwColor);
}

cImage* cImage::Create(void)
{
	cImage* newClass = new cImage;
	newClass->AddRef();
	return newClass;
}
