#pragma once
#include "cObject.h"

//�޸� ������
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

// �̱����� �Ʒ��� ���� ������ �������ֽ��ϴ�.
	static cAutoReleasePool* GetInstance() { static cAutoReleasePool instance; return &instance; }
private:
	cAutoReleasePool(void);
	virtual ~cAutoReleasePool(void);
};

