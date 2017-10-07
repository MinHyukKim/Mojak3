#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cAbilityParamter.h"

#define INVMAX 60

//�½�Ʈ
class cFont;
//Ui�½�Ʈ
class cUIImageView;
class cUIImageViewTemp;
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
//	E_ITEM_WEAR = 228,
//	E_ITEM_WEAR1 = 229,
//	E_ITEM_WEAR2 = 230,
//	E_ITEM_WEAR3 = 231,
//	E_ITEM_WEAPON = 232,
//	E_ITEM_WEAPON1 = 233,
//	E_ITEM_WEAPON2 = 234,
//	E_ITEM_SHOES = 235,
	//�ݱ��ư��
	E_BUTTON_INFO_CLOSE = 236,
	E_BUTTON_SKILL_CLOSE = 237,
	E_BUTTON_QUEST_CLOSE = 238,
	E_BUTTON_INVENTORY_CLOSE = 239,
	//��ȭâ ��������Ʈ
	E_IMAGE_DIALOG,
	E_BUTTON_DIALOG_PREV,
	E_BUTTON_DIALOG_NEXT,
	E_TEXT_DIALOG_HEAD,
	E_TEXT_DIALOG,
	E_BUTTON_DIALOG_CLOSE,
	//���� 
	E_BUTTON_EXIT,
	//������
	E_BUTTON_QUICK_01,
	E_BUTTON_QUICK_02,
	E_BUTTON_QUICK_03,
	E_BUTTON_QUICK_04,
	E_BUTTON_QUICK_05,
	E_BUTTON_QUICK_06,
	E_BUTTON_QUICK_07,
	//�� ���
	E_BUTTON_USE_SMASH,
	E_BUTTON_USE_COUNTER,
	E_BUTTON_USE_DEFENSE,
	E_BUTTON_USE_DOWNATTACK,
	E_BUTTON_USE_WINDMILL,
	E_TEXT_VIEW
};

enum ePlayerEquipTorso
{
	E_TORSO_NONE = -2,
	E_TORSO_EMPTY = -1,
	E_TORSO_WEAR_01 = 0,
	E_TORSO_WEAR_02 = 1,
	E_TORSO_WEAR_03 = 2,
};

enum ePlayerEquipShoes
{
	E_SHOES_NONE,
	E_SHOES_EMPTY,
	E_SHOES_01,
	E_SHOES_END,
};

enum ePlaterEquipWeaponHand
{
	E_WEAPON_NONE,
	E_WEAPON_EMPTY,
	E_WEAPON_01,
	E_WEAPON_END,
};

enum eDialogNPC
{
	E_DIALOG_NPC_NONE,
	E_DIALOG_NPC_NAO,
	E_DIALOG_NPC_END
};

enum eDialogText
{
	E_TEXT_NONE,
	E_TEXT_01,
	E_TEXT_02,
	E_TEXT_03,
	E_TEXT_04,
	E_TEXT_05,
	E_TEXR_END
};

//������ ��
enum eQuickSiot01
{
	E_QUICK_SIOT_NONE_01,
	E_QUICK_SIOT_SMASH_01,
	E_QUICK_SIOT_COUNTER_01,
	E_QUICK_SIOT_DEFENSE_01,
	E_QUICK_SIOT_DOWNATTACK_01,
	E_QUICK_SIOT_WINDMILL_01,
	E_QUICK_SIOT_END_01
};
enum eQuickSiot02
{
	E_QUICK_SIOT_NONE_02,
	E_QUICK_SIOT_SMASH_02,
	E_QUICK_SIOT_COUNTER_02,
	E_QUICK_SIOT_DEFENSE_02,
	E_QUICK_SIOT_DOWNATTACK_02,
	E_QUICK_SIOT_WINDMILL_02,
	E_QUICK_SIOT_END_02
};
enum eQuickSiot03
{
	E_QUICK_SIOT_NONE_03,
	E_QUICK_SIOT_SMASH_03,
	E_QUICK_SIOT_COUNTER_03,
	E_QUICK_SIOT_DEFENSE_03,
	E_QUICK_SIOT_DOWNATTACK_03,
	E_QUICK_SIOT_WINDMILL_03,
	E_QUICK_SIOT_END_03
};
enum eQuickSiot04
{
	E_QUICK_SIOT_NONE_04,
	E_QUICK_SIOT_SMASH_04,
	E_QUICK_SIOT_COUNTER_04,
	E_QUICK_SIOT_DEFENSE_04,
	E_QUICK_SIOT_DOWNATTACK_04,
	E_QUICK_SIOT_WINDMILL_04,
	E_QUICK_SIOT_END_04

};
enum eQuickSiot05
{
	E_QUICK_SIOT_NONE_05,
	E_QUICK_SIOT_SMASH_05,
	E_QUICK_SIOT_COUNTER_05,
	E_QUICK_SIOT_DEFENSE_05,
	E_QUICK_SIOT_DOWNATTACK_05,
	E_QUICK_SIOT_WINDMILL_05,
	E_QUICK_SIOT_END_05
};

