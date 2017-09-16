#pragma once
#include "cSceneObject.h"

class cChareterCustomScene : public cSceneObject
{
private:

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	static cChareterCustomScene* Create(void);
protected:
	cChareterCustomScene(void);
	virtual ~cChareterCustomScene(void);
};