#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"
#include "cCamera.h"
#include "cActionMove.h"
#include "cActionDirection.h"

cPlayer::cPlayer(void)
	: m_pCamera(nullptr)
	, m_pTarget(nullptr)
	, m_pActionMove(nullptr)
	, m_pAnimationController(nullptr)
	, m_dwNumMainAnimation(cPlayer::ANIMATION_NULL)
	, m_dwNumSubAnimation(cPlayer::ANIMATION_NULL)
	, m_dwNumRealdyTrue(0)
	, m_dwNumRealdyFalse(0)
	, m_dwNumPattern(PATTERN_NORMAL)
	, m_dwNumState(cPlayer::ORDER_NULL)
	, m_bCurrentTrack(false)
	, m_fRadius(0.3f)
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
	m_pActionMove = cActionMove::Create();
	m_pActionMove->SetTarget(this);
	m_pActionDirection = cActionDirection::Create();
	m_pActionDirection->SetTarget(this);

	if (!m_pCamera) m_pCamera = cCamera::Create();
	m_pCamera->SetupParentMatrix(&m_matWorld);

	m_vecMesh.resize(MESH_SIZE);

	return S_OK;
}

void cPlayer::Reset(void)
{
	for each(auto p in m_vecMesh) SAFE_DELETE(p);

	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pTarget);
	SAFE_RELEASE(m_pActionMove);
	SAFE_RELEASE(m_pActionDirection);
	SAFE_RELEASE(m_pAnimationController);
}

void cPlayer::Update(void)
{
	//Ÿ�� ���� Ȯ���� ��ȿ���� ������ ����
	if (m_pTarget && !m_pTarget->GetAbilityParamter()->IsEffective()) m_pTarget->Release();
	if (!m_AbilityParamter.IsEffective()) return;

	// ���Ͽ� ���� ������Ʈ
//	switch (m_dwNumPattern)
//	{
//	case cPlayer::ORDER_NULL: break;
//	case 1: break;
//	case 2: break;
//	default: break;
//	}
	this->PatternUpdate();
}

void cPlayer::Render(void)
{
	if (m_pAnimationController) m_pAnimationController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	for (DWORD i = 0; i < MESH_SIZE; i++)
	{
		if (m_vecMesh[i]) m_vecMesh[i]->UpdateAndRender(&m_matWorld);
	}

}

void cPlayer::SetupAnimationController(LPCSTR szBoneKey)
{
	if (!m_pAnimationController)
	{
		this->ChangeMeshPart(cPlayer::MESH_DUMMY, g_pSkinnedMeshManager->GetSkinnedMesh(szBoneKey));
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
	m_vecAnimationKey.resize(ANIMATION_END);
}

void cPlayer::SetupFriendly(void)
{
	m_dwNumPattern;
	this->SetStateTrue(PATTERN_FRIENDLY);
	this->SetStateFalse(PATTERN_OFFENSIVE);
	this->SetBlendingAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY);
}

void cPlayer::SetupOffnsive(void)
{
	m_dwNumPattern;
	this->SetStateTrue(PATTERN_OFFENSIVE);
	this->SetStateFalse(PATTERN_FRIENDLY);
	this->SetBlendingAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE);
}

void cPlayer::PatternUpdate(void)
{
	//�⺻ ������Ʈ
	m_AbilityParamter.Update();
	SAFE_UPDATE(m_pActionMove);
	SAFE_UPDATE(m_pActionDirection);
	if (this->CheckState(PATTERN_STOP))
	{
		if (m_pActionMove && !m_pActionMove->IsPlay())
		{
			this->OrderIden();
		}
	}
	// Ÿ���� �������϶�
	if (this->CheckState(PATTERN_TARGET))
	{
		this->OrderTarget();
	}
	// ���� ����
	if (m_AbilityParamter.IsDelayEnd())
	{
		assert(!(m_dwNumRealdyTrue & m_dwNumRealdyFalse) && "�ൿ �˰��� �浹");
		if (m_dwNumRealdyTrue)
		{
			this->SetStateTrue(m_dwNumRealdyTrue);
			m_dwNumRealdyTrue = 0;
		}
		if (m_dwNumRealdyFalse)
		{
			this->SetStateFalse(m_dwNumRealdyFalse);
			m_dwNumRealdyFalse = 0;
		}
		if (m_dwNumRealdyState)
		{
			this->SetStatePattern(m_dwNumRealdyState);
			m_dwNumRealdyState = 0;
		}
	}
}


