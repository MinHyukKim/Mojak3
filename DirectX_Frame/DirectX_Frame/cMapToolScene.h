#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapObject;
//�׽�Ʈ��
class cGrid;

class cMapToolScene : public cSceneObject
{
private:
	cCamera* m_pCamera;
	cMapObject* m_pMapObject;
	//�׽�Ʈ��
	cGrid* m_pGrid;

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

