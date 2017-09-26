#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cAbilityParamter.h"

//태스트
class cFont;
//Ui태스트
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;
//임시 플레이어
class cPlayer;
class cCamera;
class cImage;

enum
{
	E_BUTTON_NONE,
//	E_TORSO
	//메인 버튼들
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
	//드래그 태스트(x)
	E_INFO_MOVE = 223,
	E_SKILL_MOVE = 224,
	E_QUEST_MOVE = 225,
	E_INVENTORY_MOVE = 226,
	//인벤토리 태스트용
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
	//월드 메트릭스
	D3DXMATRIXA16 m_matWorldMatrix;

	//이동 가변 뿌리들은 맴버변수로
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXSPRITE m_pSpriteTemp;
	LPDIRECT3DTEXTURE9 m_pTextureTemp;
	//매인의 뿌리
	cUIImageView* m_pMainRootImageView;
	cUiObject* m_pUiRoot;
	cUIButton* m_pMainMainButton; 	//메인
	bool m_isMainWindowOn;
	cUIButton* m_pInfoButton;		//정보
	bool m_isInfoWindowOn;
	cUIButton* m_pSkillButton;		//스킬
	bool m_isSkillWindowOn;
	cUIButton* m_pQuestButton;		//퀘스트
	bool m_isQuestWindowOn;
	cUIButton* m_pInventoryButton;	//인벤
	bool m_isInventoryWindowOn;

	int m_nmainUiLocalY;

	//메인 ui틀 위치
	int mainUiLocalX = 300;			//메인 틀 x
	int mainUiLocalY = 502;			//메인 틀 y
	int mainButtonH = -25;			//메인 버튼들 높이
	int mainButtoninterval = 40;	//메인 버튼들 가로 간격(크기)
	int mainButtonSrart = 160;		//메인 버튼들 최초 시작 위치

	//플레이어 정보창
	int infoX;							//최초 윈도우 위치x
	int infoY;							//y
	cUIImageView* m_pInfoUiImageHead;	//정보창 머리줄
	cUIButton* m_pInfoUiMoveing;		//머리줄과 동일크기의 이동용 창
	cUIButton* m_pInfoUiImage;			//정보창(추후 버튼으로 수정)
	cUIButton* m_pInfoUiButton;			//버튼
	cUITextView* m_pInfoUiText;			//불변 택스트
	//임시
	cUITextView* m_pTotalInfo;			//종합(태스트) (X)
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
	//플레이어 피통
	cImage* m_pHpMaxImage;   //피통 맥스
	cImage* m_pHpImage;		 //피통 현재량
	D3DXIMAGE_INFO m_stHpBar;
	cUiObject* m_pInfoUi;
	
	//플레이어 스킬창
	int skillX;
	int skillY;
	cUIImageView* m_pSkillUiImageHead;	//스킬창 머리줄	
	cUIButton* m_pSkillUiMoveing;		//머리줄 이동용 
	cUIButton* m_pSkillUiImage;			//스킬창 이미지
	cUIButton* m_pSkillUiButton;		//스킬창 버튼
	cUITextView* m_pSkillUiText;		//불변 택스트
	cUiObject* m_pSkillUi;

	//퀘스트 정보창
	int queX;
	int queY;
	cUIImageView* m_pQuestUiImageHead;	//스킬창 머리줄	
	cUIButton* m_pQuestUiMoveing;		//머리줄 이동용 
	cUIButton* m_pQuestUiImage;			//스킬창 이미지
	cUIButton* m_pQuestUiButton;		//스킬창 버튼
	cUITextView* m_pQuestUiText;		//불변 택스트
	cUiObject* m_pQuestUi;

