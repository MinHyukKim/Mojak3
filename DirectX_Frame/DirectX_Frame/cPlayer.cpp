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
	, m_dwNumRealdyParam(0)
	, m_bCurrentTrack(false)
	, m_bHitAnimation(false)
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
	//타겟 상태 확인후 유효하지 않으면 해제
	if (m_pTarget && !m_pTarget->GetAbilityParamter()->IsEffective()) m_pTarget->Release();
	if (!m_AbilityParamter.IsEffective()) return;
	if (2 == m_AbilityParamter.GetPlayerID()) this->ComputerAI(); // AI 함수
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
		//0번 트랙 설정
		m_pAnimationController->SetTrackEnable(0, true);
		m_pAnimationController->SetTrackPosition(0, 0.0);
		m_pAnimationController->SetTrackSpeed(0, 1.0f);
		m_pAnimationController->SetTrackWeight(0, 1.0f);
		//1번 트랙 설정
		m_pAnimationController->SetTrackEnable(1, false);
		m_pAnimationController->SetTrackPosition(1, 0.0);
		m_pAnimationController->SetTrackSpeed(1, 0.0f);
		m_pAnimationController->SetTrackWeight(1, 0.0f);
	}
	m_vecAnimationKey.resize(ANIMATION_END);
}

void cPlayer::SetupFriendly(void)
{
	m_dwNumRealdyState = 0;
	this->SetStateTrue(PATTERN_FRIENDLY);
	this->SetStateFalse(PATTERN_OFFENSIVE);
	this->SetBlendingAnimation(cPlayer::ANIMATION_IDLE_FRIENDLY);

}

void cPlayer::SetupOffnsive(void)
{
	m_dwNumRealdyState = 0;
	this->SetRealdyTrue(PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_OFFENSIVE);
	this->SetRealdyFalse(PATTERN_FRIENDLY);
	this->SetBlendingAnimation(cPlayer::ANIMATION_IDLE_OFFENSIVE);
}

void cPlayer::SetupHit(void)
{
	m_dwNumRealdyState = 0;
	float fDelay = 0.0f;
	this->SetStateFalse(PATTERN_STOP);
	if (2.75f < m_AbilityParamter.GetDownGauge())
	{
		if (g_pMath->Random(2)) fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_ENDURE_01);
		else fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_ENDURE_02);
		this->OrderBackMove(&(this->GetPosition() - this->GetDirection() * fDelay));
	}
	else
	{
		if (this->IsHitAnimation()) fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_HIT_01);
		else fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_HIT_02);
		this->SetHitAnimation(!this->IsHitAnimation());
	}
	this->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

//	this->SetRealdyTrue(PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_OFFENSIVE);
//	this->SetRealdyFalse(PATTERN_FRIENDLY);
	this->SetRealdyState(cPlayer::ORDER_OFFENSIVE);
}

void cPlayer::SetupSpin(void)
{
	m_dwNumRealdyState = 0;
	float fDelay = 0.0f;

	this->SetStateFalse(PATTERN_STOP);
	fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_SPIN);
	this->OrderBackMove(&(this->GetPosition() - this->GetDirection() * fDelay * 2.0f));
	this->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

	this->SetRealdyTrue(PATTERN_OFFENSIVE);
	this->SetRealdyFalse(PATTERN_FRIENDLY);
	this->SetRealdyState(cPlayer::ORDER_DOWND);
}

void cPlayer::SetupDownd(void)
{
	m_dwNumRealdyState = 0;
	float fDelay = 0.0f;

	fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_DOWND);
	this->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

	this->SetRealdyState(cPlayer::ORDER_STANDUP);
}

void cPlayer::SetupStandUp(void)
{
	m_dwNumRealdyState = 0;
	float fDelay = 0.0f;

	fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_DOWN_TO_STAND);
	this->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

	this->SetRealdyTrue(PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
	this->SetRealdyState(cPlayer::ORDER_OFFENSIVE);
}

