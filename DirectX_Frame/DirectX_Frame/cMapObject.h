#pragma once
#include "cObject.h"
#include "cTile.h"

class cMapObject : public cObject
{
private:
	D3DSURFACE_DESC m_SurfaceDesc;
	D3DLOCKED_RECT m_rc;
	LPDIRECT3DTEXTURE9 m_texHeight;
	LPDIRECT3DTEXTURE9 m_texDiffuse;
	DWORD m_dwRow;
	DWORD m_dwCol;

public:

	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

//	virtual void Destroy(void);

// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cMapObject* Create(void);		//메모리관리용 생성자 
protected:									//상속받을수 있지만 생성할 수 없습니다.
	cMapObject(void);						//생성자 은닉
	virtual ~cMapObject(void);				//소멸자 은닉
};