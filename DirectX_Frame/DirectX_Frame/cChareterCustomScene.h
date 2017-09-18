#pragma once
#include "cSceneObject.h"

class cPlayer;

//�ӽ�
class cCamera;

class cChareterCustomScene : public cSceneObject
{
private:
	int m_n;
	
	cPlayer* m_pPlayer;
	//�ӽ�
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