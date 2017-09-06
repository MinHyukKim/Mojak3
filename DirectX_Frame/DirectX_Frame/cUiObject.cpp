#include "stdafx.h"
#include "cUiObject.h"

HRESULT cUiObject::Setup(void)
{

	return D3D_OK;
}

void cUiObject::Update(void)
{
}

void cUiObject::Render(void)
{
}

cUiObject * cUiObject::Create(void)
{
	cUiObject* newClass = new cUiObject;
	newClass->AddRef();
	return newClass;
}

cUiObject::cUiObject(void)
{
}

cUiObject::~cUiObject(void)
{
}
