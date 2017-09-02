#pragma once

#define FONT_SIZE 20
#define FONT_STYLE "�ü�ü"

class cFont : public cObject
{
private:
	//��Ʈ ��� ����
	LPD3DXFONT	m_pFont;
	std::string m_text;
	RECT	m_rc;
	DWORD	m_dwFomat;
	DWORD	m_dwColor;

public:
	//�⺻ ���� (Setup)
	void Setup(void);
	void Setup(int x, int y, LPCSTR text);

	//���� ���� (Update)

	//����
	void Render(void);


	static cFont* Create(void);
	virtual cFont* AddRef(void);
protected:
	cFont(void);
	virtual ~cFont(void);
};

