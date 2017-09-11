#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh(char * szFolder, char * szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
{
	cSkinnedMesh* pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);

	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;
	m_pEffect = pSkinnedMesh->m_pEffect;
	
	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
}

cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
{
}

void cSkinnedMesh::Load(char * szFolder, char * szFilename)
{
	m_pEffect = LoadEffect("MultiAnimation.hpp");
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy ah;
	ah.setFol

}

LPD3DXEFFECT cSkinnedMesh::LoadEffect(char * szFilename)
{
	return LPD3DXEFFECT();
}

void cSkinnedMesh::Update(ST_BONE * pCurrent, D3DXMATRIXA16 * pmatParent)
{
}

void cSkinnedMesh::Render(ST_BONE * pBone)
{
}

void cSkinnedMesh::SetupBoneMatrixPtrs(ST_BONE * pBone)
{
}

void cSkinnedMesh::Destroy()
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);
}

void cSkinnedMesh::UpdateAndRender()
{
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
}

void cSkinnedMesh::SetBlendingAnimation(int nAnimationKey, float fTravalTime)
{
}

void cSkinnedMesh::SetRandomTrackPosition()
{
}
