#include "stdafx.h"
#include "cBuilding.h"

HRESULT cBuilding::Setup(void)
{
	return E_NOTIMPL;
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
