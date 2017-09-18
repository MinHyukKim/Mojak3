#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"
#include "cCamera.h"

cPlayer::cPlayer(void)
	: m_pCamera(nullptr)
	, m_pAnimationController(nullptr)
	, m_bCurrentTrack(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cPlayer::~cPlayer(void)
{
	this->Reset();
}

HRESULT cPlayer::Setup(void)
{
	if (!m_pCamera) m_pCamera = cCamera::Create();
	m_pCamera->SetupParentMatrix(&m_matWorld);

	m_vecAnimationKey.resize(ANIMATION_END);
	m_vecMesh.resize(MESH_SIZE);
	
	if (!m_pAnimationController)
	{
		this->ChangeMeshPart(MESH_DUMMY, "./Chareter/DefaultPlayer/", "Female_Bone26_Dummy.X");
		//0�� Ʈ�� ����
		m_pAnimationController->SetTrackEnable(0, true);
		m_pAnimationController->SetTrackPosition(0, 0.0);
		m_pAnimationController->SetTrackSpeed(0, 1.0f);
		m_pAnimationController->SetTrackWeight(0, 1.0f);
		//1�� Ʈ�� ����
		m_pAnimationController->SetTrackEnable(1, false);
		m_pAnimationController->SetTrackPosition(1, 0.0);
		m_pAnimationController->SetTrackSpeed(1, 0.0f);
		m_pAnimationController->SetTrackWeight(1, 0.0f);
	}

	return S_OK;
}

void cPlayer::Reset(void)
{
	for each(auto p in m_vecMesh) SAFE_DELETE(p);

	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pAnimationController);
}

void cPlayer::Update(void)
{
	if (m_pAnimationController) m_pAnimationController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);

}

void cPlayer::Render(void)
{
	for each(auto p in m_vecMesh)
	{
		if (p)
		{
			p->UpdateAndRender(&m_matWorld);
		}
	}


}

void cPlayer::ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename)
{
	//Ű�� ������ �ø���
	if (m_vecMesh.size() <= dwPart) m_vecMesh.resize(dwPart * 2);
	//���� �޽� ����
	SAFE_DELETE(m_vecMesh[dwPart]);
	//�� �޽� ���
	m_vecMesh[dwPart] = new cSkinnedMesh((LPSTR)szFolder, (LPSTR)szFilename);

	//�ִϸ��̼� ��Ʈ�ѷ� ����
	if (m_pAnimationController)
	{
		g_pAllocateHierarchy->RegisterAnimationMatrix(m_vecMesh[dwPart]->GetRootFrame(), m_vecMesh[cPlayer::MESH_DUMMY]->GetRootFrame());

	}
	else
	{
		LPD3DXANIMATIONCONTROLLER pAnimationController = m_vecMesh[dwPart]->GetAnimationController();
		pAnimationController->CloneAnimationController(pAnimationController->GetMaxNumAnimationOutputs(), ANIMATION_END, 2, ANI_MATRIX, &m_pAnimationController);
	}

	m_vecMesh[dwPart]->SetAnimationController(m_pAnimationController);
	m_vecMesh[dwPart]->SetTrack(false);
}

DWORD cPlayer::RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation)
{
	//���� ó��
	if (!m_pAnimationController)
	{
		assert(false && "�ִϸ��̼� ��Ʈ�ѷ��� �������� �ʽ��ϴ�.");
		return 0;
	}

	//Ű�� ������ �ø���
	if (m_vecAnimationKey.size() <= dwAnimationKey) m_vecAnimationKey.resize(dwAnimationKey * 2);


	//�ִϸ��̼� ��Ʈ�ѷ� �缳��
	if (1 > m_pAnimationController->GetMaxNumAnimationSets() - m_pAnimationController->GetNumAnimationSets())
	{
		int count = m_pAnimationController->GetMaxNumAnimationSets();
		LPD3DXANIMATIONCONTROLLER pController;
		m_pAnimationController->CloneAnimationController(100,
			count < 1 ? count * 2 : 2, 2, ANI_MATRIX, &pController);
		SAFE_RELEASE(m_pAnimationController);
		m_pAnimationController = pController;
	}
	//�ִϸ��̼� ���
	m_pAnimationController->RegisterAnimationSet(pAnimation);
	//�ִϸ��̼ǹ�ȣ�� Ű�� ���
	m_vecAnimationKey[dwAnimationKey] = m_pAnimationController->GetNumAnimationSets() - 1;
	//�ִϸ��̼� ��ȣ ��ȯ
	return m_vecAnimationKey[dwAnimationKey];
}

void cPlayer::SetAnimation(IN DWORD dwAnimationKey)
{
	LPD3DXANIMATIONSET pAnimationSet;
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey], &pAnimationSet);
	m_pAnimationController->SetTrackAnimationSet(m_bCurrentTrack, pAnimationSet);
	m_pAnimationController->UnkeyAllTrackEvents(0);
	m_pAnimationController->UnkeyAllTrackEvents(1);
	m_pAnimationController->SetTrackEnable(m_bCurrentTrack, true);
	m_pAnimationController->SetTrackSpeed(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackWeight(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackPosition(0, 0.0);
	SAFE_RELEASE(pAnimationSet);
}


//�������� Release �ϼ���.
bool cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pAnimationController || !ppAnimation) return false;
	SAFE_RELEASE(*ppAnimation);
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey], ppAnimation);
	return true;
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}

