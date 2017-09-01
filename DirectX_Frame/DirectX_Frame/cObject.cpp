#include "stdafx.h"
#include "cObject.h"
#include "cAutoReleasePool.h"

cObject::cObject(void)
	: m_nReferenceCount(1)
{
	g_pAutoRelasePool->ReleaseDelay(this);
}

cObject::~cObject(void)
{
	//0보다 작을시 중복제거됨
	assert(m_nReferenceCount <= 0 && "Reference Leak");
	g_pAutoRelasePool->MemoryErase(this);
}

//릴리즈
void cObject::Release(void)
{
	//래퍼런스 카운터 1감소 0 이하면 제거
	--m_nReferenceCount;
	if (m_nReferenceCount <= 0) delete this;
}

cObject* cObject::AutoRelease(void)
{
	//잠시후에 제거될 예정
	g_pAutoRelasePool->ReleaseDelay(this);
	return this;
}

//생성자와 얕은복사
cObject* cObject::Create(void)
{
	cObject* newClass = new cObject;
	newClass->AddRef();
	return newClass;
}

cObject* cObject::AddRef(void)
{
	++m_nReferenceCount;
	return this;
}