void cPlayer::SetStatePattern(DWORD dwNumState)
{
	//���� ��ȯ�� �ʱ�ȭ
	switch (dwNumState)
	{
	case cPlayer::ORDER_IDLE_FRIENDLY: this->SetupFriendly(); break;
	case cPlayer::ORDER_IDLE_OFFENSIVE: this->SetupOffnsive(); break;
	default: return; // �����Ǿ� ���� ���� ���� ��ȣ�� ������
	}
	m_dwNumState = dwNumState; // ���� ��ȯ
}

void cPlayer::OrderFriendly(void)
{
	if (this->CheckState(PATTERN_FRIENDLY))
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_FRIENDLY);
	}
}

void cPlayer::OrderOffensive(void)
{
	if (this->CheckState(PATTERN_OFFENSIVE))
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_OFFENSIVE);
	}
}

void cPlayer::OrderTarget(void)
{
	float fDistSq;
	if (this->DistSqTarget(&fDistSq))
	{
		if (this->CheckState(PATTERN_ATTACK))
		{
			if (fDistSq > m_AbilityParamter.GetRangeSq())
			{
				this->SetStateTrue(PATTERN_TARGET);
				this->OrderMove(&m_pTarget->GetPosition());
			}
			else
			{
				this->SetStateFalse(PATTERN_TARGET);
				this->SetStateFalse(PATTERN_STOP);
				this->SetStateFalse(PATTERN_ATTACK);
				this->SetStateFalse(PATTERN_WALK);
				this->SetStateFalse(PATTERN_RUN);
				this->MoveStop();
				if (g_pMath->Random(2)) m_AbilityParamter.SetDelayTime(this->SetBlendingAnimation(cPlayer::ANIMATION_ATTACK_01));
				else  m_AbilityParamter.SetDelayTime(this->SetBlendingAnimation(cPlayer::ANIMATION_ATTACK_02));
				m_dwNumRealdyTrue |= PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_OFFENSIVE;
				m_dwNumRealdyFalse |= PATTERN_FRIENDLY;
				m_dwNumRealdyState = cPlayer::ORDER_IDLE_OFFENSIVE;
			}
		}
	}
	else this->MoveStop();
}

void cPlayer::OrderIden(void)
{
	if (!this->CheckState(PATTERN_STOP)) return;

	this->SetStateFalse(PATTERN_STOP);
	this->MoveStop();

	if (this->CheckState(PATTERN_FRIENDLY))
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_FRIENDLY);
	}
	else
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_OFFENSIVE);
	}
}

void cPlayer::OrderIdenChange(void)
{
	this->SetStateFalse(PATTERN_STOP);
	this->MoveStop();

	if (this->CheckState(PATTERN_FRIENDLY))
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_OFFENSIVE);
	}
	else
	{
		this->SetStatePattern(cPlayer::ORDER_IDLE_FRIENDLY);
	}
}

void cPlayer::OrderWalk(LPD3DXVECTOR3 pTo)
{
	if (!this->CheckState(PATTERN_WALK)) return;

	this->Rotation(&((*pTo) - this->GetPosition()), 5.0f);
	this->MoveEx(pTo, 0.5f);
	this->SetStateTrue(PATTERN_STOP);

	if (this->CheckState(PATTERN_FRIENDLY))
	{
		//�ϻ���
		this->SetBlendingAnimation(cPlayer::ANIMATION_WALK_FRIENDLY);
	}
	else
	{
		//�������
		this->SetBlendingAnimation(cPlayer::ANIMATION_WALK_OFFENSIVE);
	}
}

void cPlayer::OrderMove(LPD3DXVECTOR3 pTo)
{
	if (this->CheckState(PATTERN_RUN))
	{
		this->Rotation(&((*pTo) - this->GetPosition()), 20.0f);
		this->MoveEx(pTo, 1.0f);
		this->SetStateTrue(PATTERN_STOP);

		if (this->CheckState(PATTERN_FRIENDLY))
		{
			//�ϻ���
			this->SetBlendingAnimation(cPlayer::ANIMATION_RUN_FRIENDLY);
		}
		else
		{
			//�������
			this->SetBlendingAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE);
		}
	}
	else this->OrderWalk(pTo);
}

void cPlayer::OrderAttack(cPlayer* pTarget)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pTarget;
	SAFE_ADDREF(m_pTarget);

	if (this->CheckState(PATTERN_OFFENSIVE))
	{
		this->SetStateTrue(PATTERN_FRIENDLY);
		this->SetStateFalse(PATTERN_OFFENSIVE);
	}

	this->OrderTarget();
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

