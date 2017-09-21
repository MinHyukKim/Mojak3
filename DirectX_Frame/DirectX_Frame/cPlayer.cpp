#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"
#include "cCamera.h"

cPlayer::cPlayer(void)
	: m_pCamera(nullptr)
	, m_pAnimationController(nullptr)
	, m_bCurrentTrack(false)
	, m_vPosition(0.0f, 0.0f, 0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_stHairMaterial, sizeof(D3DMATERIAL9));
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
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);

}

void cPlayer::Render(void)
{
	for (DWORD i = 0; i < MESH_SIZE; i++)
	{
		m_vecMesh[i]->UpdateAndRender(&m_matWorld);
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

void cPlayer::ChangeMeshPart(IN DWORD dwPart, IN cSkinnedMesh* pSkinnedMesh)
{
	//Ű�� ������ �ø���
	if (m_vecMesh.size() <= dwPart) m_vecMesh.resize(dwPart * 2);
	//���� �޽� ����
	SAFE_DELETE(m_vecMesh[dwPart]);
	//�� �޽� ���
	m_vecMesh[dwPart] = new cSkinnedMesh(pSkinnedMesh);

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

void cPlayer::ChangeMeshPartColor(IN DWORD dwPart, IN LPCSTR TextureName, IN LPD3DXCOLOR pColor)
{
	if (m_vecMesh[dwPart]) m_vecMesh[dwPart]->SetTextureColor(TextureName, pColor);
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
		m_pAnimationController->CloneAnimationController(
			m_pAnimationController->GetMaxNumAnimationOutputs(),
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

void cPlayer::SetBlendingAnimation(IN DWORD dwAnimationKey, float fTravelTime)
{
	if (m_nAnimationKey == dwAnimationKey) return;
	float fCurrentTime = m_pAnimationController->GetTime();
	if (!fCurrentTime) return;
	LPD3DXKEYFRAMEDANIMATIONSET pKeyAniset;
	//�ʱ�ȭ
	LPD3DXANIMATIONSET pAnimationSet = NULL;

	m_pAnimationController->UnkeyAllTrackEvents(false);
	m_pAnimationController->UnkeyAllTrackEvents(true);

	//���� �ִϸ��̼�
	m_pAnimationController->GetAnimationSet(m_nAnimationKey, &pAnimationSet);
	float fPlayTime = pAnimationSet->GetPeriod();
	m_pAnimationController->SetTrackAnimationSet(!m_bCurrentTrack, pAnimationSet);
	m_pAnimationController->KeyTrackWeight(!m_bCurrentTrack, 1.0f,
		fCurrentTime, fPlayTime * fTravelTime, D3DXTRANSITION_LINEAR);
	m_pAnimationController->SetTrackEnable(!m_bCurrentTrack, true);
	SAFE_RELEASE(pAnimationSet);

	//���� �ִϸ��̼�
	m_pAnimationController->GetAnimationSet(m_nAnimationKey, &pAnimationSet);
	m_pAnimationController->SetTrackAnimationSet(m_bCurrentTrack, pAnimationSet);
	m_pAnimationController->KeyTrackWeight(m_bCurrentTrack, 0.0f,
		fCurrentTime, fPlayTime * fTravelTime, D3DXTRANSITION_LINEAR);
	m_pAnimationController->KeyTrackEnable(m_bCurrentTrack, false,
		fCurrentTime + fPlayTime * fTravelTime);
	SAFE_RELEASE(pAnimationSet);

	//�ִϸ��̼� ����
	m_bCurrentTrack = !m_bCurrentTrack;

	m_nAnimationKey = dwAnimationKey;
}

void cPlayer::SetBlendingAnimation(IN DWORD dwAnimationKey, int nRepeat, float fTravelTime)
{



}


//�������� Release �ϼ���.
bool cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pAnimationController || !ppAnimation) return false;
	SAFE_RELEASE(*ppAnimation);
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey], ppAnimation);
	return true;
}

void cPlayer::SetTextureEye(LPCSTR szEyeName)
{
	//���� ������
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentEyeTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureChange(m_sCurrentEyeTextureName.c_str(), szEyeName);
	}
	//�ؽ��� �̸� ������Ʈ
	m_sCurrentEyeTextureName = szEyeName;
}

void cPlayer::SetTextureEyeColor(D3DMATERIAL9* pMaterial)
{
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentEyeTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureColor(m_sCurrentEyeTextureName.c_str(), pMaterial);
	}
}

void cPlayer::SetTextureEyeColor(LPD3DXCOLOR pColor)
{
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentEyeTextureName.length())
	{
		D3DMATERIAL9 stMaterial;
		ZeroMemory(&stMaterial, sizeof(D3DMATERIAL9));
		stMaterial.Ambient = stMaterial.Diffuse = stMaterial.Specular = *pColor;
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureColor(m_sCurrentEyeTextureName.c_str(), &stMaterial);
	}
}

void cPlayer::SetTextureMouth(LPCSTR szEyeName)
{
	//���� ������
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentMouthTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureChange(m_sCurrentMouthTextureName.c_str(), szEyeName);
	}
	//�ؽ��� �̸� ������Ʈ
	m_sCurrentMouthTextureName = szEyeName;
}

void cPlayer::SetTextureMouthColor(D3DMATERIAL9 * pMaterial)
{
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentMouthTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureColor(m_sCurrentMouthTextureName.c_str(), pMaterial);
	}
}

void cPlayer::SetTextureMouthColor(LPD3DXCOLOR pColor)
{
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentMouthTextureName.length())
	{
		D3DMATERIAL9 stMaterial;
		ZeroMemory(&stMaterial, sizeof(D3DMATERIAL9));
		stMaterial.Ambient = stMaterial.Diffuse = stMaterial.Specular = *pColor;
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureColor(m_sCurrentMouthTextureName.c_str(), &stMaterial);
	}
}

void cPlayer::SetTextureHair(LPCSTR szHairName)
{
	if (m_vecMesh[cPlayer::MESH_HAIR] && m_sCurrentHairTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_HAIR]->SetTextureColor(szHairName, &m_stHairMaterial);
	}
	m_sCurrentHairTextureName = szHairName;
}

void cPlayer::SetTextureHairColor(D3DMATERIAL9* pMaterial)
{
	if (m_vecMesh[cPlayer::MESH_HAIR] && m_sCurrentHairTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_HAIR]->SetTextureColor(m_sCurrentHairTextureName.c_str(), pMaterial);
	}
	m_stHairMaterial = *pMaterial;
}

void cPlayer::SetTextureHairColor(LPD3DXCOLOR pColor)
{
	ZeroMemory(&m_stHairMaterial, sizeof(D3DMATERIAL9));
	m_stHairMaterial.Ambient = m_stHairMaterial.Diffuse = m_stHairMaterial.Specular = *pColor;
	if (m_vecMesh[cPlayer::MESH_HAIR] && m_sCurrentHairTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_HAIR]->SetTextureColor(m_sCurrentHairTextureName.c_str(), &m_stHairMaterial);
	}
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}
