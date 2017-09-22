#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//태스트
class cFont;
//Ui태스트
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

enum
{
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
	//드래그 태스트
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
	//이동 가변 뿌리들은 맴버변수로
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
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
	cUIImageView* m_pInfoUiImageHead;
	cUIImageView* m_pInfoUiImage;
	cUIButton* m_pInfoUiButton;
	cUiObject* m_pInfoUi;

	//플레이어 스킬창
	cUIImageView* m_pSkillUiImageHead;
	cUIImageView* m_pSkillUiImage;
	cUIButton* m_pSkillUiButton;
	cUiObject* m_pSkillUi;

	//퀘스트 정보창
	cUIImageView* m_pQuestUiImageHead;
	cUIImageView* m_pQuestUiImage;
	cUIButton* m_pQuestUiButton;
	cUiObject* m_pQuestUi;

	//플레이어 인벤창
	int invX;
	int invY;
	cUIImageView* m_pInventoryUiImageHead;
	cUIButton* m_pInventoryUiMoveing;
	cUIImageView* m_pInventoryUiImage;
	cUIImageView* m_pInventoryUiTempImage;
	cUIButton* m_pQInventoryUiButton;
	cUiObject* m_pInventoryUi;
	
	//패널 이미지 크기 태스트용
	cUiObject* m_pUiTestRoot;
	cUIImageView* m_pUiTesterSize;

	//왼쪽 버튼 다운 여부
	bool m_isLbuttonDown;
	//메인 창 최소화 변수
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
	//버튼 이미지 변경함수
	void changeMainButtonColor(void);

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};