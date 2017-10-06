#include "stdafx.h"
#include "cMeshFont.h"

//#include "cActionMove.h"

cMeshFont::cMeshFont(void)
	: m_pTextMesh(nullptr)
	, m_lf({})
	, m_stMaterial({})
{
	D3DXMatrixIdentity(&m_matWolrd);
}

cMeshFont::~cMeshFont(void)
{
	//SAFE_RELEASE(m_pActionMove);
	SAFE_RELEASE(m_pTextMesh);
}

HRESULT cMeshFont::Setup(LPCSTR pText, LPD3DXCOLOR pColor)
{
	ZeroMemory(&m_lf, sizeof(LOGFONT));
	m_lf.lfHeight = 20;
	m_lf.lfWidth = 10;
	m_lf.lfWeight = 100;
	m_lf.lfItalic = false;
	m_lf.lfUnderline = false;
	m_lf.lfStrikeOut = false;
	m_lf.lfCharSet = DEFAULT_CHARSET;
	lstrcpy(m_lf.lfFaceName, TEXT("Times New Roman"));

	this->SetText(pText);
	this->SetColor();

	return S_OK;
}

void cMeshFont::Update(void)
{

}

void cMeshFont::Render(void)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matTranslation * m_matWolrd));
	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->SetTexture(0, nullptr);
	g_pD3DDevice->SetFVF(m_pTextMesh->GetFVF());
	m_pTextMesh->DrawSubset(0);
}

void cMeshFont::SetText(LPCSTR szText)
{
	float fScaling = 0.05f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, fScaling, fScaling, fScaling);
	D3DXMatrixTranslation(&m_matTranslation, -0.2f * strlen(szText), 0.0f, 0.0f);
	m_matTranslation = m_matTranslation * matS; // 중앙정렬 * 글꼴크기;
	
	HDC hdc = CreateCompatibleDC(NULL);
	HFONT hFont = CreateFontIndirect(&m_lf);
	hFont = (HFONT)SelectObject(hdc, hFont);
	SAFE_RELEASE(m_pTextMesh);
	D3DXCreateText(g_pD3DDevice, hdc, TEXT(szText), 1.0f, 0.001f, &m_pTextMesh, NULL, NULL);
	DeleteObject((HFONT)SelectObject(hdc, hFont));
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void cMeshFont::SetColor(LPD3DXCOLOR pColor)
{
	SetMatrial(&m_stMaterial, *pColor);
}

void cMeshFont::SetBillboard(void)
{
	D3DXMATRIXA16 matView, matInverseView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInverseView, nullptr, &matView);
	this->SetBillboard(&matInverseView);
}

void cMeshFont::SetBillboard(LPD3DXMATRIX pInverseView)
{
	memcpy(&m_matWolrd, pInverseView, 12 * sizeof(float));
	m_matWolrd._44 = pInverseView->_44;
}

void cMeshFont::SetPosition(LPD3DXVECTOR3 pPosition)
{
	memcpy(&m_matWolrd._41, pPosition, sizeof(D3DXVECTOR3));
}

cMeshFont* cMeshFont::Create(void)
{
	cMeshFont* newClass = new cMeshFont;
	newClass->AddRef();
	return newClass;
}

cMeshFont* cMeshFont::Create(LPD3DXVECTOR3 pPosition)
{
	cMeshFont* newClass = cMeshFont::Create();
	newClass->SetPosition(pPosition);
	return newClass;
}
