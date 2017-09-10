#pragma once
#include "cUiObject.h"

class cUITextView : public cUiObject
{
private:

protected:
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwDT, DtawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwColor, Color);
//	SYNTHESIZE()

public:
	void Render(LPD3DXSPRITE pSprite) override;

	cUITextView(void);
	virtual ~cUITextView(void);
};