DWORD cPlayer::RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation, IN float fSpeed)
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
	m_vecAnimationKey[dwAnimationKey].dwKey = m_pAnimationController->GetNumAnimationSets() - 1;
	m_vecAnimationKey[dwAnimationKey].fSpeed = fSpeed;
	//�ִϸ��̼� ��ȣ ��ȯ
	return m_vecAnimationKey[dwAnimationKey].dwKey;
}

void cPlayer::SetAnimation(IN DWORD dwAnimationKey)
{
	DWORD dwNumNextAnimation = m_vecAnimationKey[dwAnimationKey].dwKey;
	if (m_dwNumMainAnimation == dwNumNextAnimation) return;

	if (!m_pAnimationController) return;
	m_pAnimationController->SetTrackSpeed(m_bCurrentTrack, m_vecAnimationKey[dwAnimationKey].fSpeed);

	LPD3DXANIMATIONSET pAnimationSet;
	m_pAnimationController->GetAnimationSet(m_dwNumMainAnimation, &pAnimationSet);
	m_pAnimationController->SetTrackAnimationSet(m_bCurrentTrack, pAnimationSet);
	m_pAnimationController->UnkeyAllTrackEvents(false);
	m_pAnimationController->UnkeyAllTrackEvents(true);
	m_pAnimationController->SetTrackEnable(m_bCurrentTrack, true);
	m_pAnimationController->SetTrackSpeed(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackWeight(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackPosition(m_bCurrentTrack, 0.0);
	SAFE_RELEASE(pAnimationSet);

	m_dwNumMainAnimation = m_vecAnimationKey[dwAnimationKey].dwKey;
}

float cPlayer::SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fSpeed, IN float fTravel)
{
	DWORD dwNumNextAnimation = m_vecAnimationKey[dwAnimationKey].dwKey;
	if (m_dwNumMainAnimation == dwNumNextAnimation) return 0.0f;
	m_pAnimationController->SetTrackSpeed(!m_bCurrentTrack, m_vecAnimationKey[dwAnimationKey].fSpeed * fSpeed);

	//�ʱ�ȭ (�ڼ��� ������ -> ����.)
	float fCurrentTime = m_pAnimationController->GetTime();																			//�ִϸ��̼� ��Ʈ�ѷ��� ����ð�
	LPD3DXANIMATIONSET pAnimationSet = nullptr;																						//�ִϸ��̼� ��Ʈ (�� ����)
	m_pAnimationController->UnkeyAllTrackEvents(false);																				//0�� Ʈ���� �ִϸ��̼� Ű (������) ����
	m_pAnimationController->UnkeyAllTrackEvents(true);																				//1�� Ʈ���� �ִϸ��̼� Ű (������) ����
	D3DXTRACK_DESC TrackDesc;																										//�� Ʈ������

	//���� �ִϸ��̼� (�ڼ��� ������ -> ����.)
	m_pAnimationController->GetAnimationSet(dwNumNextAnimation, &pAnimationSet);													//���� �ִϸ��̼� ��Ʈ ����
	m_pAnimationController->SetTrackAnimationSet(!m_bCurrentTrack, pAnimationSet);													//���� Ʈ���� ���� �ִϸ��̼� ��Ʈ ���
	m_pAnimationController->KeyTrackWeight(!m_bCurrentTrack, 1.0f, fCurrentTime, /*fPlayTime **/ fTravel, D3DXTRANSITION_LINEAR);	//���� Ʈ���� ����ġ�� ������ �÷��� (������ ���)
	m_pAnimationController->SetTrackEnable(!m_bCurrentTrack, true);																	//���� Ʈ���� �����
	m_pAnimationController->GetTrackDesc(!m_bCurrentTrack, &TrackDesc);																//���� Ʈ������ ����
	m_pAnimationController->SetTrackPosition(!m_bCurrentTrack, 0.0f);																//���� Ʈ�� �ʱ�ȭ
	float fPlayTime = pAnimationSet->GetPeriod() / TrackDesc.Speed;																	//���� �ִϸ��̼��� ���� (���� : ��)
	SAFE_RELEASE(pAnimationSet);																									//���� �ִϸ��̼� ��Ʈ ���� (��� �� ����)

	//���� �ִϸ��̼� (�ڼ��� ������ -> ����.)
	m_pAnimationController->KeyTrackWeight(m_bCurrentTrack, 0.0f, fCurrentTime, fTravel, D3DXTRANSITION_LINEAR);	//�� Ʈ���� ����ġ�� ������ ���� (������ ���)
	m_pAnimationController->KeyTrackEnable(m_bCurrentTrack, false, fCurrentTime + fTravel);							//�� Ʈ���� �����ð� ����� ������ (������ ���)


	//�ִϸ��̼� ���� (�ڼ��� ������ -> ����.)
	m_bCurrentTrack = !m_bCurrentTrack;																								//�� Ʈ���� ��ȣ�� �ٲ� (0 �Ǵ� 1 Ʈ���� 2���� ���)
	m_dwNumSubAnimation = m_dwNumMainAnimation;																						//�� Ʈ���� ��ȣ�� ���� Ʈ���� ��ȣ�� ����
	m_dwNumMainAnimation = dwNumNextAnimation;																						//���� Ʈ���� ��ȣ�� �� Ʈ���� ��ȣ�� ����
	
	return fPlayTime;
}


//�������� Release �ϼ���.
float cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pAnimationController || !ppAnimation) return 0.0f;
	SAFE_RELEASE(*ppAnimation);
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey].dwKey, ppAnimation);
	return m_vecAnimationKey[dwAnimationKey].fSpeed;
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

