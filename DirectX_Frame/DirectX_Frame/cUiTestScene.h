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
	E_TEXT_VIEW
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
	cUIButton* m_pMainMainButton;
	bool m_isMainWindowOn;
	cUIButton* m_pInfoButton;
	bool m_isInfoWindowOn;
	cUIButton* m_pSkillButton;
	bool m_isSkillWindowOn;
	cUIButton* m_pQuestButton;
	bool m_isQuestWindowOn;
	cUIButton* m_pInventoryButton;
	bool m_isInventoryWindowOn;
	int m_nmainUiLocalY;

	//메인 ui틀 위치
	int mainUiLocalX = 300;			//메인 틀 x
	int mainUiLocalY = 502;			//메인 틀 y

	int mainButtonH = -25;			//메인 버튼들 높이
	int mainButtoninterval = 40;	//메인 버튼들 가로 간격(크기)
	int mainButtonSrart = 160;		//메인 버튼들 최초 시작 위치


	//안씀
	cUiObject* m_pUiTestRoot;
	//패널 이미지 크기 태스트용
	cUIImageView* m_pUiTesterSize;

	//클릭변수?
	bool m_isClick;
	//메인 창 최소화 변수
	bool m_isMainMin;

public:
	virtual HRESULT Setup(void) override;
	void SetupBaseButton(void);
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
	//버튼 이미지 변경함수
	void changeMainButtonColor(void);

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};