#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapObject;
//�׽�Ʈ��
class cGrid;

class cMapToolScene : public cSceneObject
{
private:
	cCamera* m_pCamera;
	//�׽�Ʈ��
	cMapObject* m_pMapObject;
	cGrid* m_pGrid;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9 m_stMtl;

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

