#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
	: m_texHeight(NULL)
	, m_texDiffuse(NULL)
	, m_dwRow(0)
	, m_dwCol(0)
{
}

cMapObject::~cMapObject(void)
{
}

HRESULT cMapObject::Setup(void)
{
	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, BMP_HEIGHT)))
	{

	}
	return D3D_OK;
}

void cMapObject::Update(void)
{
}

void cMapObject::Render(void)
{
}

cMapObject* cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}