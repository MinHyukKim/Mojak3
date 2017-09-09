#pragma once
#include "cUiObject.h"

class cUIImageView : public cUiObject
{
private:
	std::string m_sTexture;

public:
	void SetTexture(std::string sFullPath);
//	void Render(LPD3DXSPRITE pSprite);

	cUIImageView(void);
	virtual ~cUIImageView(void);
};