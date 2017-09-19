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
//�÷��̾� ����
class cPlayer;
class cCamera;

//��ư ��������Ʈ �̳ѹ�
enum
{
	E_SERVER_TEXT_NEXT,
	E_SERVER_TEXT_CANCEL,

	E_TEXT_CUSTOM_NAME,

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
	//��� Į�� ����Ʈ
	E_HAIR_COLOR_SELECT_01 = 225,
	E_HAIR_COLOR_SELECT_02 = 226,
	E_HAIR_COLOR_SELECT_03 = 227,
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

enum eCustomizingHair
{

};
enum eCustomizingEye
{

};
enum eCustomizingMouth
{

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
	//���� ���� â
	cUIImageView* m_pServerSulastHeadImage;
	cUIImageView* m_pServerSulastImage;
	cUIButton* m_pServerSulastButton;
	cUITextView* m_pServerTextNext;
	cUITextView* m_pServerTextCancel;
	cUiObject* m_pServerSulastUi;

	//�̸� �Է� â
	cUIImageView* m_pNameImageHead;
	cUIImageView* m_pNameImage;
	cUIButton* m_pNameButton;
	cUiObject* m_pNameUi;

	//Ŀ��...
	eCustomizingTab m_eCustomizingTab;
	//Ʋ
	cUIImageView* m_pCustomImageHead;
	cUIImageView* m_pCustomImage;
	cUIButton* m_pCustomButtonHair;
	cUIButton* m_pCustomButtonEye;
	cUIButton* m_pCustomButtonMouth;
	cUIButton* m_pCustomButton;
	cUiObject* m_pCustomUi;
	//�۾�
	cUITextView* m_pCustomNameTest;
	//���
	cUIImageView* m_pCustomHairImageHead;
	cUIImageView* m_pCustomHairImage;
	cUIButton* m_pCustomHairSulastButton;
	cUIButton* m_pCustomHairColorSulastButton;
	cUiObject* m_pCustomHairUi;
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

	//���콺
	bool m_isLButtonDown;
	POINT m_ptMouse;
	POINT m_ptPrevMouse;

public:
	virtual HRESULT Setup(void) override;	
	void SetupPlayer(void);				//�¾� �÷��̾� 
	void SetupTotal(void);				//�¾� Ŀ�� ���� â 
	void SetupHairStyle(void);			//�¾� �Ӹ���Ÿ�� ��ư(���)
	void SetupHairColor(void);			//�¾� �Ӹ� Į�� ��ư
	void SetupEyeStyle(void);			//�¾� �� ��ư
	void SetupMouthStyle(void);			//�¾� �� ��ư
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void OnClick(cUIButton* pSender) override;

	//Ŀ�� ���μ��ù�ư ���ٲٱ�
	void changeButtonColor();

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};