void cPlayer::PatternUpdate(void)
{
	//기본 업데이트
	m_AbilityParamter.Update();
	SAFE_UPDATE(m_pActionMove);
	SAFE_UPDATE(m_pActionDirection);

	if (m_pActionMove && !m_pActionMove->IsPlay())
	{
		if (this->CheckState(PATTERN_STOP))
		{
			this->OrderIden();
		}
		else if (this->CheckState(PATTERN_OFFENSIVE))
		{
			if (m_pActionDirection && !m_pActionDirection->IsPlay())
			{
				this->TargetView();
			}
		}
	}

	// 타겟을 추적중일때
	if (this->CheckState(PATTERN_TARGET))
	{
		this->OrderTarget();
	}
	// 레디 스택
	if (m_AbilityParamter.IsDelayEnd())
	{
		assert(!(m_dwNumRealdyTrue & m_dwNumRealdyFalse) && "행동 알고리즘 충돌");
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
		}
	}
}


void cPlayer::SetStatePattern(DWORD dwNumState)
{
	//패턴 전환시 초기화
	switch (dwNumState)
	{
	case cPlayer::ORDER_FRIENDLY: this->SetupFriendly(); break;
	case cPlayer::ORDER_OFFENSIVE: this->SetupOffnsive(); break;
	case cPlayer::ORDER_HIT: this->SetupHit(); break;
	case cPlayer::ORDER_SPIN: this->SetupSpin(); break;
	case cPlayer::ORDER_DOWND: this->SetupDownd(); break;
	case cPlayer::ORDER_STANDUP: this->SetupStandUp(); break;
	default: return; // 설정되어 있지 않은 패턴 번호는 무시함
	}
	m_dwNumState = dwNumState; // 상태 전환
}

void cPlayer::OrderFriendly(void)
{
	this->SetStatePattern(cPlayer::ORDER_FRIENDLY);
	m_dwNumRealdyTrue |= PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_FRIENDLY;
	m_dwNumRealdyFalse |= PATTERN_OFFENSIVE;
}

void cPlayer::OrderOffensive(void)
{
	m_dwNumRealdyTrue |= PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_OFFENSIVE;
	m_dwNumRealdyFalse |= PATTERN_FRIENDLY;
	this->SetStatePattern(cPlayer::ORDER_OFFENSIVE);
}

