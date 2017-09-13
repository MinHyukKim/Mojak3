#include "stdafx.h"
#include "cFrustum.h"

cFrustum::cFrustum(void)
	: m_pPosition(nullptr)
{
	D3DXMatrixIdentity(&m_matFrustum);
}

cFrustum::~cFrustum(void)
{
	SAFE_DELETE_ARRAY(m_pLocalPos);
	SAFE_DELETE_ARRAY(m_pPosition);
}

void cFrustum::Setup(void)
{
	if (!m_pLocalPos)
	{
		m_pLocalPos = new D3DXVECTOR3[FRUSTUM_INDEXS];
		m_pPosition = new D3DXVECTOR3[FRUSTUM_INDEXS];
		D3DXVECTOR3 cube[FRUSTUM_VERTEXS] =
		{
			{ -1, 1, 0 },{ 1, 1, 0 },{ 1, -1, 0 },{ -1, -1,0 },
			{ -1,1,1 },{ 1,1,1 },{ 1,-1,1 },{ -1,-1,1 },
		};
		int indices[] = { 0,1,2,0,4,5,1,5,6,3,2,6,3,7,4,4,7,6 };
		for (size_t i = 0; i < FRUSTUM_INDEXS; ++i) m_pLocalPos[i] = cube[indices[i]];
	}
}

void cFrustum::Update(void)
{
	//컬링 매트릭스 설정
	D3DXMATRIXA16 matProj, matProjInverse, matView, matViewInverse;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProjInverse, nullptr, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, nullptr, &matView);
	m_matFrustum = matProjInverse * matViewInverse;

	//컬링 좌표 설정
	if (m_pLocalPos && m_pPosition)
	{
		for (size_t i = 0; i < FRUSTUM_INDEXS; i++)
		{
			D3DXVec3TransformCoord(&m_pPosition[i], &m_pLocalPos[i], &m_matFrustum);
		}

	}
}

bool cFrustum::IsCollision(IN LPD3DXVECTOR3 pPosition, IN float fRadius)
{
	for (size_t i = 0; i < 18; i += 3)
	{
		//폴리곤 생성
		D3DXPLANE stPlane;
		D3DXPlaneFromPoints(&stPlane, &m_pPosition[i], &m_pPosition[i + 1], &m_pPosition[i + 2]);
		//구체비교
		float fDistance = D3DXPlaneDotCoord(&stPlane, pPosition);
		if (fDistance >= fRadius) return false;
	}
	return true;
}

void cFrustum::Destroy(void)
{
	SAFE_DELETE_ARRAY(m_pLocalPos);
	SAFE_DELETE_ARRAY(m_pPosition);
}
