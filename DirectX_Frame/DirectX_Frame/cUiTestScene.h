#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//�½�Ʈ
class cFont;
//Ui�½�Ʈ
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

enum
{
	E_BUTTON_NONE,
	//���� ��ư��
	E_MAIN_BUTTON_PLAYER_INFO = 213,
	E_MAIN_BUTTON_SKILL = 214,
	E_MAIN_BUTTON_QUEST = 215,
	E_MAIN_BUTTON_INVENTORY = 216,
	E_MAIN_BUTTON_ABILITY = 217,
	E_MAIN_BUTTON_ACTION = 218,
	E_MAIN_BUTTON_PET = 219,
	E_MAIN_BUTTON_MESSENGER = 220,
	E_MAIN_BUTTON_MIN = 221,
	E_MAIN_BUTTON_MAIN = 222,
	//�巡�� �½�Ʈ(x)
	E_INFO_MOVE = 223,
	E_SKILL_MOVE = 224,
	E_QUEST_MOVE = 225,
	E_INVENTORY_MOVE = 226,
	//�½�Ʈ��
	E_BUTTON_TEST1 = 227,
	E_TEXT_VIEW
	
};

class cUiTestScene : public cSceneObject, iButtonDelegate
{
private:
	//�̵� ���� �Ѹ����� �ɹ�������
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	//������ �Ѹ�
	cUIImageView* m_pMainRootImageView;
	cUiObject* m_pUiRoot;
	cUIButton* m_pMainMainButton; 	//����
	bool m_isMainWindowOn;
	cUIButton* m_pInfoButton;		//����
	bool m_isInfoWindowOn;
	cUIButton* m_pSkillButton;		//��ų
	bool m_isSkillWindowOn;
	cUIButton* m_pQuestButton;		//����Ʈ
	bool m_isQuestWindowOn;
	cUIButton* m_pInventoryButton;	//�κ�
	bool m_isInventoryWindowOn;

	int m_nmainUiLocalY;

	//���� uiƲ ��ġ
	int mainUiLocalX = 300;			//���� Ʋ x
	int mainUiLocalY = 502;			//���� Ʋ y
	int mainButtonH = -25;			//���� ��ư�� ����
	int mainButtoninterval = 40;	//���� ��ư�� ���� ����(ũ��)
	int mainButtonSrart = 160;		//���� ��ư�� ���� ���� ��ġ

	//�÷��̾� ����â
	int infoX;
	int infoY;
	cUIImageView* m_pInfoUiImageHead;
	cUIButton* m_pInfoUiMoveing;
	cUIImageView* m_pInfoUiImage;
	cUIButton* m_pInfoUiButton;
	cUiObject* m_pInfoUi;

	//�÷��̾� ��ųâ
	int skillX;
	int skillY;
	cUIImageView* m_pSkillUiImageHead;
	cUIButton* m_pSkillUiMoveing;
	cUIImageView* m_pSkillUiImage;
	cUIButton* m_pSkillUiButton;
	cUiObject* m_pSkillUi;

	//����Ʈ ����â
	int queX;
	int queY;
	cUIImageView* m_pQuestUiImageHead;
	cUIButton* m_pQuestUiMoveing;
	cUIImageView* m_pQuestUiImage;
	cUIButton* m_pQuestUiButton;
	cUiObject* m_pQuestUi;

	//�÷��̾� �κ�â
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;
	cUIButton* m_pInventoryUiMoveing;
	cUIButton* m_pInventoryUiImage;
	//�ӽ� ĭ�� ǥ��
	cUIImageView* m_pInventoryUiTempImage;
	//ĭ ��
	vector<cUIButton*> m_vecInventoryUiBlock;
	cUIButton* m_pInventoryUiBlock[60];
	cUIButton* m_pQInventoryUiButton;
	cUiObject* m_pInventoryUi;
	//��� �ڸ� ǥ��
	cUIButton* m_pInventoryUiEquipTorso;
	cUIButton* m_pInventoryUiEquipWeaponHand;
	cUIButton* m_pInventoryUiEquipSubHand;
	cUIButton* m_pInventoryUiEquipShoes;
	//������ �Ⱦ� ����
	bool isPickUpItem;
	//�г� �̹��� ũ�� �½�Ʈ��
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;

	//���� ��ư �ٿ� ����
	bool m_isLbuttonDown;
	//���� â �ּ�ȭ ����
	bool m_isMainMin;
	//���콺 ������ �ޱ��
	POINT m_ptMouse;

	//�ӽÿ� (���߿� ������ �ٽ� �ޱ�)
	cUIButton* m_pTempItem;

public:
	virtual HRESULT Setup(void) override;
	void SetupBaseButton(void);
	void SetupInfoUi(void);
	void SetupSkillUi(void);
	void SetupQuestUi(void);
	void SetupInventoryUi(void);
	virtual void Reset(void) override;
	virtual void Update(void) override;
	void MoveUiWindow(void);
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
	//��ư �̹��� �����Լ�
	void changeMainButtonColor(void);

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};