#pragma once
#include "cUiObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) {};
	virtual void OnMouseOver(cUIButton* pSender) {};
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
	virtual void SetTexture(std::string sNor, std::string sOvr, std::string sSel);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	RECT rc;
	bool isOver;

	int m_Alpha;
	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUIButton* Create(void);		//메모리관리용 생성자 
protected:
	cUIButton(void);
	virtual ~cUIButton(void);
};