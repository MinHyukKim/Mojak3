#pragma once
#include "cObject.h"

class cSkybox : public cObject
{
private:
	//��ī�̹ڽ� ���ؽ�, �ؽ���, �ε���
	LPDIRECT3DVERTEXBUFFER9		m_pVertex[6];
	LPDIRECT3DINDEXBUFFER9		m_pIndex[6];
	LPDIRECT3DTEXTURE9			m_pTexture[6];
	D3DXVECTOR3					vPos;
public:
	//��ī�̹ڽ� �¾� �Լ�(�ӽ�)
	virtual HRESULT Setup(const char* top,
		const char* bottom,
		const char* left,
		const char* right,
		const char* front,
		const char* back);
	virtual void Update(D3DXVECTOR3 cameraPt);
	virtual void Render(void);
	//��ī�̹ڽ� ���� �Լ�
	static cSkybox* Create(void);

protected:
	cSkybox(void);
	virtual ~cSkybox(void);
};
