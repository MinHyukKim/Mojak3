#pragma once
#include "cSceneObject.h"

class cCamera;
class cGrid;



class cCharTestScene : public cSceneObject
{
private:

	cCamera* m_pCamera;
	//테스트용
	cGrid* m_pGrid;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9 m_stMtl;
	vector<cSkinnedMesh*>	m_vecSkinnedMesh;


public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;



	static cCharTestScene* Create(void);
protected:
	cCharTestScene(void);
	virtual ~cCharTestScene(void);
};

