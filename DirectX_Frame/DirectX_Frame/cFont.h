#pragma once

#define FONT_STYLE "궁서체"
#define FONT_LENGTH 32

class cFont : public cObject
{
private:
	//폰트 출력 정보
	LPD3DXFONT	m_pFont;
	std::string m_text;
	RECT	m_rc;
	DWORD	m_dwFomat;
	DWORD	m_dwColor;
	int		m_nFontSize;

public:
	//기본 설정 및 수정 (Setup) 글씨크기나 스타일 변경시 사용
	void Setup(int nFontSize = 20, LPCSTR szFontStyle = FONT_STYLE);

	//정보 수정 (Update)
	void SetRectangle(int nX, int nY, int nWidth, int nHeight) { SetRect(&m_rc, nX, nY, nX + nWidth, nY + nHeight); }
	void SetText(LPCSTR szText) { m_text = szText; }			//글씨 내용
	void DrawFont(int nX, int nY, LPCSTR szText);				//글씨 위치와 내용
	void SetFomat(DWORD dwFomat) { m_dwFomat = dwFomat; }		//글씨 정렬 설정
	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }		//글씨 색상 설정

	//실제 출력 타이밍 (Render)
	void Render(void);


	static cFont* Create(void);
protected:
	cFont(void);
	virtual ~cFont(void);
};

