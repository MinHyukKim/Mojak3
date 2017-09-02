#include "stdafx.h"
#include "cAutoReleasePool.h"
#include "cObject.h"

cAutoReleasePool::cAutoReleasePool(void)
{
}

cAutoReleasePool::~cAutoReleasePool(void)
{
	//�ý��� ����� �޸�Ǯ�� �����Ͱ� ���������� ���α׷� ���!
	assert(m_setMemoryPool.empty() && "Release�� ����սô�.");
}


void cAutoReleasePool::MemoryInsert(cObject * pMemory)
{
	//�޸�Ǯ�� ������ �߰�
	m_setMemoryPool.insert(pMemory);
}

void cAutoReleasePool::MemoryErase(cObject * pMemory)
{
	//�޸�Ǯ�� ������ ����
	m_setMemoryPool.erase(pMemory);
}

void cAutoReleasePool::ReleaseDelay(cObject * pObject)
{
	//�ٷ� ������ �����ʰ� ��� �Ŀ� �������ϰڽ��ϴ�.
	m_setAutoRelase.insert(pObject);
}

void cAutoReleasePool::AutoReleaseCheck(void)
{
	// �޸𸮿� ��ϵ� Ŭ������ ������ �������� ����
	if (m_setAutoRelase.empty()) return;

	//��ϵ� ������Ʈ�� ���۷���ī���͸� 1 ����
	for each(auto pObject in m_setAutoRelase)
	{
		if (pObject) pObject->Release();
	}
	m_setAutoRelase.clear();
}