void cPlayer::OrderTarget(void)
{
	float fDistSq;
	if (this->DistSqTarget(&fDistSq))
	{
		//타겟이 있을때
		if (this->CheckState(PATTERN_ATTACK))
		{
			//공격모드일때
			if (fDistSq > m_AbilityParamter.GetRangeSq())
			{
				//공격범위 밖에 있을경우
				this->SetStateTrue(PATTERN_TARGET);
				this->OrderMove(&m_pTarget->GetPosition());
			}
			else if (!m_dwNumRealdyState)
			{
				//공격범위 안에 있을경우
				//공격 준비
				this->OrderIden();
				//this->SetDirection(&(m_pTarget->GetPosition() - this->GetPosition()));
				this->SetStateFalse(PATTERN_TARGET | PATTERN_STOP | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
				float fDelay = 0.0f;

				if (this->CheckState(PATTERN_SMASH))	//스매시
				{
					//공격
					fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_SMASH);
					this->SetRealdyFalse(PATTERN_SMASH);

					//피격
					m_pTarget->OrderIden();
					m_pTarget->SetTarget(this);
					m_pTarget->Rotation(&(this->GetPosition() - m_pTarget->GetPosition()), 20.0f);
					m_pTarget->SetStateFalse(PATTERN_TARGET | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_STOP);

					if (m_pTarget->CheckState(PATTERN_COUNTER))
					{
						//반격
						m_pTarget->SetStateFalse(PATTERN_COUNTER);
						fDelay = m_pTarget->SetBlendingAnimation(cPlayer::ANIMATION_COUNTER);
						m_pTarget->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

						m_pTarget->SetRealdyTrue(PATTERN_TARGET | PATTERN_STOP | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
						m_pTarget->SetRealdyState(cPlayer::ORDER_OFFENSIVE);

						//공격
						this->m_AbilityParamter.SetDelayTime(fDelay * 0.3f);
						this->SetStateFalse(PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_STOP);
						this->GetAbilityParamter()->SetDownGauge(m_pTarget->GetAbilityParamter()->GetDownGauge() + 2.25f);

						this->SetRealdyState(cPlayer::ORDER_SPIN);
						this->SetParam(0);

					}
					else
					{
						//공격
						this->m_AbilityParamter.SetDelayTime(fDelay - 0.1f);
						this->SetRealdyTrue(PATTERN_TARGET | PATTERN_STOP | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
						this->SetRealdyState(cPlayer::ORDER_OFFENSIVE);
						//피격
						m_pTarget->SetBlendingAnimation(cPlayer::ANIMATION_GROGGY, fDelay * 0.3f);
						m_pTarget->GetAbilityParamter()->SetDelayTime(fDelay * 0.3f);
						m_pTarget->GetAbilityParamter()->SetDownGauge(m_pTarget->GetAbilityParamter()->GetDownGauge() + 2.25f);

						m_pTarget->SetRealdyState(cPlayer::ORDER_SPIN);
						m_pTarget->SetParam(0);
					}

				}
				else
				{
					//통상 공격
					if (g_pMath->Random(2)) fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_ATTACK_01);
					else  fDelay = this->SetBlendingAnimation(cPlayer::ANIMATION_ATTACK_02);

					//통상 피격
					m_pTarget->OrderIden();
					m_pTarget->SetTarget(this);
					m_pTarget->Rotation(&(this->GetPosition() - m_pTarget->GetPosition()), 20.0f);
					m_pTarget->SetStateFalse(PATTERN_TARGET | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_STOP);

					if (m_pTarget->CheckState(PATTERN_COUNTER))
					{
						//반격
						m_pTarget->SetStateFalse(PATTERN_COUNTER);
						fDelay = m_pTarget->SetBlendingAnimation(cPlayer::ANIMATION_COUNTER);
						m_pTarget->GetAbilityParamter()->SetDelayTime(fDelay - 0.1f);

						m_pTarget->SetRealdyTrue(PATTERN_TARGET | PATTERN_STOP | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
						m_pTarget->SetRealdyState(cPlayer::ORDER_OFFENSIVE);

						//공격
						this->m_AbilityParamter.SetDelayTime(fDelay * 0.3f);
						this->SetStateFalse(PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN | PATTERN_STOP);
						this->GetAbilityParamter()->SetDownGauge(m_pTarget->GetAbilityParamter()->GetDownGauge() + 2.25f);

						this->SetRealdyState(cPlayer::ORDER_SPIN);
						this->SetParam(0);
					}
					else
					{
						//공격
						this->m_AbilityParamter.SetDelayTime(fDelay - 0.1f);
						this->SetRealdyTrue(PATTERN_TARGET | PATTERN_STOP | PATTERN_ATTACK | PATTERN_WALK | PATTERN_RUN);
						this->SetRealdyState(cPlayer::ORDER_OFFENSIVE);
						//피격
						m_pTarget->GetAbilityParamter()->SetDelayTime(fDelay * 0.3f);
						m_pTarget->GetAbilityParamter()->SetDownGauge(m_pTarget->GetAbilityParamter()->GetDownGauge() + this->GetAbilityParamter()->GetPower());

						m_pTarget->SetRealdyState(cPlayer::ORDER_HIT);
						m_pTarget->SetParam(0);
					}
				}
			}
		}
	}
	else this->OrderIden();
}

void cPlayer::OrderIden(void)
{
	if (!this->CheckState(PATTERN_STOP)) return;

	this->SetStateFalse(PATTERN_STOP);
	this->MoveStop();

	if (this->CheckState(PATTERN_FRIENDLY))
	{
		this->SetStatePattern(cPlayer::ORDER_FRIENDLY);
	}
	else
	{
		this->SetStatePattern(cPlayer::ORDER_OFFENSIVE);
	}
}

void cPlayer::OrderIdenChange(void)
{
	this->SetStateFalse(PATTERN_STOP);
	this->MoveStop();

	if (this->CheckState(PATTERN_FRIENDLY))
	{
		this->SetStatePattern(cPlayer::ORDER_OFFENSIVE);
	}
	else
	{
		this->SetStatePattern(cPlayer::ORDER_FRIENDLY);
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
		//일상모드
		this->SetBlendingAnimation(cPlayer::ANIMATION_WALK_FRIENDLY);
	}
	else
	{
		//전투모드
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
			//일상모드
			this->SetBlendingAnimation(cPlayer::ANIMATION_RUN_FRIENDLY);
		}
		else
		{
			//전투모드
			this->SetBlendingAnimation(cPlayer::ANIMATION_RUN_OFFENSIVE);
		}
	}
	else this->OrderWalk(pTo);
}

void cPlayer::OrderBackMove(LPD3DXVECTOR3 pTo)
{
	assert(m_pActionMove && "이 캐릭터는 이동할 수 없는 캐릭터 입니다.");
	this->Rotation(&(this->GetPosition() - (*pTo)), 20.0f);
	this->m_pActionMove->SetToPlay(pTo, 2.0f);
	this->SetStateFalse(PATTERN_STOP);
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
	//키가 적으면 늘리기
	if (m_vecMesh.size() <= dwPart) m_vecMesh.resize(dwPart * 2);
	//기존 메쉬 제거
	SAFE_DELETE(m_vecMesh[dwPart]);
	//새 메시 등록
	m_vecMesh[dwPart] = new cSkinnedMesh((LPSTR)szFolder, (LPSTR)szFilename);

	//애니메이션 컨트롤로 복사
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
	//키가 적으면 늘리기
	if (m_vecMesh.size() <= dwPart) m_vecMesh.resize(dwPart * 2);
	//기존 메쉬 제거
	SAFE_DELETE(m_vecMesh[dwPart]);
	//새 메시 등록
	if (!pSkinnedMesh) return;
	m_vecMesh[dwPart] = new cSkinnedMesh(pSkinnedMesh);

	//애니메이션 컨트롤로 복사
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
	m_mainColor = *pColor;
	if (m_vecMesh[dwPart]) m_vecMesh[dwPart]->SetTextureColor(TextureName, pColor);
}

D3DXCOLOR cPlayer::GetMeshColor()
{
	return m_mainColor;
}

DWORD cPlayer::RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation, IN float fSpeed)
{
	//예외 처리
	if (!m_pAnimationController)
	{
		assert(false && "애니메이션 컨트롤러가 존재하지 않습니다.");
		return 0;
	}

	//키가 적으면 늘리기
	if (m_vecAnimationKey.size() <= dwAnimationKey) m_vecAnimationKey.resize(dwAnimationKey * 2);


	//애니메이션 컨트롤러 재설정
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
	//애니메이션 등록
	m_pAnimationController->RegisterAnimationSet(pAnimation);
	//애니메이션번호를 키에 등록
	m_vecAnimationKey[dwAnimationKey].dwKey = m_pAnimationController->GetNumAnimationSets() - 1;
	m_vecAnimationKey[dwAnimationKey].fSpeed = fSpeed;
	//애니메이션 번호 반환
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

	//초기화 (자세한 내용은 -> 참고.)
	float fCurrentTime = m_pAnimationController->GetTime();																			//애니메이션 컨트롤러의 현재시간
	LPD3DXANIMATIONSET pAnimationSet = nullptr;																						//애니메이션 세트 (빈 공간)
	m_pAnimationController->UnkeyAllTrackEvents(false);																				//0번 트랙의 애니메이션 키 (예비동작) 제거
	m_pAnimationController->UnkeyAllTrackEvents(true);																				//1번 트랙의 애니메이션 키 (예비동작) 제거
	D3DXTRACK_DESC TrackDesc;																										//빈 트랙정보

	//다음 애니메이션 (자세한 내용은 -> 참고.)
	m_pAnimationController->GetAnimationSet(dwNumNextAnimation, &pAnimationSet);													//다음 애니메이션 세트 생성
	m_pAnimationController->SetTrackAnimationSet(!m_bCurrentTrack, pAnimationSet);													//보조 트랙에 다음 애니메이션 세트 등록
	m_pAnimationController->KeyTrackWeight(!m_bCurrentTrack, 1.0f, fCurrentTime, /*fPlayTime **/ fTravel, D3DXTRANSITION_LINEAR);	//보조 트랙에 가중치를 서서히 늘려줌 (예비동작 등록)
	m_pAnimationController->SetTrackEnable(!m_bCurrentTrack, true);																	//보조 트랙을 사용함
	m_pAnimationController->GetTrackDesc(!m_bCurrentTrack, &TrackDesc);																//보조 트랙정보 저장
	m_pAnimationController->SetTrackPosition(!m_bCurrentTrack, 0.0f);																//보조 트랙 초기화
	float fPlayTime = pAnimationSet->GetPeriod() / TrackDesc.Speed;																	//다음 애니메이션의 길이 (단위 : 초)
	SAFE_RELEASE(pAnimationSet);																									//다음 애니메이션 세트 제거 (등록 후 제거)

	//이전 애니메이션 (자세한 내용은 -> 참고.)
	m_pAnimationController->KeyTrackWeight(m_bCurrentTrack, 0.0f, fCurrentTime, fTravel, D3DXTRANSITION_LINEAR);					//주 트랙에 가중치를 서서히 줄임 (예비동작 등록)
	m_pAnimationController->KeyTrackEnable(m_bCurrentTrack, false, fCurrentTime + fTravel);											//주 트랙을 일정시간 경과후 사용안함 (예비동작 등록)


	//애니메이션 변경 (자세한 내용은 -> 참고.)
	m_bCurrentTrack = !m_bCurrentTrack;																								//주 트랙의 번호를 바꿈 (0 또는 1 트랙을 2개만 사용)
	m_dwNumSubAnimation = m_dwNumMainAnimation;																						//주 트랙의 번호를 보조 트랙의 번호로 저장
	m_dwNumMainAnimation = dwNumNextAnimation;																						//다음 트랙의 번호를 주 트랙의 번호로 저장
	
	return fPlayTime;
}


