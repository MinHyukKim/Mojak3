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
	DWORD m_dwNumVertex;
	DWORD m_dwNumFace;
	DWORD m_dwCol;
	DWORD m_dwRow;
	float m_fMinHeight;
	float m_fMaxHeight;

public:

//	virtual HRESULT Setup(void) override;
	virtual HRESULT Setup(IN LPCSTR szHeightMap);
	virtual HRESULT Setup(IN DWORD dwCol, IN DWORD dwRow);
	virtual void Update(void) override;
	virtual void Render(void) override;

//	virtual void Destroy(void);

	//���ؽ� �ʱ�ȭ
	HRESULT InitVB(void);
	HRESULT InitVB(IN DWORD dwCol, IN DWORD dwRow);
	//�ε��� �ʱ�ȭ
	HRESULT InitIB(void);

// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);				//�Ҹ��� ����
};