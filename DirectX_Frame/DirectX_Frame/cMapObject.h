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

// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);				//�Ҹ��� ����
};