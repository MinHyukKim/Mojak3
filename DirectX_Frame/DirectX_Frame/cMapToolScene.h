#pragma once
#include "cSceneObject.h"

class cCamera;
class cMapTerrain;
class cSkybox;

//�׽�Ʈ��
class cGrid;
class cBuilding;
//class cMapObject;

class cMapToolScene : public cSceneObject
{
private:
	cCamera* m_pCamera;
	cMapTerrain* m_pMapTerrain;
	//�׽�Ʈ��
	//cMapObject* m_pMapObject;
	cGrid* m_pGrid;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATERIAL m_stMtl;

	cBuilding* m_pBuild;
	cSkybox*	m_pSkybox;


public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	//���� ������Ʈ�� ���Ϸ� ���̺�
	void SaveCurrentObjectsState(const char* filename);
	void LoadCurrentObjectsState(const char* filename);



	static cMapToolScene* Create(void);
protected:
	cMapToolScene(void);
	virtual ~cMapToolScene(void);
};

