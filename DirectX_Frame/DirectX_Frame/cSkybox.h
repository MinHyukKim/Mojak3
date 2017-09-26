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