//꺼내간거 Release 하세요.
float cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pAnimationController || !ppAnimation) return 0.0f;
	SAFE_RELEASE(*ppAnimation);
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey].dwKey, ppAnimation);
	return m_vecAnimationKey[dwAnimationKey].fSpeed;
}

void cPlayer::SetTextureEye(LPCSTR szEyeName)
{
	//얼굴이 있으면
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentEyeTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureChange(m_sCurrentEyeTextureName.c_str(), szEyeName);
	}
	//텍스쳐 이름 업데이트
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
	//얼굴이 있으면 
	if (m_vecMesh[cPlayer::MESH_FACE] && m_sCurrentMouthTextureName.length())
	{
		m_vecMesh[cPlayer::MESH_FACE]->SetTextureChange(m_sCurrentMouthTextureName.c_str(), szEyeName);
	}
	//텍스쳐 이름 업데이트
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
	assert(m_pActionMove && "이 캐릭터는 이동할 수 없는 캐릭터 입니다.");
	this->m_pActionMove->SetToPlay(pTo, m_AbilityParamter.GetMoveSpeed() * fSpeed);
}

void cPlayer::Move(LPD3DXVECTOR3 pTo)
{
	assert(m_pActionMove && "이 캐릭터는 이동할 수 없는 캐릭터 입니다.");
	this->m_pActionMove->SetToPlay(pTo, m_AbilityParamter.GetMoveSpeed());
}

