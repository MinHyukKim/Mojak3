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
	virtual void MemoryInsert(cObject* pMemory);
	virtual void MemoryErase(cObject* pMemory);
	virtual void ReleaseDelay(cObject* pObject);
	virtual void AutoReleaseCheck(void);

// �̱����� �Ʒ��� ���� ������ �������ֽ��ϴ�.
	static cAutoReleasePool* GetInstance() { static cAutoReleasePool instance; return &instance; }

private:
	cAutoReleasePool(void);
	virtual ~cAutoReleasePool(void);
};

