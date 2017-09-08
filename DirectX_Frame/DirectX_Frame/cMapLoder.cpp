#include "stdafx.h"
#include "cMapLoder.h"

#include "cMapObject.h"

cMapLoder::cMapLoder(void)
{
}

cMapLoder::~cMapLoder(void)
{
}

void cMapLoder::Create(cMapObject** ppMap, int nMapSize)
{
	cMapObject* pMapObject = cMapObject::Create();
	(*ppMap) = pMapObject;
	pMapObject->Setup();


}

