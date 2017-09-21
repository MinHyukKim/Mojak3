#pragma once
#include "cSceneObject.h"

#define NEXT_SCENE "cUiCustomizingScene"

class cDataLoder;
class cImage;
class cFont;
class cLodingScene : public cSceneObject
{
private:
	D3DXMATRIXA16 m_matWorldMatrix;

	CRITICAL_SECTION m_cs;
	thread* m_pThread;

	cDataLoder* m_pData;
	LPD3DXSPRITE m_pSprite;
	cImage* m_pLodingImage;
	cFont* m_pFont;

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

