#include "stdafx.h"
#include "cFont.h"

cFont::cFont(void)
{
}

cFont::~cFont(void)
{
}


void cFont::Setup(void)
{
	SAFE_RELEASE(m_pFont);
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = FONT_SIZE;
	fd.Width = FONT_SIZE / 2;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	lstrcpyn(fd.FaceName, FONT_STYLE, FONT_LENGTH);					//��Ʈ Ÿ�� ����
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);			//��Ʈ ����
	SetRect(&m_rc, 0, 0, FONT_SIZE / 2 * FONT_LENGTH, FONT_SIZE);	//�۾� ��� ����
	m_dwColor = D3DCOLOR_XRGB(255, 255, 255);						//�۾� �⺻ ����
	m_dwFomat = DT_LEFT | DT_TOP;									//�۾� LeftTop ����
}

void cFont::Setup(int x, int y, LPCSTR text, int size)
{
}

void cFont::Render(void)
{
}

cFont * cFont::Create(void)
{
	return nullptr;
}

cFont * cFont::AddRef(void)
{
	return nullptr;
}

