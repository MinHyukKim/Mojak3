#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
{
}

cMapObject::~cMapObject(void)
{
}

//생성자와 얕은 복사
cMapObject * cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}