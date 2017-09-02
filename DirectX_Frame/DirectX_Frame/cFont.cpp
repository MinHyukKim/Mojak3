#include "stdafx.h"
#include "cFont.h"

cFont::cFont(void)
	: m_pFont(NULL)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))		//�۾� �⺻ ����
	, m_dwFomat(DT_LEFT | DT_TOP)					//�۾� LeftTop ����
{
}

cFont::~cFont(void)
{
	SAFE_RELEASE(m_pFont);							//��Ʈ ������
}


void cFont::Setup(int nFontSize, LPCSTR szFontStyle)
{
	SAFE_RELEASE(m_pFont);							//��Ʈ�� ������ Release

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));			//�������� �ʱ�ȭ
	fd.Height = nFontSize;							//��Ʈ ũ��
	fd.Width = nFontSize / 2;						//��Ʈ ũ���� ����
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	lstrcpyn(fd.FaceName, szFontStyle, LF_FACESIZE);										//��Ʈ ��Ÿ�� �̸�(Buffer ����)
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);									//��Ʈ ����
	if (nFontSize)																			// if(0 == fontsize) ��¹��� ��������
	{
		m_nFontSize = nFontSize;
		if (m_text.empty()) this->SetRectangle(0, 0, fd.Width * FONT_LENGTH / 2, nFontSize);	//�۾��� ������ �⺻�� = 32
	}
}

void cFont::DrawFont(int nX, int nY, LPCSTR szText)
{
	int nStrlen = strlen(szText);															//���ڼ� ã��
	this->SetRectangle(nX, nY, m_nFontSize * nStrlen / 2 + 1, m_nFontSize);					//���� �̵�
	this->SetText(szText);																	//�ؽ�Ʈ ���� ����
}

void cFont::Render(void)
{
	//��Ʈ ���
	if (m_pFont) m_pFont->DrawText(NULL, m_text.c_str(), m_text.length(), &m_rc, m_dwFomat, m_dwColor);
}

cFont* cFont::Create(void)
{
	return nullptr;
}

cFont* cFont::AddRef(void)
{
	return nullptr;
}

