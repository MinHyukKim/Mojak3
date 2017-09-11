#include "stdafx.h"
#include "cQuadTree.h"

#include "cFrustum.h"

cQuadTree::cQuadTree(IN int nX, IN int nY)
	: m_dwCenter(0)
	, m_fRadius(0.0f)
{
	ZeroMemory(m_pChild, 4 * sizeof(cQuadTree));
	ZeroMemory(m_dwCorner, 4 * sizeof(int));
	m_dwCorner[cQuadTree::CORNER_LEFT_TOP] = 0;
	m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] = nX -1;
	m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM] = nX * (nY - 1);
	m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM] = nX * nY - 1;
	m_dwCenter = (m_dwCorner[cQuadTree::CORNER_LEFT_TOP] + m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] +
		m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM] + m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]) / 4;
}

cQuadTree::cQuadTree(cQuadTree* pParent)
	: m_dwCenter(0)
	, m_fRadius(0.0f)
{
	ZeroMemory(m_pChild, 4 * sizeof(cQuadTree));
	ZeroMemory(m_dwCorner, 4 * sizeof(int));
}

cQuadTree::~cQuadTree(void)
{
	this->_Destroy();
}

bool cQuadTree::TreeBuild(std::vector<ST_PNT_VERTEX>* pVecVertex)
{
	if (_SubDivide())
	{
		D3DXVECTOR3 v = pVecVertex->operator[](m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]).p - pVecVertex->operator[](m_dwCorner[cQuadTree::CORNER_LEFT_TOP]).p;
		m_fRadius = D3DXVec3Length(&v) / 2.0f;
		m_pChild[cQuadTree::CORNER_LEFT_TOP]->TreeBuild(pVecVertex);
		m_pChild[cQuadTree::CORNER_RIGHT_TOP]->TreeBuild(pVecVertex);
		m_pChild[cQuadTree::CORNER_LEFT_BOTTOM]->TreeBuild(pVecVertex);
		m_pChild[cQuadTree::CORNER_RIGHT_BOTTOM]->TreeBuild(pVecVertex);
	}
	return true;
}

int cQuadTree::GenerateIndex(OUT LPDWORD pIndexBuffer, std::vector<ST_PNT_VERTEX>* pVecVertex, cFrustum* pFrustum)
{
	this->_FrustumCull(pVecVertex, pFrustum);
	return this->_GenTriIndex(pIndexBuffer, 0);
}

inline cQuadTree* cQuadTree::_AddChild(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB)
{
	cQuadTree* pChild = new cQuadTree(this);
	pChild->_SetCorners(nCornerLT, nCornerRT, nCornerLB, nCornerRB);
	return pChild;
}

inline bool cQuadTree::_SetCorners(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB)
{
	m_dwCorner[cQuadTree::CORNER_LEFT_TOP] = nCornerLT;
	m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] = nCornerRT;
	m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM] = nCornerLB;
	m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM] = nCornerRB;
	m_dwCenter = (m_dwCorner[cQuadTree::CORNER_LEFT_TOP] + m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] +
		m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM] + m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]) / 4;
	return true;
}

inline bool cQuadTree::_SubDivide(void)
{
	//분해불가
	if (this->_IsVisible()) return false;

	//분할점
	DWORD dwLeftCenter = ( m_dwCorner[cQuadTree::CORNER_LEFT_TOP] + m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM]) / 2;
	DWORD dwTopCenter = (m_dwCorner[cQuadTree::CORNER_LEFT_TOP] + m_dwCorner[cQuadTree::CORNER_RIGHT_TOP]) / 2;
	DWORD dwRightCenter = (m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] + m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]) / 2;
	DWORD dwBottomCenter = (m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM] + m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]) / 2;

	//자식들
	m_pChild[cQuadTree::CORNER_LEFT_TOP] = this->_AddChild(m_dwCorner[cQuadTree::CORNER_LEFT_TOP], dwTopCenter, dwLeftCenter, m_dwCenter);
	m_pChild[cQuadTree::CORNER_RIGHT_TOP] = this->_AddChild(dwTopCenter, m_dwCorner[cQuadTree::CORNER_RIGHT_TOP], m_dwCenter, dwRightCenter);
	m_pChild[cQuadTree::CORNER_LEFT_BOTTOM] = this->_AddChild(dwLeftCenter, m_dwCenter, m_dwCorner[cQuadTree::CORNER_LEFT_BOTTOM], dwBottomCenter);
	m_pChild[cQuadTree::CORNER_RIGHT_BOTTOM] = this->_AddChild(m_dwCenter, dwRightCenter, dwBottomCenter, m_dwCorner[cQuadTree::CORNER_RIGHT_BOTTOM]);

	return true;
}