class cUiTestScene : public cSceneObject, iButtonDelegate
{
private:
	//���� ��Ʈ����
	D3DXMATRIXA16 m_matWorldMatrix;
	RECT m_Wrc;
	//�̵� ���� �Ѹ����� �ɹ�������
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXSPRITE m_pSpriteTemp;
	LPDIRECT3DTEXTURE9 m_pTextureTemp;
	//������ �Ѹ�
	cUIImageView* m_pMainRootImageView;
	cUIButton*	m_pMainRootImageViewMove;
	cUIButton* m_pMinButton;		//ä��ȭ ��ư
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
	//���ο����� �̹��� â
	int m_nMainHPx;
	int m_nMainHPy;
	cUIImageViewTemp* m_pMainHpMaxImage;	//���� �ƽ�
	cUIImageViewTemp* m_pMainHpImage;		 //���� ���緮
	cUITextView* m_pMainHpText;				//���� �ý�Ʈ
	int m_nMainMPx;
	int m_nMainMPy;
	cUIImageViewTemp* m_pMainMpMaxImage;	//������ �ƽ�
	cUIImageViewTemp* m_pMainMpImage;		 //������ ���緮
	cUITextView* m_pMainMpText;				//������ �ý�Ʈ
	int m_nMainStaminaX;
	int m_nMainStaminaY;
	cUIImageViewTemp* m_pMainStaminaMaxImage;	//������ �ƽ�
	cUIImageViewTemp* m_pMainStaminaImage;		 //������ ���緮
	cUITextView* m_pMainStaminaText;			//������ �ý�Ʈ
	int m_nMainEXPx;
	int m_nMainEXPy;
	cUIImageViewTemp* m_pMainEXPMaxImage;	//����ġ�� �ƽ�
	cUIImageViewTemp* m_pMainEXPImage;		 //����ġ�� ���緮
	cUITextView* m_pMainEXPText;			//����ġ�� �ý�Ʈ
	cUITextView* m_pMainLevelText;			//���� �ý�Ʈ
	//������ �Ѹ�
	cUiObject* m_pUiRoot;
	//���� �޴� ����(����)
	cUIButton* m_pUiExitBackImage;
	cUIButton* m_pUiExitButton;
	cUITextView* m_pUiExitText;
	bool m_isExitUiOn;
	cUiObject* m_pUiExit;

	int m_nmainUiLocalY;

	//���� uiƲ ��ġ
	int mainUiLocalX;			//���� Ʋ x
	int mainUiLocalY;			//���� Ʋ y
	int mainButtonH;			//���� ��ư�� ����
	int mainButtoninterval;	//���� ��ư�� ���� ����(ũ��)
	int mainButtonSrart;		//���� ��ư�� ���� ���� ��ġ

	//�÷��̾� ����â
	int infoX;							//���� ������ ��ġx
	int infoY;							//y
	cUIImageView* m_pInfoUiImageHead;	//����â �Ӹ���
	cUIButton* m_pInfoUiMoveing;		//�Ӹ��ٰ� ����ũ���� �̵��� â
	cUIButton* m_pInfoUiImage;			//����â(���� ��ư���� ����)
	cUIButton* m_pInfoCloseButton;		//�ݱ� ��ư
	cUIButton* m_pInfoUiButton;			//��ư
	cUITextView* m_pInfoUiText;			//�Һ� �ý�Ʈ
	//�ӽ�
	cUITextView* m_pTotalInfo;			//����(�½�Ʈ) (X)
	cUITextView* m_pInfoLevel;			//����
	cUITextView* m_pInfoEXP;			//����ġ
	cUITextView* m_pInfoAP;				//AP
	cUITextView* m_pInfoAdventureLevel; //Ž�跹��
	cUITextView* m_pInfodventureEXP;	//Ž�����ġ
	cUITextView* m_pTempInfoHP;			//Hp
	cUITextView* m_pTempInfoMP;			//Mp
	cUITextView* m_pTempInfoStamina;	//���׹̳�
	cUITextView* m_pTempInfoSTR;		//ü��
	cUITextView* m_pTempInfoINT;		//����
	cUITextView* m_pTempInfoWill;		//����
	cUITextView* m_pTempInfoLuck;		//���
	cUITextView* m_pTempInfoWorkmanship;//�ؾ�
	cUITextView* m_pTempInfoDamage;		//���ݷ�
	cUITextView* m_pTempInfoMagicDamage;//�������ݷ�
	cUITextView* m_pTempInfoInjury;		//�λ��з�
	cUITextView* m_pTempInfoCritical;	//ũ��Ƽ��
	cUITextView* m_pTempInfoBalance;	//������
	cUITextView* m_pTempInfoDefense;	//���
	cUITextView* m_pTempInfoProtect;	//��ȣ
	cUITextView* m_pTempInfoMagicDefense;//�������
	cUITextView* m_pTempInfoMagicProtect;//������ȣ
	cUITextView* m_pTempInfoArmorPiercing;//������
	//�÷��̾� ���� �̹���
	cUIImageViewTemp* m_pHpMaxImage;	//���� �ƽ�
	cUIImageViewTemp* m_pHpImage;		 //���� ���緮
	//������ �̹���
	cUIImageViewTemp* m_pMpMaxImage;	//������ �ƽ�
	cUIImageViewTemp* m_pMpImage;		 //������ ���緮
	//���¹̳� �̹���
	cUIImageViewTemp* m_pStaminaMaxImage;	//������ �ƽ�
	cUIImageViewTemp* m_pStaminaImage;		 //������ ���緮
	//����ġ �̹���
	cUIImageViewTemp* m_pEXPMaxImage;	//����ġ�� �ƽ�
	cUIImageViewTemp* m_pEXPImage;		 //����ġ�� ���緮
	//���� ui�Ѹ�
	cUiObject* m_pInfoUi;
	
