#pragma once
#include "cSceneObject.h"

class cCharTestScene : public cSceneObject
{
private:
public:
	//	virtual HRESULT Setup(void) override;
	//	virtual void Reset(void) override;
	//	virtual void Update(void) override;
	//	virtual void Render(void) override;

	static cCharTestScene* Create(void);
protected:
	cCharTestScene(void);
	virtual ~cCharTestScene(void);
};

