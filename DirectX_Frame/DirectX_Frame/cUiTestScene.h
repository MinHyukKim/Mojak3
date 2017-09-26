#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cAbilityParamter.h"

//�½�Ʈ
class cFont;
//Ui�½�Ʈ
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;
//�ӽ� �÷��̾�
class cPlayer;
class cCamera;
class cImage;

enum
{
	E_BUTTON_NONE,
//	E_TORSO
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
	//�κ��丮 �½�Ʈ��
	E_BUTTON_TEST1 = 227,
	E_ITEM_WEAR = 228,
	E_ITEM_WEAR1 = 229,
	E_ITEM_WEAR2 = 230,
	E_ITEM_WEAR3 = 231,
	E_ITEM_WEAPON = 232,
	E_ITEM_WEAPON1 = 233,
	E_ITEM_WEAPON2 = 234,
	E_ITEM_SHOES = 235,
	E_TEXT_VIEW
};

class cUiTestScene : public cSceneObject, iButtonDelegate
{
private:
	//���� ��Ʈ����
	D3DXMATRIXA16 m_matWorldMatrix;

	//�̵� ���� �Ѹ����� �ɹ�������
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXSPRITE m_pSpriteTemp;
	LPDIRECT3DTEXTURE9 m_pTextureTemp;
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
	int infoX;							//���� ������ ��ġx
	int infoY;							//y
	cUIImageView* m_pInfoUiImageHead;	//����â �Ӹ���
	cUIButton* m_pInfoUiMoveing;		//�Ӹ��ٰ� ����ũ���� �̵��� â
	cUIButton* m_pInfoUiImage;			//����â(���� ��ư���� ����)
	cUIButton* m_pInfoUiButton;			//��ư
	cUITextView* m_pInfoUiText;			//�Һ� �ý�Ʈ
	//�ӽ�
	cUITextView* m_pTotalInfo;			//����(�½�Ʈ) (X)
	cUITextView* m_pTempInfoHP;
	cUITextView* m_pTempInfoMP;
	cUITextView* m_pTempInfoStamina;
	cUITextView* m_pTempInfoSTR;
	cUITextView* m_pTempInfoINT;
	cUITextView* m_pTempInfoWill;
	cUITextView* m_pTempInfoLuck;
	cUITextView* m_pTempInfoWorkmanship;
	cUITextView* m_pTempInfoDamage;
	cUITextView* m_pTempInfoMagicDamage;
	cUITextView* m_pTempInfoInjury;
	cUITextView* m_pTempInfoCritical;
	cUITextView* m_pTempInfoBalance;
	cUITextView* m_pTempInfoDefense;
	cUITextView* m_pTempInfoProtect;
	cUITextView* m_pTempInfoMagicDefense;
	cUITextView* m_pTempInfoMagicProtect;
	cUITextView* m_pTempInfoArmorPiercing;
	//�÷��̾� ����
	cImage* m_pHpMaxImage;   //���� �ƽ�
	cImage* m_pHpImage;		 //���� ���緮
	D3DXIMAGE_INFO m_stHpBar;
	cUiObject* m_pInfoUi;
	
	//�÷��̾� ��ųâ
	int skillX;
	int skillY;
	cUIImageView* m_pSkillUiImageHead;	//��ųâ �Ӹ���	
	cUIButton* m_pSkillUiMoveing;		//�Ӹ��� �̵��� 
	cUIButton* m_pSkillUiImage;			//��ųâ �̹���
	cUIButton* m_pSkillUiButton;		//��ųâ ��ư
	cUITextView* m_pSkillUiText;		//�Һ� �ý�Ʈ
	cUiObject* m_pSkillUi;

	//����Ʈ ����â
	int queX;
	int queY;
	cUIImageView* m_pQuestUiImageHead;	//��ųâ �Ӹ���	
	cUIButton* m_pQuestUiMoveing;		//�Ӹ��� �̵��� 
	cUIButton* m_pQuestUiImage;			//��ųâ �̹���
	cUIButton* m_pQuestUiButton;		//��ųâ ��ư
	cUITextView* m_pQuestUiText;		//�Һ� �ý�Ʈ
	cUiObject* m_pQuestUi;