void cPlayer::SetDirection(LPD3DXVECTOR3 pDir)
{
	D3DXVECTOR3 vDir;
	if (pDir) D3DXVec3Normalize(&vDir, pDir);
	else return;

	D3DXVec3Cross(&vDir, &vDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&vDir, &vDir);
	m_matWorld._11 = vDir.x, m_matWorld._12 = vDir.y, m_matWorld._13 = vDir.z;

	m_matWorld._21 = 0.0f, m_matWorld._22 = 1.0f, m_matWorld._33 = 0.0f;

	D3DXVec3Cross(&vDir, &vDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&vDir, &vDir);
	m_matWorld._31 = vDir.x, m_matWorld._32 = vDir.y, m_matWorld._33 = vDir.z;
}

void cPlayer::MoveEx(LPD3DXVECTOR3 pTo, float fSpeed)
{
	assert(m_pActionMove && "�� ĳ���ʹ� �̵��� �� ���� ĳ���� �Դϴ�.");
	this->m_pActionMove->SetToPlay(pTo, m_AbilityParamter.GetMoveSpeed() * fSpeed);
}

void cPlayer::Move(LPD3DXVECTOR3 pTo)
{
	assert(m_pActionMove && "�� ĳ���ʹ� �̵��� �� ���� ĳ���� �Դϴ�.");
	this->m_pActionMove->SetToPlay(pTo, m_AbilityParamter.GetMoveSpeed());
}

void cPlayer::Rotation(LPD3DXVECTOR3 pTo, float fSpeed)
{
	assert(m_pActionMove && "�� ĳ���ʹ� ȸ���� �� ���� ĳ���� �Դϴ�.");
	this->m_pActionDirection->SetToPlay(pTo, fSpeed);
}

void cPlayer::MoveStop(void)
{
	if (!m_pActionMove) return;
	this->SetStateFalse(PATTERN_TARGET);
	this->m_pActionMove->Stop();
}


void cPlayer::PlayerToTarget(float fRange)
{
	cPlayer* pPlayer = g_pObjectManager->GetPlayer();
	if (m_pTarget || !pPlayer) return;

	float fRangeSq = fRange * fRange;
	float fLengtSq = D3DXVec3LengthSq(&(pPlayer->GetPosition() - this->GetPosition()));
	if (fLengtSq < fRangeSq)
	{
		m_pTarget = pPlayer;
		m_pTarget->AddRef();
		this->TargetView();
	}
}

void cPlayer::AutoTarget(float fRange)
{
	if (m_pTarget) g_pObjectManager->GetNextTarget(&m_pTarget, &this->GetPosition(), fRange);
	else
	{
		m_pTarget = g_pObjectManager->GetMinRangeMonster(this, fRange);
		SAFE_ADDREF(m_pTarget);
	}
	if (m_pTarget) this->SetDirection(&(m_pTarget->GetPosition() - this->GetPosition()));
}

void cPlayer::GoToTarget(void)
{
	if (!m_pTarget || !m_pActionMove) return;
	this->m_pActionMove->SetToPlay(&m_pTarget->GetPosition(), m_AbilityParamter.GetMoveSpeed());
}

