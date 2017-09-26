#pragma once
#include "cObject.h"

class cSkybox : public cObject
{
private:
	//��ī�̹ڽ� ���ؽ�, �ؽ���, �ε���
	LPDIRECT3DVERTEXBUFFER9		m_pVertex[6];
	LPDIRECT3DINDEXBUFFER9		m_pIndex[6];
	LPDIRECT3DTEXTURE9			m_pTexture[6];
public:
	cSkybox(const char* top, 
		const char* bottom,
		const char* left,
		const char* right, 
		const char* front,
		const char* back);


	virtual HRESULT Setup(void);
	virtual void Update(void);

	//��ī�̹ڽ� ���� �Լ�
	static cSkybox* Create(void);
protected:
	cSkybox(void);
	virtual ~cSkybox(void);
};
