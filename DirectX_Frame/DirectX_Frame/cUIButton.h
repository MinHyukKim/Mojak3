#pragma once
#include "cUiObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUiObject* pSender) = 0;
//	virtual void OnClick(cUiObject* pSender) {};
};

class cUIButton : public cUiObject
{
private:

protected:

public:

	cUIButton(void);
	virtual ~cUIButton(void);
};