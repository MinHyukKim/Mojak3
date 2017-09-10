#include "stdafx.h"
#include "cQuadTree.h"

cQuadTree::cQuadTree(int nX, int nY)
{
}

cQuadTree::cQuadTree(cQuadTree * pParent)
{
}

cQuadTree::~cQuadTree(void)
{
}

inline cQuadTree * cQuadTree::_AddChild(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB)
{
	return nullptr;
}

inline bool cQuadTree::_SetCorners(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB)
{
	return false;
}

inline bool cQuadTree::_SubDivide(void)
{
	return false;
}

inline int cQuadTree::_GetTriIndex(int nTriangles, LPVOID pIndex)
{
	return 0;
}

inline void cQuadTree::_Destroy(void)
{
}

bool cQuadTree::TreeBuild(void)
{
	return false;
}
