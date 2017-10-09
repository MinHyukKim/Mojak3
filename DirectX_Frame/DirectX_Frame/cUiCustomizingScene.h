#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cImage.h"


#define NEXT_SCENE "cCharTestScene"

//폰트
class cFont;
//Ui구성
class cUIImageView;
class cUIImageViewTemp;
class cUIButton;
class cUITextView;
class iButtonDelegate;
//플레이어 띄우기
class cPlayer;
class cCamera;
//이미지
class cImage;

//버튼 딜리게이트 이넘문
enum
{
	E_SERVER_TEXT_NEXT,
	E_SERVER_TEXT_CANCEL,

	E_TEXT_CUSTOM_NAME,
	E_TEXT_CUSTOM_FIN,

	E_SERVER_BUTTON_SERVER = 213,
	E_SERVER_BUTTON_NEXT = 214,
	E_SERVER_BUTTON_CANCEL = 215,

	E_CUSTOM_BUTTON_HAIR = 216,
	E_CUSTOM_BUTTON_EYE = 217,
	E_CUSTOM_BUTTON_MOUTH = 218,

	//헤어설랙트
	E_HAIR_SELECT_01 = 219,
	E_HAIR_SELECT_02 = 220,
	E_HAIR_SELECT_03 = 221,
	//눈 설랙트
	E_EYE_SELECT_01 = 222,
	E_EYE_SELECT_02 = 223,
	E_EYE_SELECT_03 = 224,
	//입 설랙트
	E_MOUTH_SELECT_01 = 222,
	E_MOUTH_SELECT_02 = 223,
	E_MOUTH_SELECT_03 = 224,
	//헤어,눈 칼라 설렉트
	E_HAIR_COLOR_SELECT_BLACK = 225,
	E_HAIR_COLOR_SELECT_MID_BLUE = 226,
	E_HAIR_COLOR_SELECT_RED = 227,
	E_HAIR_COLOR_SELECT_BROWN = 228,
	E_HAIR_COLOR_SELECT_BLONDE = 229,
	E_HAIR_COLOR_SELECT_ORANGE = 230,
	E_HAIR_COLOR_SELECT_DARKGREEN = 232,
	E_HAIR_COLOR_SELECT_WHITE = 233,
	E_HAIR_COLOR_SELECT_SKY = 234,
	E_HAIR_COLOR_SELECT_BLUE = 235,
	//완료 후 나가기
	E_CUSTOM_BUTTON_FIN = 236,
};

//커스텀마이징 메뉴에서의 선택(머리 or 눈 or 입)
enum eCustomizingTab
{
	E_CUSTOM_NONE,
	E_CUSTOM_HAIR,
	E_CUSTOM_EYE,
	E_CUSTOM_MOUTH,
	E_CUSTOM_END
};

//헤어 창 버튼 상태용
enum eCustomizingHair
{
	E_HAIR_NONE,
	E_HAIR_01,
	E_HAIR_02,
	E_HAIR_03,
	E_HAIR_END,
};
//칼라 버튼 상태용
enum cCustomizingHairColor
{
	E_CLOLR_BLACK,
	E_CLOLR_MID,
	E_CLOLR_RED,
	E_CLOLR_BROWN,
	E_CLOLR_BLONDE,
	E_CLOLR_ORANGE,
	E_CLOLR_DARKGREEN,
	E_CLOLR_WHITE,
	E_CLOLR_SKY,
	E_CLOLR_BLUE,
};
//눈 버튼 상태
enum eCustomizingEye
{
	E_EYE_NONE,
	E_EYE_01,
	E_EYE_02,
	E_EYE_03,
	E_EYE_END,
};
//입 버튼 상태
enum eCustomizingMouth
{
	E_MOUTH_NONE,
	E_MOUTH_01,
	E_MOUTH_02,
	E_MOUTH_03,
	E_MOUTH_END,
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
	cSkinnedMesh* pSkinMesh;
	//임시 캐매라
	cCamera* m_pMainCamera;

	//패널 이미지 크기 태스트용
	cUIImageView* m_pUiTesterSize;
	cUiObject* m_mUiTest;

	//이동 가변 뿌리들은 맴버변수로
	//서버 생성 창 (x)
	cUIImageView* m_pServerSulastHeadImage;
	cUIImageView* m_pServerSulastImage;
	cUIButton* m_pServerSulastButton;
	cUITextView* m_pServerTextNext;
	cUITextView* m_pServerTextCancel;
	cUiObject* m_pServerSulastUi;

	//이름 입력 창 (모름)
	cUIImageView* m_pNameImageHead;
	cUIImageView* m_pNameImage;
	cUIButton* m_pNameButton;
	cUiObject* m_pNameUi;

	//커마 메뉴 구분용
	eCustomizingTab m_eCustomizingTab;
	//틀
	cUIImageView* m_pCustomImageHead;
	cUIImageView* m_pCustomImage;
	cUIButton* m_pCustomButtonHair;
	cUIButton* m_pCustomButtonEye;
	cUIButton* m_pCustomButtonMouth;
	cUIButton* m_pCustomButtonFin;
	cUIButton* m_pCustomButton;
	cUiObject* m_pCustomUi;
	//커마 창 글씨
	cUITextView* m_pCustomNameTest;
	//헤어
	eCustomizingHair m_eHairStyleTab;
	cUIImageView* m_pCustomHairImageHead;
	cUIImageView* m_pCustomHairImage;
	cUIButton* m_pCustomHairSulastButton;
	cUiObject* m_pCustomHairUi;
	//색깔(헤어, 눈)
	cUIImageView* m_pCustomColorImageHead;
	cUIImageView* m_pCustomColorImage;
	cUIButton* m_pCustomColorSulastButton;
	cUiObject* m_pCustomColorUi;
	LPD3DXCOLOR m_pHairColor;
	D3DXCOLOR m_hairColor;
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

	//백그라운드
//	cUIImageView* m_pBackImage;
	cImage* m_pBackImage;
	cUIImageViewTemp* m_pBackgroundImage;
	cUiObject* m_pBackgroundUi;

	//초기 위치 잡이
	int m_nX, m_nY;

	//마우스
	bool m_isLButtonDown;
	POINT m_ptMouse;

public:
	virtual HRESULT Setup(void) override;	
	void SetupPlayer(void);				//셋업 플레이어 
	void SetupTotal(void);				//셋업 커마 전제 창 
	void SetupHairStyle(void);			//셋업 머리스타일 버튼(모양)
	void SetupHairEyeColor(void);			//셋업 머리 칼라 버튼
	void SetupEyeStyle(void);			//셋업 눈 버튼
	void SetupMouthStyle(void);			//셋업 입 버튼
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void OnClick(cUIButton* pSender) override;

	//커마 메인선택버튼 색바꾸기
	void changeButtonColor();
	//헤어 버튼 색변경
	void changeButtonColorHair();

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};