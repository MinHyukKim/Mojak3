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
	//����
	ST_BONE* pNewFrame = new ST_BONE;
	CopyString(&pNewFrame->Name, Name);

	//��ȯ
	(*ppNewFrame) = pNewFrame;
	return D3D_OK;
}