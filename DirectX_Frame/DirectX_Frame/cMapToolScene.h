#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapTerrain;
class cSkybox;

//테스트용
class cGrid;
class cBuilding;
//class cMapObject;

class cMapToolScene : public cSceneObject
{
public:
	enum E_MODE
	{
		M_NONE,
		M_BUILD,
		M_MOB,
		END,
	};
private:
	cCamera* m_pCamera;
	cMapTerrain* m_pMapTerrain;
	//테스트용
	//cMapObject* m_pMapObject;
	cGrid* m_pGrid;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL m_stMtl;

	cBuilding* m_pBuild;
	cSkybox*	m_pSkybox;

	vector<char*> m_vecObjectList;

	int currentMode;

	cFont* m_pPickPosition;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	
	static cMapToolScene* Create(void);

	//현재 오브젝트 선택 상태에 따라 상태를 해제해주는 함수
	void DeselectObjects();
protected:
	cMapToolScene(void);
	virtual ~cMapToolScene(void);
};

