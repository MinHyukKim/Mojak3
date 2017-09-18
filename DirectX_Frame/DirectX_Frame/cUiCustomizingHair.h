#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//폰트
class cFont;
//Ui구성
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiCustomizingHair : public iButtonDelegate
{
private:

	//기본 구성 스프라이트, 택스트 등
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

	//패널 이미지 크기 태스트용
	cUIImageView* m_pUiTesterSize;
	cUiObject* m_pUiTest;

	//전체 이미지
	cUIImageView* m_pHairSulastHeadImage;
	cUIImageView* m_pHairSulastImage;
	cUIButton* m_pHairButton;
	cUIButton* m_pHairButton01;
	cUIButton* m_pHairButton02;
	cUIButton* m_pHairButton03;
	cUIButton* m_pHairColorButton;
	cUIButton* m_pHairColorButton01;
	cUIButton* m_pHairColorButton02;
	cUIButton* m_pHairColorButton03;
	cUiObject* m_pHairUi;

public:
	virtual HRESULT Setup(void);
	virtual void Reset(void);
	virtual void Update(void);
	virtual void Render(void);

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;

//	static cUiCustomizingHair* Create(void);
	cUiCustomizingHair(void);
	virtual ~cUiCustomizingHair(void);
protected:
	
};