#pragma once
#include "cSceneObject.h"

class cTestScene : public cSceneObject
{
private:
public:
//	virtual HRESULT Setup(void) override;
//	virtual void Reset(void) override;
//	virtual void Update(void) override;
//	virtual void Render(void) override;

	static cTestScene* Create(void);
protected:
	cTestScene(void);
	virtual ~cTestScene(void);
};

