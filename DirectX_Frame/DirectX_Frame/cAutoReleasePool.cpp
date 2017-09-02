#include "stdafx.h"
#include "cAutoReleasePool.h"
#include "cObject.h"

cAutoReleasePool::cAutoReleasePool(void)
{
}

cAutoReleasePool::~cAutoReleasePool(void)
{
	//시스템 종료시 메모리풀에 데이터가 남아있으면 프로그램 경고!
	assert(m_setMemoryPool.empty() && "Release를 사용합시다.");
}


void cAutoReleasePool::MemoryInsert(cObject * pMemory)
{
	//메모리풀에 데이터 추가
	m_setMemoryPool.insert(pMemory);
}

void cAutoReleasePool::MemoryErase(cObject * pMemory)
{
	//메모리풀에 데이터 제거
	m_setMemoryPool.erase(pMemory);
}

void cAutoReleasePool::ReleaseDelay(cObject * pObject)
{
	//바로 릴리즈 하지않고 잠시 후에 릴리즈하겠습니다.
	m_setAutoRelase.insert(pObject);
}

void cAutoReleasePool::AutoReleaseCheck(void)
{
	// 메모리에 등록된 클래스가 없으면 실행하지 않음
	if (m_setAutoRelase.empty()) return;

	//등록된 오브젝트의 래퍼런스카운터를 1 감소
	for each(auto pObject in m_setAutoRelase)
	{
		if (pObject) pObject->Release();
	}
	m_setAutoRelase.clear();
}