void cPlayer::GoToTarget(float fSpeed)
{
	if (!m_pTarget || !m_pActionMove) return;
	m_AbilityParamter.SetMoveSpeed(fSpeed);
	this->m_pActionMove->SetToPlay(&m_pTarget->GetPosition(), fSpeed);
}

void cPlayer::KeepToTarget(float fRange)
{
	if (!m_pTarget || !m_pActionMove) return;
	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, &(this->GetPosition() - m_pTarget->GetPosition()));
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	vDir = vDir * fRange;
	this->m_pActionMove->SetToPlay(&(m_pTarget->GetPosition() + vDir), m_AbilityParamter.GetMoveSpeed());
}

void cPlayer::KeepToTarget(float fRange, float fSpeed)
{
	if (!m_pTarget || !m_pActionMove) return;
	m_AbilityParamter.SetMoveSpeed(fSpeed);
	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, &(this->GetPosition() - m_pTarget->GetPosition()));
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	vDir = vDir * fRange;
	this->m_pActionMove->SetToPlay(&(m_pTarget->GetPosition() + vDir), fSpeed);
}

void cPlayer::RotationToTarget(float fAngle)
{
	if (!m_pTarget || !m_pActionMove) return;
	D3DXVECTOR3 vDir = this->GetPosition() - m_pTarget->GetPosition();
	D3DXMATRIXA16 matR;
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	D3DXVec3TransformCoord(&vDir, &vDir, D3DXMatrixRotationY(&matR, fAngle));
	this->m_pActionMove->SetToPlay(&(m_pTarget->GetPosition() + vDir), m_AbilityParamter.GetMoveSpeed());
}

void cPlayer::RotationToTarget(float fAngle, float fSpeed)
{
	if (!m_pTarget || !m_pActionMove) return;
	m_AbilityParamter.SetMoveSpeed(fSpeed);
	D3DXVECTOR3 vDir = this->GetPosition() - m_pTarget->GetPosition();
	D3DXMATRIXA16 matR;
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	D3DXVec3TransformCoord(&vDir, &vDir, D3DXMatrixRotationY(&matR, fAngle));
	this->m_pActionMove->SetToPlay(&(m_pTarget->GetPosition() + vDir), fSpeed);
}

bool cPlayer::DistSqTarget(OUT float * pDist)
{
	if (!m_pTarget) return false;
	(*pDist) = D3DXVec3LengthSq(&(m_pTarget->GetPosition() - this->GetPosition()));
	return true;
}

bool cPlayer::DistTarget(OUT float * pDist)
{
	if (!m_pTarget) return false;
	(*pDist) = D3DXVec3Length(&(m_pTarget->GetPosition() - this->GetPosition()));
	return true;
}

// ���� �Ÿ��� ���ϴ� �Լ� (_�߸��� _��ǻ�͸� ã�µ� �ð��� �����ɸ��ϴ�.)
bool cPlayer::DistTarget(OUT DWORD dwTarget, OUT float fRange)
{
	float fRangeSq = fRange * fRange;
	switch (dwTarget)
	{
	case 0:
		for each (auto pMonster in *g_pObjectManager->GetMonsterVectorPointer())
		{
			if (2 != pMonster->GetAbilityParamter()->GetPlayerID()) continue;
			if (D3DXVec3LengthSq(&(m_pTarget->GetPosition() - this->GetPosition())) < fRangeSq) return true;
		} break;

	case 1: if (g_pObjectManager->GetPlayer()) return D3DXVec3LengthSq(&(g_pObjectManager->GetPlayer()->GetPosition() - this->GetPosition())) > fRangeSq; break;

	case 2:
		for each (auto pMonster in *g_pObjectManager->GetMonsterVectorPointer())
		{
			if (2 != pMonster->GetAbilityParamter()->GetPlayerID()) continue;
			if (D3DXVec3LengthSq(&(m_pTarget->GetPosition() - this->GetPosition())) < fRangeSq) return true;
		} break;

	case 3: if (m_pTarget) return D3DXVec3LengthSq(&(m_pTarget->GetPosition() - this->GetPosition())) < fRangeSq; break;

	}
	return false;
}

//������ ���浹
bool cPlayer::IsCollision(IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir)
{
	float fLength = (D3DXVec3Dot(&(this->GetPosition() - (*pRay)), pDir));
	fLength = D3DXVec3LengthSq(&((*pRay) + (*pDir) * fLength - this->GetPosition()));
	return (fLength  < m_fRadius * m_fRadius);
}

void cPlayer::SetTarget(cPlayer* pTarget)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pTarget;
	SAFE_ADDREF(m_pTarget);
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}
