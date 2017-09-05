#pragma once
#include "cSceneObject.h"

//테스트용
class cFont;

class cMapToolScene : public cSceneObject
{
private:
	cFont* m_pFont;

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

