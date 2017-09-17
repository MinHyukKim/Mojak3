#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"
#include "cCamera.h"

cPlayer::cPlayer(void)
	: m_pMesh(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cPlayer::~cPlayer(void)
{
	this->Reset();
}

HRESULT cPlayer::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->SetupParentMatrix(&m_matWorld);

	m_vecAnimationKey.resize(ANIMATION_END);
	return S_OK;
}

void cPlayer::Reset(void)
{
	SAFE_DELETE(m_pMesh);

	SAFE_RELEASE(m_pCamera);
}

void cPlayer::Update(void)
{

}

void cPlayer::Render(void)
{
	if (m_pMesh) m_pMesh->UpdateAndRender();


}

void cPlayer::CreateMesh(IN LPCSTR szFolder, IN LPCSTR szFilename)
{
	SAFE_DELETE(m_pMesh);
	m_pMesh = new cSkinnedMesh((LPSTR)szFolder, (LPSTR)szFilename);
}

DWORD cPlayer::RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation)
{
	//키가 적으면
	if (m_vecAnimationKey.size() <= dwAnimationKey) m_vecAnimationKey.resize(dwAnimationKey * 2);
	//애니메이션번호를 키에 등록
	m_vecAnimationKey[dwAnimationKey] = m_pMesh->AddAnimationSet(pAnimation);
	//애니메이션 번호반환
	return m_vecAnimationKey[dwAnimationKey];
}

bool cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pMesh->GetAnimationController() || !ppAnimation) return false;
	SAFE_RELEASE(*ppAnimation);
	m_pMesh->GetAnimationController()->GetAnimationSet(m_vecAnimationKey[dwAnimationKey], ppAnimation);
	return true;
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}

