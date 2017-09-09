#pragma once
#include "cObject.h"
#include "cTile.h"

class cMapObject : public cObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBufer;
	LPDIRECT3DTEXTURE9 m_texHeight;
	LPDIRECT3DTEXTURE9 m_texDiffuse;
	DWORD m_dwCol;
	DWORD m_dwRow;

public:

	virtual HRESULT Setup(IN LPCSTR szHeightMap);
//	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

//	virtual void Destroy(void);

	HRESULT InitVB(void);
	HRESULT InitIB(void);

// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);				//�Ҹ��� ����
};