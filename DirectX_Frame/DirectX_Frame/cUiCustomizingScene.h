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
//플레이어 띄우기
class cPlayer;
class cCamera;

enum eCustomizingTab
{
	E_CUSTOM_NONE,
	E_CUSTOM_HAIR,
	E_CUSTOM_EYE,
	E_CUSTOM_MOUTH,
	E_CUSTOM_END
};

class cUiCustomizingScene : public cSceneObject, iButtonDelegate
{
private:

	//기본 구성 스프라이트, 택스트 등
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

	//플레이어 보여주기
	cPlayer* m_pPlayer;
	//임시 캐매라
	cCamera* m_pMainCamera;

	//패널 이미지 크기 태스트용
	cUIImageView* m_pUiTesterSize;
	cUiObject* m_mUiTest;

	//이동 가변 뿌리들은 맴버변수로
	//서버 생성 창
	cUIImageView* m_pServerSulastHeadImage;
	cUIImageView* m_pServerSulastImage;
	cUIButton* m_pServerSulastButton;
	cUITextView* m_pServerTextNext;
	cUITextView* m_pServerTextCancel;
	cUiObject* m_pServerSulastUi;

	//이름 입력 창
	cUIImageView* m_pNameImageHead;
	cUIImageView* m_pNameImage;
	cUIButton* m_pNameButton;
	cUiObject* m_pNameUi;

	//커마...
	eCustomizingTab m_eCustomizingTab;
	//틀
	cUIImageView* m_pCustomImageHead;
	cUIImageView* m_pCustomImage;
	cUIButton* m_pCustomButtonHair;
	cUIButton* m_pCustomButtonEye;
	cUIButton* m_pCustomButtonMouth;
	cUIButton* m_pCustomButton;
	cUiObject* m_pCustomUi;
	//헤어
	cUIImageView* m_pCustomHairImageHead;
	cUIImageView* m_pCustomHairImage;
	cUIButton* m_pCustomHairSulastButton;
	cUIButton* m_pCustomHairColorSulastButton;
	cUiObject* m_pCustomHairUi;
	//눈
	cUIImageView* m_pCustomEyeImageHead;
	cUIImageView* m_pCustomEyeImage;
	cUIButton* m_pCustomEyeSulastButton;
	cUIButton* m_pCustomEyeColorSulastButton;
	cUiObject* m_pCustomEyeUi;
	//입
	cUIImageView* m_pCustomMouthImageHead;
	cUIImageView* m_pCustomMouthImage;
	cUIButton* m_pCustomMouthSulastButton;
	cUIButton* m_pCustomMouthColorSulastButton;
	cUiObject* m_pCustomMouthUi;
	//확인팝업

	//마우스
	bool m_isLButtonDown;
	POINT m_ptMouse;
	POINT m_ptPrevMouse;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;

	//커마 메인 색바꾸기
	void changeButtonColor();
	//음직임?
	void moveingPlayer();

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};