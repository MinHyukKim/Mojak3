#pragma once
#include "cSceneObject.h"

class cPlayer;
class cChareterCustomScene : public cSceneObject
{
private:
	cPlayer* m_pPlayer;

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