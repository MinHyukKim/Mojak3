#include "stdafx.h"
#include "cFont.h"

cFont::cFont(void)
	: m_pFont(NULL)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))		//글씨 기본 색상
	, m_dwFomat(DT_LEFT | DT_TOP)					//글씨 LeftTop 정렬
{
}

cFont::~cFont(void)
{
	SAFE_RELEASE(m_pFont);							//폰트 릴리즈
}


void cFont::Setup(int nFontSize, LPCSTR szFontStyle)
{
	SAFE_RELEASE(m_pFont);							//폰트가 있으면 Release

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));			//지역변수 초기화
	fd.Height = nFontSize;							//폰트 크기
	fd.Width = nFontSize / 2;						//폰트 크기의 절반
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	lstrcpyn(fd.FaceName, szFontStyle, LF_FACESIZE);										//폰트 스타일 이름(Buffer 있음)
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);									//폰트 생성
	if (nFontSize)																			// if(0 == fontsize) 출력범위 수정안함
	{
		m_nFontSize = nFontSize;
		if (m_text.empty()) this->SetRectangle(0, 0, fd.Width * FONT_LENGTH / 2, nFontSize);	//글씨가 없으면 기본값 = 32
	}
}

void cFont::DrawFont(int nX, int nY, LPCSTR szText)
{
	int nStrlen = strlen(szText);															//글자수 찾기
	this->SetRectangle(nX, nY, m_nFontSize * nStrlen / 2 + 1, m_nFontSize);					//상자 이동
	this->SetText(szText);																	//텍스트 내용 수정
}

void cFont::Render(void)
{
	//폰트 출력
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

