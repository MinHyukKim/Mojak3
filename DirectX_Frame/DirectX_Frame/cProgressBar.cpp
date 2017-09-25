#include "stdafx.h"
#include "cProgressBar.h"
#include "cUIImageView.h"

cProgressBar::cProgressBar(void)
{
}

cProgressBar::~cProgressBar(void)
{
}

cProgressBar * cProgressBar::Create(void)
{
	cProgressBar* newClass = new cProgressBar;
	newClass->AddRef();
	return newClass;
}


HRESULT cProgressBar::SetUp(const char * upKeyName, const char * downKeyName, float x, float y, int width, int height)
{


	return D3D_OK;
}

HRESULT cProgressBar::SetUp(float x, float y)
{
	m_fX = x;
	m_fY = y;
	
//	m_pGaugeUp = cUIImageView::SetTexture()

	return D3D_OK;
}
