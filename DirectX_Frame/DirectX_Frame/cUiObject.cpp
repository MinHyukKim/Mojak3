#include "stdafx.h"
#include "cUiObject.h"

cUiObject::cUiObject(void)
{
}

cUiObject::~cUiObject(void)
{
}
HRESULT cUiObject::Setup(void)
{
	return D3D_OK;
}


void cUiObject::Render(void)
{
}

void cUiObject::AddChild(cUiObject * pChild)
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUiObject::Update(void)
{
//	m_matWorld._41 = m_vPosition
}

void cUiObject::Render(LPD3DXSPRITE pSprite)
{
}

void cUiObject::SetPosition(float x, float y)
{
}

void cUiObject::GetRect(RECT * pRect)
{
}

cUiObject * cUiObject::GetChildByTag(int nTag)
{
	return nullptr;
}

cUiObject * cUiObject::Create(void)
{
	cUiObject* newClass = new cUiObject;
	newClass->AddRef();
	return newClass;
}

