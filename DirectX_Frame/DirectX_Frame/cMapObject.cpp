#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
{
}

cMapObject::~cMapObject(void)
{
}

//�����ڿ� ���� ����
cMapObject * cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}