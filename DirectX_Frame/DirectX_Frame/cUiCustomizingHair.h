#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//��Ʈ
class cFont;
//Ui����
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiCustomizingHair : public iButtonDelegate
{
private:

	//�⺻ ���� ��������Ʈ, �ý�Ʈ ��
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

	//�г� �̹��� ũ�� �½�Ʈ��
	cUIImageView* m_pUiTesterSize;
//	cUiObject* m_mUiTest;

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