#pragma once
#include "cSceneObject.h"

class cCamera;
class cGrid;
class cMapTerrain;
class cCrtCtrl;
class cBuilding;
class cUiTestScene;

class cCharTestScene : public cSceneObject
{
private:
	cCamera* m_pCamera;
	cMapTerrain* m_pMapTerrain;

	cGrid* m_pGrid;
	
	//ui연동 태스트
	cUiTestScene* m_pUi;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;


	static cCharTestScene* Create(void);
protected:
	cCharTestScene(void);
	virtual ~cCharTestScene(void);
};

