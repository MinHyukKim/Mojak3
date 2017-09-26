#pragma once
#include "cObject.h"

class cSkybox : public cObject
{
private:
	//스카이박스 버텍스, 텍스쳐, 인덱스
	LPDIRECT3DVERTEXBUFFER9		m_pVertex[6];
	LPDIRECT3DINDEXBUFFER9		m_pIndex[6];
	LPDIRECT3DTEXTURE9			m_pTexture[6];
	D3DXVECTOR3					vPos;
public:
	//스카이박스 셋업 함수(임시)
	virtual HRESULT Setup(const char* top,
		const char* bottom,
		const char* left,
		const char* right,
		const char* front,
		const char* back);
	virtual void Update(D3DXVECTOR3 cameraPt);
	virtual void Render(void);
	//스카이박스 생성 함수
	static cSkybox* Create(void);

	void Set_Vtx3D_Tex(ST_PNT_VERTEX &ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv)
	{
		ct.p = p; ct.n = n;	ct.t = D3DXVECTOR2(tu, tv);
	}

	void Set_Idx(ST_INDEX &ci, WORD _0, WORD _1, WORD _2)
	{
		ci._0 = _0; ci._1 = _1;	ci._2 = _2;
	}


protected:
	cSkybox(void);
	virtual ~cSkybox(void);
};