	//�÷��̾� �κ�â
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;	//�κ�â �Ӹ���
	cUIButton* m_pInventoryUiMoveing;		//�̵��� �Ӹ���
	cUIButton* m_pInventoryUiImage;			//�κ� â
	cUITextView* m_pInventoryUiText;		//�Һ� �ý�Ʈ
	//ĭ ��
	vector<cUIButton*> m_vecInventoryUiBlock;	//�Ⱦ�
	cUIButton* m_pInventoryUiBlock[60];			//�κ��丮 ĭ(����ǰ)
	cUIButton* m_pQInventoryUiButton;			//�κ� ��ư
	cUiObject* m_pInventoryUi;
	//��� �ڸ� ǥ��
	cUIButton* m_pInventoryUiEquipTorso;			//���� ĭ
	bool m_isTorsoMount;							//���� ���� ����
	cUIButton* m_pInventoryUiEquipWeaponHand;		//���� �� ĭ
	bool m_isWeaponHandMount;						//���� �� ���� ����
	cUIButton* m_pInventoryUiEquipSubHand;			//���� �� ĭ
	bool m_isSubHandMount;							//���� �� ���� ����
	cUIButton* m_pInventoryUiEquipShoes;			//�Ź� �� ĭ
	bool m_isShoesMount;							//�Ź� ��������
	//������ �Ⱦ� ����
	bool isPickUpItem;				//������ �Ⱦ� ����(��� �ø���)
	//�г� �̹��� ũ�� �½�Ʈ��
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;	

	//���� ��ư �ٿ� ����
	bool m_isLbuttonDown;
	//���� â �ּ�ȭ ����
	bool m_isMainMin;
	//���콺 ������ �ޱ��
	POINT m_ptMouse;

	//�ӽ� �÷��̾�
	//�÷��̾� �����ֱ�
	cPlayer* m_pPlayer;
	cSkinnedMesh* pSkinMesh;
	//�ӽ� ĳ�Ŷ�
	cCamera* m_pMainCamera;
	//�ӽ� ����
	int m_nTempMaxHP; int m_nTempHP;  //����
	int m_nTempMaxMP; int m_nTempMP;  //������
	int m_nTempMaxStamina, nTempStamina;	//���¹̳�
	int m_nTempSTR;						//ü��
	int m_nTempINT;						//����
	int m_nTempWill;					//����	
	int m_nTempLuck;					//���
	int m_nTempWorkmanship;				//�ؾ�
	int m_nTempTotalDamage, m_nTempMinDamage, m_nTempMaxDamage, m_nTempDamege; //���ݷ�
	int m_nTempTotalMagicDamage, m_nTempMaxMagicDamagel, m_nTempMinMagicDamagel, m_nTempMagicDamege; //����
	float m_fTempInjury;	//�λ�Ȯ��
	float m_fTempCritical;			//ũ��
	int m_nTempBalance;					//������
	int m_nTempDefense;				//���
	int m_nTempProtect;				//��ȣ
	int m_nTempMagicDefense;		//����
	int m_nTempMagicProtect;		//������ȣ
	int m_nTempArmorPiercing;		//���

	std::vector<cUIButton*> m_pTempItem;
	std::vector<cUIButton*> m_pTempBsg;

	//�����Ƽ
	cAbilityParamter m_AbilityParamter;

public:
	virtual HRESULT Setup(void) override;
	void SetupBaseButton(void);
	void SetupInfoUi(void);
	void SetupSkillUi(void);
	void SetupQuestUi(void);
	void SetupInventoryUi(void);
	void SetUpTempPlayer(void);
	virtual void Reset(void) override;
	virtual void Update(void) override;
	void UpdateInfoUi(void);
	void MoveUiWindow(void);
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
	//��ư �̹��� �����Լ�
	void changeMainButtonColor(void);
	//�κ��丮 �̹��� ���� �Լ�
	void changeInventoryImage(void);

	//ui ���� �ְ� �ޱ��
	bool GetInfoOnOff(void) { return m_isInfoWindowOn; }
	void SetInfoOnOff(bool is) { m_isInfoWindowOn = is; }
	bool GetSkillOnOff(void) { return m_isSkillWindowOn; }
	void SetSkillOnOff(bool is) { m_isSkillWindowOn = is; }
	bool GetQuestOnOff(void) { return m_isQuestWindowOn; }
	void SetQuestOnOff(bool is) { m_isQuestWindowOn = is; }
	bool GetInventoryOnOff(void) { return m_isInventoryWindowOn; }
	void SetInventoryOnOff(bool is) { m_isInventoryWindowOn = is; }
	//���콺 ���� �Լ�
	bool GetMoveingOK();
	

	//�����Ƽ ����
	cAbilityParamter* GetAbilityParamter(void) { return &m_AbilityParamter; }

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};