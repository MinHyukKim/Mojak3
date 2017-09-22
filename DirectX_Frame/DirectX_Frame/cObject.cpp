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
	//0보다 작을시 중복제거됨
	assert(m_nReferenceCount <= 0 && "Delete를 사용하지 마세요.");
	g_pAutoRelasePool->MemoryErase(this);
	
	//0903 추가
	//자식 소멸
//	this->RelaseChild();
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

void cObject::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

//생성자와 얕은복사
cObject* cObject::Create(void)
{
	cObject* newClass = new cObject;
	newClass->AddRef();
	return newClass;
}

//0903 추가
HRESULT cObject::Setup(void)
{
//	this->SetupChild();
	return D3D_OK;
}

HRESULT cObject::Setup(D3DXVECTOR3 * pvTarget)
{
	return D3D_OK;
}

void cObject::Update(void)
{
//	this->UpdateChild();
}

void cObject::Render(void)
{
//	this->RenderChild();
}

//자식들 생성 업데이트 렌더 릴리즈
//void cObject::SetupChild(void)
//{
//	for each(auto p in m_vecChild) SAFE_SETUP(p);
//}
//
//void cObject::UpdateChild(void)
//{
//	for each (auto p in m_vecChild) SAFE_UPDATE(p);
//}
//
//void cObject::RenderChild(void)
//{
//	for each (auto p in m_vecChild) SAFE_RENDER(p);
//}
//
//void cObject::RelaseChild(void)
//{
//	for each(auto p in m_vecChild) SAFE_RELEASE(p);
//	m_vecChild.clear();
//}
