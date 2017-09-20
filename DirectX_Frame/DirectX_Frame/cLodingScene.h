#pragma once
#include "cSceneObject.h"

class cDataLoder;
class cImage;
class cLodingScene : public cSceneObject
{
private:
	D3DXMATRIXA16 m_matWorldMatrix;

	CRITICAL_SECTION m_cs;

	cDataLoder* m_pData;
	LPD3DXSPRITE m_pSprite;
	cImage* m_pLodingImage;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	static cLodingScene* Create(void);
protected:
	cLodingScene(void);
	virtual ~cLodingScene(void);
};

