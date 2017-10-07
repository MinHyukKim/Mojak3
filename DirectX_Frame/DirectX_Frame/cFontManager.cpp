#include "stdafx.h"
#include "cFontManager.h"

#include "cMeshFont.h"

cFontManager::cFontManager(void)
{
}

cFontManager::~cFontManager(void)
{
}

void cFontManager::Update(void)
{
	float fElapsedTime = g_pTimeManager->GetElapsedTime();
	D3DXMATRIXA16 matView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&m_matInverseView, nullptr, &matView);
	for (vecFontIter it = m_vecFont.begin(); it != m_vecFont.end();)
	{
		it->fDelayTime -= fElapsedTime;
		if (0.0f < it->fDelayTime)
		{
			it->pFont->SetPosition(&(it->pFont->GetPosition() + it->vDir * fElapsedTime));
			it->pFont->SetBillboard(&m_matInverseView);
			it++;
		}
		else
		{
			SAFE_RELEASE(it->pFont);
			it = m_vecFont.erase(it);
		}
	}
}

void cFontManager::Render(void)
{
	for each (auto value in m_vecFont)
	{
		if (0.0f >= value.fDelayTime) continue;
		value.pFont->Render();
	}
}

void cFontManager::Destroy(void)
{
	for each (auto value in m_vecFont)
	{
		SAFE_RELEASE(value.pFont);
	}
	m_vecFont.clear();
}

void cFontManager::AddFont(LPCSTR szText, LPD3DXVECTOR3 pPos, LPD3DXVECTOR3 pDir, float fTime, float fSpeed)
{
	cMeshFont* pFont = cMeshFont::Create(pPos);
	pFont->Setup(szText);
	pFont->SetBillboard();

	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, pDir);
	vDir *= fSpeed;

	m_vecFont.push_back(ST_FONTCONTAINER(&vDir, fTime, pFont));
}
