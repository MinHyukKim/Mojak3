#pragma once
#include "cSceneObject.h"

class cPlayer;

//임시
class cCamera;

class cChareterCustomScene : public cSceneObject
{
private:
	int m_n;
	
	cPlayer* m_pPlayer;
	//임시
	cCamera* m_pMainCamera;

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