	//�÷��̾� ��ųâ
	int skillX;
	int skillY;
	cUIImageView* m_pSkillUiImageHead;	//��ųâ �Ӹ���	
	cUIButton* m_pSkillUiMoveing;		//�Ӹ��� �̵��� 
	cUIButton* m_pSkillUiImage;			//��ųâ �̹���
	cUIButton* m_pSkillCloseButton;		//�ݱ� ��ư
	cUIButton* m_pSkillUiButton;		//��ųâ ��ư
	cUITextView* m_pSkillUiText;		//�Һ� �ý�Ʈ

	cUIButton* m_pSkillSmash;			//������ų ���޽�
	cUIButton* m_pSkillCounter;			//������ų ī����
	cUIButton* m_pSkillDefense;			//������ų ���潺
	cUIButton* m_pSkillDownAttack;		//������ų �ٿ����
	cUIButton* m_pSkillWindmill;		//���� ��ų �����
	cUIButton* m_pSkillCombat;			//�Ĺ� �����͸�

	cUIImageViewTemp* m_pSkillExpMax;			//��ų ����ġ��
	cUIImageViewTemp* m_pSkillExpSmash;			
	cUIImageViewTemp* m_pSkillExpCounter;
	cUIImageViewTemp* m_pSkillExpDefense;
	cUIImageViewTemp* m_pSkillExpDownAttack;
	cUIImageViewTemp* m_pSkillExpWindmill;
	cUIImageViewTemp* m_pSkillExpCombat;

	//ap����
	cUITextView* m_pSKillLevelSmash;
	cUITextView* m_pSKillLevelCounter;
	cUITextView* m_pSKillLevelDefense;
	cUITextView* m_pSKillLevelDownAttack;
	cUITextView* m_pSKillLevelWindmill;
	cUITextView* m_pSKillLevelCombat;
	//cUIButton* m_pTraining

	cUiObject* m_pSkillUi;		

	//��ȭ����
	int m_nDialogX;
	int m_nDialogY;
	bool m_isDialogOpen;			//���â ��/����
	cUIButton* m_pDialogBackImage;  //��� â �̹���
	cUITextView* m_pDialogNameText;	//NPC �̸�	
	cUITextView* m_pDialogText;		//��ȭ ����
	cUIButton* m_pDialogPrev;		//������ư
	cUITextView* pDialogPrevText;
	cUIButton* m_pDialogNext;		//���� ��ư
	cUITextView* pDialogNextText;
	cUIButton* m_pDialogAcceptButton; //���� ���� ��ư
	cUIButton* m_pDialogCloseButton;  //�ݱ� ��ư
	bool m_isDialogFin;					//��ȭ ��(�Ⱦ�
	eDialogNPC m_eDialogNPCKind;		//��ȭ���� NPC(������ NPC) ����
	int m_nDialogTextNum;				//�ý�Ʈ ����
	eDialogText m_eDialogText;			//�ý�Ʈ ����
	cUiObject* m_pDialogUi;			

	//����Ʈ ����â
	int queX;
	int queY;
	cUIImageView* m_pQuestUiImageHead;	//���â �Ӹ���	
	cUIButton* m_pQuestUiMoveing;		//�Ӹ��� �̵��� 
	cUIButton* m_pQuestUiImage;			//��â �̹���
	cUIButton* m_pQuestCloseButton;		//�ݱ� ��ư
	cUIButton* m_pQuestUiButton;		//��â ��ư
	cUITextView* m_pQuestUiText;		//�Һ� �ý�Ʈ
	cUITextView* m_pQuestText;			//�½�Ʈ�� �ý�Ʈ
	cUiObject* m_pQuestUi;

