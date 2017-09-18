#pragma once
#include "cSceneObject.h"

class cLodingScene : public cSceneObject
{
private:
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

