#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
{
}

cMapObject::~cMapObject(void)
{
}

HRESULT cMapObject::Setup(void)
{
	return D3D_OK;
}

void cMapObject::Reset(void)
{
}

void cMapObject::Update(void)
{
}

void cMapObject::Render(void)
{
}

//생성자와 얕은 복사
cMapObject * cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}