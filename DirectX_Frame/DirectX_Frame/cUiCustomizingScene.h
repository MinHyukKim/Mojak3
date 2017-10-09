#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cImage.h"


#define NEXT_SCENE "cCharTestScene"

//��Ʈ
class cFont;
//Ui����
class cUIImageView;
class cUIImageViewTemp;
class cUIButton;
class cUITextView;
class iButtonDelegate;
//�÷��̾� ����
class cPlayer;
class cCamera;
//�̹���
class cImage;

//��ư ��������Ʈ �̳ѹ�
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

	//����Ʈ
	E_HAIR_SELECT_01 = 219,
	E_HAIR_SELECT_02 = 220,
	E_HAIR_SELECT_03 = 221,
	//�� ����Ʈ
	E_EYE_SELECT_01 = 222,
	E_EYE_SELECT_02 = 223,
	E_EYE_SELECT_03 = 224,
	//�� ����Ʈ
	E_MOUTH_SELECT_01 = 222,
	E_MOUTH_SELECT_02 = 223,
	E_MOUTH_SELECT_03 = 224,
	//���,�� Į�� ����Ʈ
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
	//�Ϸ� �� ������
	E_CUSTOM_BUTTON_FIN = 236,
};

//Ŀ���Ҹ���¡ �޴������� ����(�Ӹ� or �� or ��)
enum eCustomizingTab
{
	E_CUSTOM_NONE,
	E_CUSTOM_HAIR,
	E_CUSTOM_EYE,
	E_CUSTOM_MOUTH,
	E_CUSTOM_END
};

//��� â ��ư ���¿�
enum eCustomizingHair
{
	E_HAIR_NONE,
	E_HAIR_01,
	E_HAIR_02,
	E_HAIR_03,
	E_HAIR_END,
};
//Į�� ��ư ���¿�
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
//�� ��ư ����
enum eCustomizingEye
{
	E_EYE_NONE,
	E_EYE_01,
	E_EYE_02,
	E_EYE_03,
	E_EYE_END,
};
//�� ��ư ����
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

	//�⺻ ���� ��������Ʈ, �ý�Ʈ ��
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

	//�÷��̾� �����ֱ�
	cPlayer* m_pPlayer;
	cSkinnedMesh* pSkinMesh;
	//�ӽ� ĳ�Ŷ�
	cCamera* m_pMainCamera;

	//�г� �̹��� ũ�� �½�Ʈ��
	cUIImageView* m_pUiTesterSize;
	cUiObject* m_mUiTest;

	//�̵� ���� �Ѹ����� �ɹ�������
	//���� ���� â (x)
	cUIImageView* m_pServerSulastHeadImage;
	cUIImageView* m_pServerSulastImage;
	cUIButton* m_pServerSulastButton;
	cUITextView* m_pServerTextNext;
	cUITextView* m_pServerTextCancel;
	cUiObject* m_pServerSulastUi;

	//�̸� �Է� â (��)
	cUIImageView* m_pNameImageHead;
	cUIImageView* m_pNameImage;
	cUIButton* m_pNameButton;
	cUiObject* m_pNameUi;

	//Ŀ�� �޴� ���п�
	eCustomizingTab m_eCustomizingTab;
	//Ʋ
	cUIImageView* m_pCustomImageHead;
	cUIImageView* m_pCustomImage;
	cUIButton* m_pCustomButtonHair;
	cUIButton* m_pCustomButtonEye;
	cUIButton* m_pCustomButtonMouth;
	cUIButton* m_pCustomButtonFin;
	cUIButton* m_pCustomButton;
	cUiObject* m_pCustomUi;
	//Ŀ�� â �۾�
	cUITextView* m_pCustomNameTest;
	//���
	eCustomizingHair m_eHairStyleTab;
	cUIImageView* m_pCustomHairImageHead;
	cUIImageView* m_pCustomHairImage;
	cUIButton* m_pCustomHairSulastButton;
	cUiObject* m_pCustomHairUi;
	//����(���, ��)
	cUIImageView* m_pCustomColorImageHead;
	cUIImageView* m_pCustomColorImage;
	cUIButton* m_pCustomColorSulastButton;
	cUiObject* m_pCustomColorUi;
	LPD3DXCOLOR m_pHairColor;
	D3DXCOLOR m_hairColor;
	//��
	cUIImageView* m_pCustomEyeImageHead;
	cUIImageView* m_pCustomEyeImage;
	cUIButton* m_pCustomEyeSulastButton;
	cUIButton* m_pCustomEyeColorSulastButton;
	cUiObject* m_pCustomEyeUi;
	//��
	cUIImageView* m_pCustomMouthImageHead;
	cUIImageView* m_pCustomMouthImage;
	cUIButton* m_pCustomMouthSulastButton;
	cUIButton* m_pCustomMouthColorSulastButton;
	cUiObject* m_pCustomMouthUi;
	//Ȯ���˾�

	//��׶���
//	cUIImageView* m_pBackImage;
	cImage* m_pBackImage;
	cUIImageViewTemp* m_pBackgroundImage;
	cUiObject* m_pBackgroundUi;

	//�ʱ� ��ġ ����
	int m_nX, m_nY;

	//���콺
	bool m_isLButtonDown;
	POINT m_ptMouse;

public:
	virtual HRESULT Setup(void) override;	
	void SetupPlayer(void);				//�¾� �÷��̾� 
	void SetupTotal(void);				//�¾� Ŀ�� ���� â 
	void SetupHairStyle(void);			//�¾� �Ӹ���Ÿ�� ��ư(���)
	void SetupHairEyeColor(void);			//�¾� �Ӹ� Į�� ��ư
	void SetupEyeStyle(void);			//�¾� �� ��ư
	void SetupMouthStyle(void);			//�¾� �� ��ư
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void OnClick(cUIButton* pSender) override;

	//Ŀ�� ���μ��ù�ư ���ٲٱ�
	void changeButtonColor();
	//��� ��ư ������
	void changeButtonColorHair();

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};