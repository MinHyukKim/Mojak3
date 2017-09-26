#pragma once
#include "cObject.h"

class cSkybox : public cObject
{
private:
	//스카이박스 버텍스, 텍스쳐, 인덱스
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

	//스카이박스 생성 함수
	static cSkybox* Create(void);
protected:
	cSkybox(void);
	virtual ~cSkybox(void);
};
