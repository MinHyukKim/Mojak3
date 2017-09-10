#include "stdafx.h"
#include "cUiObject.h"

cUiObject::cUiObject(void)
	: m_vPosition(0, 0, 0)
	, m_stSize(0, 0)
	, m_pParent(NULL)
	, m_nTag(0)
{
}

cUiObject::~cUiObject(void)
{
	for each (auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
}


HRESULT cUiObject::Setup(void)
{
	return D3D_OK;
}


//void cUiObject::Render(void)
//{
//}

cUiObject * cUiObject::Create(void)
{
	cUiObject* newClass = new cUiObject;
	newClass->AddRef();
	return newClass;
}

void cUiObject::AddChild(cUiObject * pChild)
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUiObject::Update(void)
{
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
	}
	for each (auto p in m_vecChild)
	{
		p->Update();
	}
}

void cUiObject::Render(LPD3DXSPRITE pSprite)
{
	for each (auto p in m_vecChild)
	{
		p->Render(pSprite);
	}
}

void cUiObject::SetPosition(float x, float y)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = 0;
}

void cUiObject::GetRect(RECT * pRect)
{
	if (!pRect) return;
	pRect->left = m_matWorld._41;
	pRect->top = m_matWorld._42;
	pRect->right = m_matWorld._41 + m_stSize.fWidth;
	pRect->bottom = m_matWorld._42 + m_stSize.fHeight;
}

cUiObject * cUiObject::GetChildByTag(int nTag)
{
	if (m_nTag == nTag)
	{
		return this;
	}
	
	cUiObject* pChild = NULL;

	for each (auto p in m_vecChild)
	{
		if (p->GetTag() == nTag)
		{
			pChild = p;
			break;
		}
	}
	return pChild;
}



