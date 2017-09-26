#pragma once
#include "stdafx.h"
#include "cSkybox.h"

HRESULT cSkybox::Setup(void)
{
	return E_NOTIMPL;
}

void cSkybox::Update(void)
{
}

cSkybox * cSkybox::Create(void)
{
	cSkybox* newClass = new cSkybox;
	newClass->AddRef();
	return newClass;
}

cSkybox::cSkybox(void)
{
}

cSkybox::~cSkybox(void)
{
}
