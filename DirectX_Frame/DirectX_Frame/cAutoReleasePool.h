#pragma once
#include "cObject.h"

//메모리 관리자
#define g_pAutoRelasePool cAutoReleasePool::GetInstance()

class cAutoReleasePool
{
private:
	std::set<cObject*> m_setMemoryPool;
	std::set<cObject*> m_setAutoRelase;

public:
	void MemoryInsert(cObject* pMemory);
	void MemoryErase(cObject* pMemory);
	void ReleaseDelay(cObject* pObject);
	void AutoReleaseCheck(void);
	void Destroy(void) { assert(m_setMemoryPool.empty() && "Memory Leak"); }

// 싱글톤은 아래와 같은 구조를 가지고있습니다.
	static cAutoReleasePool* GetInstance() { static cAutoReleasePool instance; return &instance; }
private:
	cAutoReleasePool(void);
	virtual ~cAutoReleasePool(void);
};

