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

	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUITextView* Create(void);		//메모리관리용 생성자 
protected:
	cUITextView(void);
	virtual ~cUITextView(void);
};