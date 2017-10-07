#pragma once
#include "cSceneObject.h"

class cCamera;

class cTitleScene : public cSceneObject
{
public:
private:
	cMapTerrain* m_pMapTerrain;
	//테스트용
	//cMapObject* m_pMapObject;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL m_stMtl;


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