	//플레이어 인벤창
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;	//인벤창 머리줄
	cUIButton* m_pInventoryUiMoveing;		//이동용 머리줄
	cUIButton* m_pInventoryUiImage;			//인벤 창
	cUITextView* m_pInventoryUiText;		//불변 택스트
	//칸 수
	vector<cUIButton*> m_vecInventoryUiBlock;	//안씀
	cUIButton* m_pInventoryUiBlock[60];			//인벤토리 칸(소지품)
	cUIButton* m_pQInventoryUiButton;			//인벤 버튼
	cUiObject* m_pInventoryUi;
	//장비 자리 표시
	cUIButton* m_pInventoryUiEquipTorso;			//몸통 칸
	bool m_isTorsoMount;							//몸통 장착 여부
	cUIButton* m_pInventoryUiEquipWeaponHand;		//무기 손 칸
	bool m_isWeaponHandMount;						//무기 손 장착 여부
	cUIButton* m_pInventoryUiEquipSubHand;			//서브 손 칸
	bool m_isSubHandMount;							//서브 손 장착 여부
	cUIButton* m_pInventoryUiEquipShoes;			//신발 손 칸
	bool m_isShoesMount;							//신발 장착여부
	//아이탬 픽업 여부
	bool isPickUpItem;				//아이탬 픽업 여부(찍고 올리기)
	//패널 이미지 크기 태스트용
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;	

	//왼쪽 버튼 다운 여부
	bool m_isLbuttonDown;
	//메인 창 최소화 변수
	bool m_isMainMin;
	//마우스 음직임 받기용
	POINT m_ptMouse;

	//임시 플레이어
	//플레이어 보여주기
	cPlayer* m_pPlayer;
	cSkinnedMesh* pSkinMesh;
	//임시 캐매라
	cCamera* m_pMainCamera;
	//임시 스탯
	int m_nTempMaxHP; int m_nTempHP;  //피통
	int m_nTempMaxMP; int m_nTempMP;  //마나통
	int m_nTempMaxStamina, nTempStamina;	//스태미나
	int m_nTempSTR;						//체력
	int m_nTempINT;						//지력
	int m_nTempWill;					//의지	
	int m_nTempLuck;					//행운
	int m_nTempWorkmanship;				//솜씨
	int m_nTempTotalDamage, m_nTempMinDamage, m_nTempMaxDamage, m_nTempDamege; //공격렬
	int m_nTempTotalMagicDamage, m_nTempMaxMagicDamagel, m_nTempMinMagicDamagel, m_nTempMagicDamege; //마공
	float m_fTempInjury;	//부상확률
	float m_fTempCritical;			//크리
	int m_nTempBalance;					//벨런스
	int m_nTempDefense;				//방어
	int m_nTempProtect;				//보호
	int m_nTempMagicDefense;		//마방
	int m_nTempMagicProtect;		//마법보호
	int m_nTempArmorPiercing;		//방관

	std::vector<cUIButton*> m_pTempItem;
	std::vector<cUIButton*> m_pTempBsg;

	//어빌리티
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
	//버튼 이미지 변경함수
	void changeMainButtonColor(void);
	//인벤토리 이미지 변경 함수
	void changeInventoryImage(void);

	//ui 열림 주고 받기용
	bool GetInfoOnOff(void) { return m_isInfoWindowOn; }
	void SetInfoOnOff(bool is) { m_isInfoWindowOn = is; }
	bool GetSkillOnOff(void) { return m_isSkillWindowOn; }
	void SetSkillOnOff(bool is) { m_isSkillWindowOn = is; }
	bool GetQuestOnOff(void) { return m_isQuestWindowOn; }
	void SetQuestOnOff(bool is) { m_isQuestWindowOn = is; }
	bool GetInventoryOnOff(void) { return m_isInventoryWindowOn; }
	void SetInventoryOnOff(bool is) { m_isInventoryWindowOn = is; }
	//마우스 오버 함수
	bool GetMoveingOK();
	

	//어빌리티 연동
	cAbilityParamter* GetAbilityParamter(void) { return &m_AbilityParamter; }

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};