inline int cQuadTree::_GenTriIndex(OUT LPDWORD pIndex, IN DWORD dwTriangles)
{
	if (this->_IsVisible())
	{
		LPDWORD pointer = pIndex += dwTriangles * 3;
		pointer[0] = m_dwCorner[0];
		pointer[1] = m_dwCorner[1];
		pointer[2] = m_dwCorner[2];
		pointer[3] = m_dwCorner[2];
		pointer[4] = m_dwCorner[1];
		pointer[5] = m_dwCorner[3];

		return (dwTriangles + 2);
	}

	DWORD dwFaces = dwTriangles;;
	if (m_pChild[cQuadTree::CORNER_LEFT_TOP]) dwFaces = m_pChild[cQuadTree::CORNER_LEFT_TOP]->_GenTriIndex(pIndex, dwFaces);
	if (m_pChild[cQuadTree::CORNER_RIGHT_TOP]) dwFaces = m_pChild[cQuadTree::CORNER_LEFT_TOP]->_GenTriIndex(pIndex, dwFaces);
	if (m_pChild[cQuadTree::CORNER_LEFT_BOTTOM]) dwFaces = m_pChild[cQuadTree::CORNER_LEFT_TOP]->_GenTriIndex(pIndex, dwFaces);
	if (m_pChild[cQuadTree::CORNER_RIGHT_BOTTOM]) dwFaces = m_pChild[cQuadTree::CORNER_LEFT_TOP]->_GenTriIndex(pIndex, dwFaces);
	return dwFaces;
}

inline void cQuadTree::_Destroy(void)
{
	SAFE_DELETE(m_pChild[0]);
	SAFE_DELETE(m_pChild[1]);
	SAFE_DELETE(m_pChild[2]);
	SAFE_DELETE(m_pChild[3]);
}

int cQuadTree::_IsInFrustum(std::vector<ST_PNT_VERTEX>* pVecVertex, cFrustum* pFrustum)
{
	//충돌검사
	bool bInSphere = pFrustum->IsCollision(&pVecVertex->operator[](m_dwCenter).p, m_fRadius);
	if (!bInSphere) return cQuadTree::LOCATION_OUT;
	//모서리 충돌검사
	bool bChild[4] = {};
	bChild[0] = pFrustum->IsCollision(&pVecVertex->operator[](m_dwCorner[0]).p);
	bChild[1] = pFrustum->IsCollision(&pVecVertex->operator[](m_dwCorner[1]).p);
	bChild[2] = pFrustum->IsCollision(&pVecVertex->operator[](m_dwCorner[2]).p);
	bChild[3] = pFrustum->IsCollision(&pVecVertex->operator[](m_dwCorner[3]).p);
	if (4 == bChild[0] + bChild[1] + bChild[2] + bChild[3]) return cQuadTree::LOCATION_IN;
	//일부 충돌
	return cQuadTree::LOCATION_HALF;
}

void cQuadTree::_FrustumCull(std::vector<ST_PNT_VERTEX>* pVecVertex, cFrustum* pFrustum)
{
	switch (_IsInFrustum(pVecVertex, pFrustum))
	{
	case LOCATION_IN: m_bCulled = false; return;

	case LOCATION_HALF: m_bCulled = false; break;

	case LOCATION_OUT: m_bCulled = true; return;

	default: return;
	}

	if (m_pChild[0]) m_pChild[0]->_FrustumCull(pVecVertex, pFrustum);
	if (m_pChild[1]) m_pChild[1]->_FrustumCull(pVecVertex, pFrustum);
	if (m_pChild[2]) m_pChild[2]->_FrustumCull(pVecVertex, pFrustum);
	if (m_pChild[3]) m_pChild[3]->_FrustumCull(pVecVertex, pFrustum);
}