void cPlayer::Rotation(LPD3DXVECTOR3 pTo, float fSpeed)
{
	assert(m_pActionMove && "이 캐릭터는 회전할 수 없는 캐릭터 입니다.");
	this->m_pActionDirection->SetToPlay(pTo, fSpeed);
}

void cPlayer::ComputerAI(void)
{
	if (this->CheckState(PATTERN_FRIENDLY))
	{
		//일상 모드일때
		if (m_AbilityParamter.IsDelayEnd())
		{
			//지연시간이 없으면
			float fFriendlyRange = 10.0f;
			if (!this->DistTarget(1, fFriendlyRange))
			{
				//'플레이어'와 거리가 '10.0f' 미만일때 ('1'와 거리가 'fFriendlyRange' 이상이 아닐때)
				float fOffensiveRange = 5.0f;
				if (this->DistTarget(1, fFriendlyRange))
				{
					//'플레이어'와 거리가 '5.0f' 이상일때 ('1'와 거리가 'fOffensiveRange' 이상일때)
					RotationToTargetWalk(this, g_pMath->Random(-D3DX_PI, D3DX_PI), g_pMath->Random(10.0f));
					m_AbilityParamter.SetDelayTime(g_pMath->Random(3.0f, 8.0f));
				}
				else
				{
					//'플레이어'와 거리가 '5.0f' 미만일때 ('1'와 거리가 'fOffensiveRange' 이상이 아닐때)
					if (g_pMath->Random(8))
					{
						RotationToTargetWalk(g_pObjectManager->GetPlayer(), g_pMath->Random(-1.0f, 1.0f), g_pMath->Random(1.0f, 10.0f));
						m_AbilityParamter.SetDelayTime(g_pMath->Random(5.0f, 10.0f));
					}
					else
					{
						SAFE_RELEASE(m_pTarget);
						m_pTarget = g_pObjectManager->GetPlayer();
						SAFE_ADDREF(m_pTarget);
						this->OrderIdenChange();
					}
				}
			}
		}
	}
	else if (this->CheckState(PATTERN_OFFENSIVE))
	{
		//전투 모드일때
		if (!this->DistTarget(3, 5.0f))
		{
			//타겟과 거리가 5.0f 초과일때
			this->OrderIdenChange();
		}
		else if (!this->CheckState(PATTERN_TARGET))
		{
			//공격하려 가는중이 아닐때
			if (this->m_AbilityParamter.IsDelayEnd())
			{
				if (this->CheckState(PATTERN_COUNTER))
				{
					this->SetStateTrue(PATTERN_WALK | PATTERN_RUN);
					this->SetStateFalse(PATTERN_COUNTER);
				}
				//지연시간이 없으면
				if (this->DistTarget(3, m_AbilityParamter.GetRange() + 0.01f))
				{
					//타겟이 공격범위 안에 있을경우
					this->OrderAttack(m_pTarget);
				}
				else
				{
					//타겟이 공격범위 밖에 있을경우
					switch (g_pMath->Random(5))
					{
					case 0:
						//아무것도 하지않고 3~8초 쉰다.
						this->m_AbilityParamter.SetDelayTime(g_pMath->Random(3.0f, 8.0f));
						break;

					case 1:
						//타겟에게 강한 공격한다.
						this->OrderAttack(m_pTarget);
						this->SetStateTrue(PATTERN_SMASH);
						break;

					case 2:
						//일정시간동안 공격에 대비한다.
						this->SetStateTrue(PATTERN_COUNTER);
						this->SetStateFalse(PATTERN_WALK | PATTERN_RUN);
						this->m_AbilityParamter.SetDelayTime(g_pMath->Random(3.0f, 8.0f));
						break;

					case 3:
						//타겟 주위를 맴돈다.
						this->RotationToTarget(g_pMath->Random(-1.5f, 1.5f));
						this->m_AbilityParamter.SetDelayTime(g_pMath->Random(1.0f, 3.0f));
						break;

					default:
						//타겟에게 일반 공격한다.
						this->OrderAttack(m_pTarget);
						break;
					}
				}
			}
		}
	}
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
//	this->m_pActionMove->SetToPlay(&(m_pTarget->GetPosition() + vDir), m_AbilityParamter.GetMoveSpeed());
	OrderMove(&(m_pTarget->GetPosition() + vDir));
}

