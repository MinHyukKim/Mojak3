#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton(void)
	: m_eButtonStatus(E_NORMAL)
	, m_pDelegate(NULL)
{
}

cUIButton::~cUIButton(void)
{
}

cUIButton * cUIButton::Create(void)
{
	cUIButton* newClass = new cUIButton;
	newClass->AddRef();
	return newClass;
}

//void iButtonDelegate::OnClick(cUiObject * pSender)
//{
//
//}

void cUIButton::SetTexture(std::string sNor, std::string sOvr, std::string sSel)
{
	m_aTexture[E_NORMAL] = sNor;
	m_aTexture[E_MOUSEOVER] = sOvr;
	m_aTexture[E_SELECTED] = sSel;

	D3DXIMAGE_INFO stImageInfo;
	g_pTexture->GetTextureEx(sNor, &stImageInfo);
	m_stSize.fWidth = stImageInfo.Width;
	m_stSize.fHeight = stImageInfo.Height;
}

void cUIButton::Update()
{
	RECT rc;
	GetRect(&rc);

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&rc, ptMouse))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			//마우스 오버
			if (m_eButtonStatus == E_MOUSEOVER)
			{
				m_eButtonStatus = E_SELECTED;
			}
		}
		else
		{
			if (m_eButtonStatus == E_SELECTED)
			{
				if (m_pDelegate) m_pDelegate->OnClick(this);
			}
			m_eButtonStatus = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonStatus = E_NORMAL;
	}

	cUiObject::Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	D3DXIMAGE_INFO stImageInfo;
	LPDIRECT3DTEXTURE9 pTexture = g_pTexture->GetTextureEx(m_aTexture[m_eButtonStatus], &stImageInfo);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, stImageInfo.Width, stImageInfo.Height);
	pSprite->Draw(pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

	cUiObject::Render(pSprite);
}