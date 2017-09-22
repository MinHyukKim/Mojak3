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
	//�巡�� �½�Ʈ
	E_INVENTORY_MOVE = 224,
	E_TEXT_VIEW
	
};
enum eMoveUi
{
	E_MOVE_NONE,
	E_MOVE_INVENTORY,
	E_MOVE_END
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
	cUIImageView* m_pInfoUiImageHead;
	cUIImageView* m_pInfoUiImage;
	cUIButton* m_pInfoUiButton;
	cUiObject* m_pInfoUi;

	//�÷��̾� ��ųâ
	cUIImageView* m_pSkillUiImageHead;
	cUIImageView* m_pSkillUiImage;
	cUIButton* m_pSkillUiButton;
	cUiObject* m_pSkillUi;

	//����Ʈ ����â
	cUIImageView* m_pQuestUiImageHead;
	cUIImageView* m_pQuestUiImage;
	cUIButton* m_pQuestUiButton;
	cUiObject* m_pQuestUi;

	//�÷��̾� �κ�â
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;
	cUIButton* m_pInventoryUiMoveing;
	cUIImageView* m_pInventoryUiImage;
	cUIImageView* m_pInventoryUiTempImage;
	cUIButton* m_pQInventoryUiButton;
	cUiObject* m_pInventoryUi;
	
	//�г� �̹��� ũ�� �½�Ʈ��
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;

	//���� ��ư �ٿ� ����
	bool m_isLbuttonDown;
	//���� â �ּ�ȭ ����
	bool m_isMainMin;

	POINT m_ptMouse;
	eMoveUi e_move;

public:
	virtual HRESULT Setup(void) override;
	void SetupBaseButton(void);
	void SetupInventoryUi(void);
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
	virtual void OnMouseOver(cUIButton* pSender) override;
	//��ư �̹��� �����Լ�
	void changeMainButtonColor(void);

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};