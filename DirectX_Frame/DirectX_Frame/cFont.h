#pragma once

#define FONT_SIZE 20
#define FONT_STYLE "궁서체"

class cFont : public cObject
{
private:
	//폰트 출력 정보
	LPD3DXFONT	m_pFont;
	std::string m_text;
	RECT	m_rc;
	DWORD	m_dwFomat;
	DWORD	m_dwColor;

public:
	//기본 설정 (Setup)
	void Setup(void);
	void Setup(int x, int y, LPCSTR text);

	//정보 수정 (Update)

	//랜더
	void Render(void);


	static cFont* Create(void);
	virtual cFont* AddRef(void);
protected:
	cFont(void);
	virtual ~cFont(void);
};

