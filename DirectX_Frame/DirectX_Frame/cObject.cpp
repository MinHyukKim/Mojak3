#include "stdafx.h"
#include "cObject.h"
#include "cAutoReleasePool.h"

cObject::cObject(void)
	: m_nReferenceCount(1)
	, m_pParent(NULL)
{
	g_pAutoRelasePool->MemoryInsert(this);
	g_pAutoRelasePool->ReleaseDelay(this);

}

cObject::~cObject(void)
{
	//0���� ������ �ߺ����ŵ�
	assert(m_nReferenceCount <= 0 && "Delete�� ������� ������.");
	g_pAutoRelasePool->MemoryErase(this);
}

//������
void cObject::Release(void)
{
	//���۷��� ī���� 1���� 0 ���ϸ� ����
	--m_nReferenceCount;
	if (m_nReferenceCount <= 0) delete this;
}

cObject* cObject::AutoRelease(void)
{
	//����Ŀ� ���ŵ� ����
	g_pAutoRelasePool->ReleaseDelay(this);
	return this;
}

//�����ڿ� ��������
cObject* cObject::Create(void)
{
	cObject* newClass = new cObject;
	newClass->AddRef();
	return newClass;
}

void cObject::Setup(void)
{
	this->SetupChild();
}

void cObject::Update(void)
{
	this->UpdateChild();
}

void cObject::Render(void)
{
	this->RenderChild();
}

void cObject::SetupChild(void)
{
	for each(auto p in m_vecChild) SAFE_SETUP(p);
}

void cObject::UpdateChild(void)
{
	for each (auto p in m_vecChild) SAFE_UPDATE(p);
}

void cObject::RenderChild(void)
{
	for each (auto p in m_vecChild) SAFE_RENDER(p);
}

void cObject::RelaseChild(void)
{
	for each(auto p in m_vecChild) SAFE_RELEASE(p);
	m_vecChild.clear();
}
