#pragma once
#include "cUiObject.h"

class cUIImageView : public cUiObject
{
private:
	std::string m_sTexture;

public:
	virtual void SetTexture(std::string sFullPath);
	virtual void Render(LPD3DXSPRITE pSprite);

	cUIImageView(void);
	virtual ~cUIImageView(void);
};