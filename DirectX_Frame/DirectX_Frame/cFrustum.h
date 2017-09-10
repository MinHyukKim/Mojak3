#pragma once

#define FRUSTUM_VERTEXS 8
#define FRUSTUM_INDEXS 18

class cFrustum
{
private:
	D3DXMATRIXA16 m_matFrustum;
	LPD3DXVECTOR3 m_pLocalPos;
	LPD3DXVECTOR3 m_pPosition;
public:
	void Setup(void);
	void Update(void);

	//점 또는 구체 충돌
	bool IsCollision(IN LPD3DXVECTOR3 pPosition, IN float fRadius = 0.0f);


	cFrustum(void);
	virtual ~cFrustum(void);
};

