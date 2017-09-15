#pragma once
#include "cUiObject.h"

class cUITextView : public cUiObject
{
private:

protected:
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwDT, DtawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwColor, Color);

public:
	SYNTHESIZE(cUiFontManager::eFontType, m_eFontType, FontType);
	virtual void Render(LPD3DXSPRITE pSprite) override;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUITextView* Create(void);		//�޸𸮰����� ������ 
protected:
	cUITextView(void);
	virtual ~cUITextView(void);
};