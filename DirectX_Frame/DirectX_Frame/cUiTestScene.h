#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//태스트
class cFont;
//Ui태스트
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiTestScene : public cSceneObject
{
private:
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	cUiObject* m_pUiRoot;
	cUIImageView* m_pUIImageView;
//	cUIButton* m_pUIButton;

	//클릭변수?
	bool m_isClick;


public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	virtual void OnClick(cUIButton* pSender) override;
//	virtual void Onclick(cUIButton* pSender) override;

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};