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
	//���
	cUIImageView* m_pCustomHairImageHead;
	cUIImageView* m_pCustomHairImage;
	cUIButton* m_pCustomHairSulastButton;
	cUIButton* m_pCustomHairColorSulastButton;
	cUiObject* m_pCustomHairUi;
	LPD3DXCOLOR m_pHairColor;
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
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void OnClick(cUIButton* pSender) override;

	//Ŀ�� ���� ���ٲٱ�
	void changeButtonColor();

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};