	//�÷��̾� �κ�â
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;	//�κ�â �Ӹ���
	cUIButton* m_pInventoryUiMoveing;		//�̵��� �Ӹ���
	cUIButton* m_pInventoryUiImage;			//�κ� â
	cUIButton* m_pInventoryUiEquipImage;	//���� â
	cUIButton* m_pInventoryCloseButton;		//�ݱ� ��ư
	cUITextView* m_pInventoryUiText;		//�Һ� �ý�Ʈ
	//ĭ ��
	vector<cUIButton*> m_vecInventoryUiBlock;	//�κ��丮 ĭ(����)(x)
	D3DXVECTOR3 m_vItemPrevPos;
	cUIButton* m_pInventoryUiBlock[INVMAX];		//�κ��丮 ĭ(����ǰ)
	cUIButton* m_pQInventoryUiButton;			//�κ� ��ư
	cUiObject* m_pInventoryUi;
	//��� �ڸ� ǥ��
	cUIButton* m_pInventoryUiEquipTorso;			//���� ĭ
	int m_isTorsoMount;								//���� ���� ����
	cUIButton* m_pInventoryUiEquipWeaponHand;		//���� �� ĭ
	bool m_isWeaponHandMount;						//���� �� ���� ����
	cUIButton* m_pInventoryUiEquipSubHand;			//���� �� ĭ
	bool m_isSubHandMount;							//���� �� ���� ����
	cUIButton* m_pInventoryUiEquipShoes;			//�Ź� �� ĭ
	int m_isShoesMount;							//�Ź� ��������
	//������ �Ⱦ� ����
	bool isPickUpItem;				//������ �Ⱦ� ����(��� �ø���)

	//�����Ե�
	cUIButton* m_pUiQuickSiot1;
	cUIButton* m_pUiQuickSiot2;
	cUIButton* m_pUiQuickSiot3;
	cUIButton* m_pUiQuickSiot4;
	cUIButton* m_pUiQuickSiot5;
	cUIButton* m_pUiQuickSiot6;
	cUIButton* m_pUiQuickSiot7;
	cUiObject* m_pUiQuickSiot;
	bool m_isSiot01;
	bool m_isSiot02;
	bool m_isSiot03;
	bool m_isSiot04;
	bool m_isSiot05;
	eQuickSiot01 m_eQuickSiot01;
	eQuickSiot02 m_eQuickSiot02;
	eQuickSiot03 m_eQuickSiot03;
	eQuickSiot04 m_eQuickSiot04;
	eQuickSiot05 m_eQuickSiot05;

	//�г� �̹��� ũ�� �½�Ʈ��
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;	
	cUIImageViewTemp* test;

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

	std::vector<cUIButton*> m_vecTempPlayerItem;
	int m_nItemMax;
	cUIButton* m_pTempPlayerItemArr[INVMAX];
	//�����Ƽ
	cAbilityParamter m_AbilityParamter;
	//��ġ ����
	int m_nBasicDef;
	int m_nWearDef;
	int m_nShoesDef;

public:
	virtual HRESULT Setup(void) override;
	void SetupBaseButton(void);
	void SetupInfoUi(void);
	void SetupSkillUi(void);
	void SetupQuestUi(void);
	void SetupInventoryUi(void);
	void SetupDialogUi(void);
	void SetUpTempPlayer(void);
	void AddItem(LPCSTR imgName, float x, float y, int itemType, int itemName);
	virtual void Reset(void) override;
	virtual void Update(void) override;
	void UpdateMainUi(void);
	void UpdateInfoUi(void);
	void UpdateSkillUi(void);
	void MoveUiWindow(void);
	void _ItemInventory(int i);
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
	//��ư �̹��� �����Լ�
	void changeMainButtonColor(void);
	//�κ��丮 �̹��� ���� �Լ�
	void changeInventoryImage(void);
	//�Ž� ���� �Լ�
	void changePlayerMesh(void);
	//��� ���� �Լ�
	void changeDialogText(void);

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
	//��ȭâ ���� �ݱ�
	bool GetDialogOpen() { return m_isDialogOpen; }
	void SetDialogOpen(bool is) { m_isDialogOpen = is; }

	//��� ���� �̳ѹ�
	ePlayerEquipTorso m_eEquipTorso;
	ePlayerEquipShoes m_eEquipShoes;
	ePlaterEquipWeaponHand m_eEquipWeaponHand;

	//�����Ƽ ����
	cAbilityParamter* GetAbilityParamter(void) { return &m_AbilityParamter; }

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};