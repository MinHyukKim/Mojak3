#include "stdafx.h"
#include "cSceneObject.h"

cSceneObject::cSceneObject(void)
{
}

cSceneObject::~cSceneObject(void)
{
}

HRESULT cSceneObject::Setup(void)
{

	return D3D_OK;
}

void cSceneObject::Reset(void)
{
}

void cSceneObject::Update(void)
{
}

void cSceneObject::Render(void)
{
}

//생성자와 얕은복사
cSceneObject * cSceneObject::Create(void)
{
	cSceneObject* newClass = new cSceneObject;
	newClass->AddRef();
	return newClass;
}

