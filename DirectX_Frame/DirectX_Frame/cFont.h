#pragma once

#define FONT_STYLE "�ü�ü"
#define FONT_LENGTH 32

class cFont : public cObject
{
private:
	//��Ʈ ��� ����
	LPD3DXFONT	m_pFont;
	std::string m_text;
	RECT	m_rc;
	DWORD	m_dwFomat;
	DWORD	m_dwColor;
	int		m_nFontSize;

public:
	//�⺻ ���� �� ���� (Setup) �۾�ũ�⳪ ��Ÿ�� ����� ���
	void Setup(int nFontSize = 20, LPCSTR szFontStyle = FONT_STYLE);

	//���� ���� (Update)
	void SetRectangle(int nX, int nY, int nWidth, int nHeight) { SetRect(&m_rc, nX, nY, nX + nWidth, nY + nHeight); }
	void SetText(LPCSTR szText) { m_text = szText; }			//�۾� ����
	void DrawFont(int nX, int nY, LPCSTR szText);				//�۾� ��ġ�� ����
	void SetFomat(DWORD dwFomat) { m_dwFomat = dwFomat; }		//�۾� ���� ����
	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }		//�۾� ���� ����

	//���� ��� Ÿ�̹� (Render)
	void Render(void);


	static cFont* Create(void);
protected:
	cFont(void);
	virtual ~cFont(void);
};

