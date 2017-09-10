#pragma once
#include "cUiObject.h"

class cUIButton;

class iButtonDelegate
{
public:
//	virtual void OnClick(cUIButton* pSender) = 0;
	virtual void OnClick(cUIButton* pSender) {};
};

class cUIButton : public cUiObject
{
private:
	bool isClick;

protected:
	enum eButtonStatus
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATUS_COUNT,
	};

	eButtonStatus m_eButtonStatus;
	std::string m_aTexture[E_STATUS_COUNT];
	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);

public:
	//¹Ì±¸Çö
	virtual void SetTexture(std::string sNor, std::string sOvr, std::string sSel);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;

	cUIButton(void);
	virtual ~cUIButton(void);
};