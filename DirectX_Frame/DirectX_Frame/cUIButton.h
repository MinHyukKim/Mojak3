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

	//enum eButtonStatus
	//{
	//	E_NORMAL,
	//	E_MOUSEOVER,
	//	E_SELECTED,
	//	E_STATUS_COUNT,
	//};

	//eButtonStatus m_eButtonStatus;
	//std::string m_aTexture[E_STATUS_COUNT];

	virtual void SetTexture(std::string sNor, std::string sOvr, std::string sSel);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;

	eButtonStatus GetButtonStatus(void) { return m_eButtonStatus; }


	D3DXIMAGE_INFO stImageInfo;
	RECT rc;
	bool isOver;
	bool isClick;

	int m_Alpha;
	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUIButton* Create(void);		//�޸𸮰����� ������ 
protected:
	cUIButton(void);
	virtual ~cUIButton(void);
};