void cPlayer::RotationToTarget(cPlayer* pTarget, float fAngle, float Distance)
{
	if (!pTarget || !m_pActionMove) return;
	D3DXVECTOR3 vDir;
	D3DXMATRIXA16 matR;
	if (this == pTarget) D3DXVec3Normalize(&vDir, &this->GetDirection());
	else D3DXVec3Normalize(&vDir, &(this->GetPosition() - pTarget->GetPosition()));
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	D3DXVec3TransformCoord(&vDir, &vDir, D3DXMatrixRotationY(&matR, fAngle));
	this->OrderMove(&(pTarget->GetPosition() + vDir * Distance));
}
void cPlayer::RotationToTargetWalk(cPlayer* pTarget, float fAngle, float Distance)
{
	if (!pTarget || !m_pActionMove) return;
	D3DXVECTOR3 vDir;
	D3DXMATRIXA16 matR;
	if (this == pTarget) D3DXVec3Normalize(&vDir, &this->GetDirection());
	else D3DXVec3Normalize(&vDir, &(this->GetPosition() - pTarget->GetPosition()));
	if (vDir == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) vDir = m_pActionMove->GetDirection();
	D3DXVec3TransformCoord(&vDir, &vDir, D3DXMatrixRotationY(&matR, fAngle));
	this->OrderWalk(&(pTarget->GetPosition() + vDir * Distance));
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

// 대상과 거리를 비교하는 함수 (_중립과 _컴퓨터를 찾는데 시간이 오래걸립니다.)
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

//광선과 원충돌
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
