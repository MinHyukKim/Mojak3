#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"
#include "cImage.h"

class cCamera;
class cMapTerrain;
class cSkybox;
class cBuilding;
class cImage;
class cFont;
class cUIButton;

class cUiObject;
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cTitleScene : public cSceneObject, iButtonDelegate
{
public:
	enum
	{
		E_MAPTOOL_BUTTON = 213,
		E_START_BUTTON = 214,
		E_CONTINUE_BUTTON,
		E_EXIT_BUTTON,
	};
private:
	D3DXMATRIXA16 m_matWorldMatrix;
	LPD3DXSPRITE m_pSprite;


	cMapTerrain* m_pMapTerrain;
	//테스트용
	//cMapObject* m_pMapObject;

	cCamera* m_pCamera;
	cImage* m_pTitleImage;
	D3DXIMAGE_INFO m_stImageInfo;

	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL	 m_stMtl;
	cBuilding*		 m_pBuild;
	cSkybox*	m_pSkybox;

	//UI관련
	//UI루트
	cUiObject* m_pUIRoot;

	cUIImageView* rootBase;				//메뉴 배경
	cUIButton* m_pMaptoolButton;		//맵툴씬 이동 버튼
	cUIButton* m_pStartButton;			//캐릭터 커스터마이징 씬 이동 버튼
	cUIButton* m_pContinueButton;		//컨티뉴 버튼
	cUIButton* m_pExitButton;			//종료버튼
	//cUITextView* m_pQuestUiText;		//불변 택스트
	//cUITextView* m_pQuestText;			//태스트용 택스트
	//cUiObject* m_pQuestUi;



public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	// iButtonDelegate override
	virtual void OnClick(cUIButton* pSender) override;

	static cTitleScene* Create(void);

protected:
	cTitleScene(void);
	virtual ~cTitleScene(void);
};

