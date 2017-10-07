#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapTerrain;
class cSkybox;
class cBuilding;
class cImage;
class cFont;

class cTitleScene : public cSceneObject
{
public:
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

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	static cTitleScene* Create(void);


protected:
	cTitleScene(void);
	virtual ~cTitleScene(void);
};

