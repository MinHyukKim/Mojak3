#include "stdafx.h"
#include "cSceneObject.h"

cSceneObject::cSceneObject(void)
{
}

cSceneObject::~cSceneObject(void)
{
}

HRESULT cSceneObject::Setup()
{

	return D3D_OK;
}

void cSceneObject::Update()
{
}

void cSceneObject::Render()
{
}

//생성자와 얕은복사
cSceneObject * cSceneObject::Create(void)
{
	cSceneObject* newClass = new cSceneObject;
	newClass->AddRef();
	return newClass;
}

