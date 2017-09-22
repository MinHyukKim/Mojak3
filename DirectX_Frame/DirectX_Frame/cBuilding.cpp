#include "stdafx.h"
#include "cBuilding.h"

HRESULT cBuilding::Setup(void)
{
	return E_NOTIMPL;
}

LPD3DXMESH cBuilding::LoadModel(const char * filename)
{
	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL, NULL, NULL, NULL, &ret)));
	{
		OutputDebugString("모델 로딩 실패");
	}

	return ret;
}

void cBuilding::Reset(void)
{
}

void cBuilding::Update(void)
{
}

void cBuilding::Render(void)
{
}

cBuilding::cBuilding(void)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cBuilding::~cBuilding(void)
{
	this->Reset();
}

cBuilding* cBuilding::Create(void)
{
	cBuilding* newClass = new cBuilding;
	newClass->AddRef();
	return newClass;
}
