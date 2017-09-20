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
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
//	virtual void Onclick(cUIButton* pSender) override;

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};