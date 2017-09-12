#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapTerrain;

//테스트용
class cGrid;
class cMapObject;

class cMapToolScene : public cSceneObject
{
private:
	cCamera* m_pCamera;
	cMapTerrain* m_pMapTerrain;
	//테스트용
	cMapObject* m_pMapObject;
	cGrid* m_pGrid;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL m_stMtl;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	static cMapToolScene* Create(void);
protected:
	cMapToolScene(void);
	virtual ~cMapToolScene(void);
};

