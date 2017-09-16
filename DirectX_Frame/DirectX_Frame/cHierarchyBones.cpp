#include "stdafx.h"
#include "cHierarchyBones.h"


cHierarchyBones::cHierarchyBones(void)
{
}


cHierarchyBones::~cHierarchyBones(void)
{
}

HRESULT cHierarchyBones::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
	//생성
	ST_BONE* pNewFrame = new ST_BONE;
	CopyString(&pNewFrame->Name, Name);

	//반환
	(*ppNewFrame) = pNewFrame;
	return D3D_OK;
}