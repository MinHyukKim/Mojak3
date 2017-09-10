#pragma once
#include "cSceneObject.h"

//태스트
class cFont;
//Ui태스트
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiTestScene : public cSceneObject/*, public iButtonDelegate*/
{
private:
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// iButtonDelegate override
//	void OnClick(cUIButton* pSender) override;

	static cSceneObject* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};