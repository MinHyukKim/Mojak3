
#include "stdafx.h"
#include "cUiCustomizingHair.h"
//ÆùÆ® ¿ë
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

cUiCustomizingHair::cUiCustomizingHair(void)
	: m_pSprite(NULL)
	, m_pTexture(NULL)
{
}

cUiCustomizingHair::~cUiCustomizingHair(void)
{
}

//cUiCustomizingHair * cUiCustomizingHair::Create(void)
//{
//	cUiCustomizingHair* newClass = new cUiCustomizingHair;
//	newClass->AddRef();
//	return newClass;
//}


HRESULT cUiCustomizingHair::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	return D3D_OK;
}

void cUiCustomizingHair::Reset(void)
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}

void cUiCustomizingHair::Update(void)
{
}

void cUiCustomizingHair::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
}

void cUiCustomizingHair::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cUiCustomizingHair::OnClick(cUIButton * pSender)
{
}

