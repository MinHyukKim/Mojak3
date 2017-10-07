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
	//�׽�Ʈ��
	//cMapObject* m_pMapObject;

	cCamera* m_pCamera;
	cImage* m_pTitleImage;
	D3DXIMAGE_INFO m_stImageInfo;

	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL	 m_stMtl;
	cBuilding*		 m_pBuild;
	cSkybox*	m_pSkybox;

	//UI����
	//UI��Ʈ
	cUiObject* m_pUIRoot;

	cUIImageView* rootBase;				//�޴� ���
	cUIButton* m_pMaptoolButton;		//������ �̵� ��ư
	cUIButton* m_pStartButton;			//ĳ���� Ŀ���͸���¡ �� �̵� ��ư
	cUIButton* m_pContinueButton;		//��Ƽ�� ��ư
	cUIButton* m_pExitButton;			//�����ư
	//cUITextView* m_pQuestUiText;		//�Һ� �ý�Ʈ
	//cUITextView* m_pQuestText;			//�½�Ʈ�� �ý�Ʈ
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

