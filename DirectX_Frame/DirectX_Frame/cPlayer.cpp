#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"
#include "cCamera.h"
#include "cActionMove.h"

cPlayer::cPlayer(void)
	: m_pCamera(nullptr)
	, m_pActionMove(nullptr)
	, m_pAnimationController(nullptr)
	, m_dwNumMainAnimation(cPlayer::ANIMATION_NULL)
	, m_dwNumSubAnimation(cPlayer::ANIMATION_NULL)
	, m_dwNumPattern(PATTERN_IDEN_PEACEFUL)
	, m_bCurrentTrack(false)
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

	if (!m_pCamera) m_pCamera = cCamera::Create();
	m_pCamera->SetupParentMatrix(&m_matWorld);

	m_vecAnimationKey.resize(ANIMATION_END);
	m_vecMesh.resize(MESH_SIZE);
	
	if (!m_pAnimationController)
	{
		this->ChangeMeshPart(cPlayer::MESH_DUMMY, g_pSkinnedMeshManager->GetSkinnedMesh("더미"));
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

	return S_OK;
}

void cPlayer::Reset(void)
{
	for each(auto p in m_vecMesh) SAFE_DELETE(p);

	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pActionMove);
	SAFE_RELEASE(m_pAnimationController);
}

void cPlayer::Update(void)
{
	if (m_pAnimationController) m_pAnimationController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	SAFE_UPDATE(m_pActionMove);

	// 자세한 이론은 인터넷 검색(검색어) : 유한상태기계(FSM) FlyingSpaghettiMonster 아님
	switch (m_dwNumPattern)
	{
	case cPlayer::PATTERN_NULL: break;
	case cPlayer::PATTERN_IDEN_OFFENSIVE: this->PatternIdenOffensive(); break;
	case cPlayer::PATTERN_IDEN_PEACEFUL: this->PatternIdenPeaceful(); break;
	case cPlayer::PATTERN_RUN_OFFENSIVE: this->PatternRuningOffensive(); break;
	case cPlayer::PATTERN_RUN_PEACEFUL: this->PatternRuningPeaceful(); break;

	default: break;
	}

}

void cPlayer::Render(void)
{
	for (DWORD i = 0; i < MESH_SIZE; i++)
	{
		m_vecMesh[i]->UpdateAndRender(&m_matWorld);
	}

}

//전투 준비 설정
void cPlayer::SetIdenOffensive(void)
{
}
//일반 준비 설정
void cPlayer::SetIdenPeaceful(void)
{
	this->SetBlendingAnimation(cPlayer::ANIMATION_IDLE_PEACEFUL);
}
//전투 달리기 설정
void cPlayer::SetRuningOffensive(void)
{
}
//일반 달리기 설정
void cPlayer::SetRuningPeaceful(void)
{
	this->SetBlendingAnimation(cPlayer::ANIMATION_RUN_PEACEFUL);
}

//전투 준비 상태
void cPlayer::PatternIdenOffensive(void)
{
}
//알반 준비 상태
void cPlayer::PatternIdenPeaceful(void)
{
}
//전투 달리기 상태
void cPlayer::PatternRuningOffensive(void)
{
}
//일반 달리기 상태
void cPlayer::PatternRuningPeaceful(void)
{
	if (m_pActionMove)
	{
		if (m_pActionMove->IsPlay())
		{
			//이동 액션중일 경우	캐릭터 방향을 돌린다.(미구현)

			D3DXMATRIXA16 mat;
			D3DXVECTOR3 v;

			D3DXVec3Cross(&v, &m_pActionMove->GetDirection(), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			m_matWorld._11 = v.x, m_matWorld._12 = v.y, m_matWorld._13 = v.z;

			D3DXVec3Cross(&v, &v, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			m_matWorld._31 = v.x, m_matWorld._32 = v.y, m_matWorld._33 = v.z;
		}
		else
		{
			//이동 액션이 끝나면	iden 상태가 된다.
			this->SetPatternState(cPlayer::PATTERN_IDEN_PEACEFUL);
		}
	}
}


void cPlayer::SetPatternState(DWORD dwPattern)
{
	//패턴 전환시 초기화
	switch (dwPattern)
	{
	case cPlayer::PATTERN_NULL: break;
	case cPlayer::PATTERN_IDEN_OFFENSIVE: this->SetIdenOffensive(); break;
	case cPlayer::PATTERN_IDEN_PEACEFUL:  this->SetIdenPeaceful(); break;


	case cPlayer::PATTERN_RUN_OFFENSIVE: this->SetRuningOffensive(); break;
	case cPlayer::PATTERN_RUN_PEACEFUL:  this->SetRuningPeaceful(); break;
	default: return; // 설정되어 있지 않은 패턴 번호는 무시함
	}
	m_dwNumPattern = dwPattern; // 새로운 패턴으로 전환
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
	if (m_vecMesh[dwPart]) m_vecMesh[dwPart]->SetTextureColor(TextureName, pColor);
}

DWORD cPlayer::RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation)
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
	m_vecAnimationKey[dwAnimationKey] = m_pAnimationController->GetNumAnimationSets() - 1;
	//애니메이션 번호 반환
	return m_vecAnimationKey[dwAnimationKey];
}

void cPlayer::SetAnimation(IN DWORD dwAnimationKey)
{
	DWORD dwNumNextAnimation = m_vecAnimationKey[dwAnimationKey];
	if (m_dwNumMainAnimation == dwNumNextAnimation) return;

	if (!m_pAnimationController) return;

	LPD3DXANIMATIONSET pAnimationSet;
	m_pAnimationController->GetAnimationSet(m_dwNumMainAnimation, &pAnimationSet);
	m_pAnimationController->SetTrackAnimationSet(m_bCurrentTrack, pAnimationSet);
	m_pAnimationController->UnkeyAllTrackEvents(false);
	m_pAnimationController->UnkeyAllTrackEvents(true);
	m_pAnimationController->SetTrackEnable(m_bCurrentTrack, true);
	m_pAnimationController->SetTrackSpeed(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackWeight(m_bCurrentTrack, 1.0f);
	m_pAnimationController->SetTrackPosition(0, 0.0);
	SAFE_RELEASE(pAnimationSet);

	m_dwNumMainAnimation = m_vecAnimationKey[dwAnimationKey];
}

void cPlayer::SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fTravelTime)
{
	DWORD dwNumNextAnimation = m_vecAnimationKey[dwAnimationKey];
	if (m_dwNumMainAnimation == dwNumNextAnimation) return;

	//초기화 (자세한 내용은 -> 참고.)
	float fCurrentTime = m_pAnimationController->GetTime();																			//애니메이션 컨트롤러의 현재시간
	LPD3DXANIMATIONSET pAnimationSet = nullptr;																						//애니메이션 세트 (빈 공간)
	m_pAnimationController->UnkeyAllTrackEvents(false);																				//0번 트랙의 애니메이션 키 (예비동작) 제거
	m_pAnimationController->UnkeyAllTrackEvents(true);																				//1번 트랙의 애니메이션 키 (예비동작) 제거

	//다음 애니메이션 (자세한 내용은 -> 참고.)
	m_pAnimationController->GetAnimationSet(dwNumNextAnimation, &pAnimationSet);													//다음 애니메이션 세트 생성
	float fPlayTime = pAnimationSet->GetPeriod();																					//다음 애니메이션의 길이 (단위 : 초)
	m_pAnimationController->SetTrackAnimationSet(!m_bCurrentTrack, pAnimationSet);													//보조 트랙에 다음 애니메이션 세트 등록
	m_pAnimationController->KeyTrackWeight(!m_bCurrentTrack, 1.0f, fCurrentTime, fPlayTime * fTravelTime, D3DXTRANSITION_LINEAR);	//보조 트랙에 가중치를 서서히 늘려줌 (예비동작)
	m_pAnimationController->SetTrackEnable(!m_bCurrentTrack, true);																	//보조 트랙을 사용함
	SAFE_RELEASE(pAnimationSet);																									//다음 애니메이션 세트 제거 (등록 후 제거)

	//이전 애니메이션 (자세한 내용은 -> 참고.)
	m_pAnimationController->KeyTrackWeight(m_bCurrentTrack, 0.0f, fCurrentTime, fPlayTime * fTravelTime, D3DXTRANSITION_LINEAR);	//주 트랙에 가중치를 서서히 줄임 (예비동작)
	m_pAnimationController->KeyTrackEnable(m_bCurrentTrack, false, fCurrentTime + fPlayTime * fTravelTime);							//주 트랙을 특정시간 경과후 사용안함 (예비동작)

	//애니메이션 변경 (자세한 내용은 -> 참고.)
	m_bCurrentTrack = !m_bCurrentTrack;																								//주 트랙의 번호를 바꿈 (0 또는 1 트랙을 2개만 사용)
	m_dwNumSubAnimation = m_dwNumMainAnimation;																						//주 트랙의 번호를 보조 트랙의 번호로 저장
	m_dwNumMainAnimation = dwNumNextAnimation;																						//다음 트랙의 번호를 주 트랙의 번호로 저장
}


//꺼내간거 Release 하세요.
bool cPlayer::ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey)
{
	if (!m_pAnimationController || !ppAnimation) return false;
	SAFE_RELEASE(*ppAnimation);
	m_pAnimationController->GetAnimationSet(m_vecAnimationKey[dwAnimationKey], ppAnimation);
	return true;
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

void cPlayer::MoveToPlayer(LPD3DXVECTOR3 pTo, float fSpeed)
{
	if (!m_pActionMove) return;
	this->m_pActionMove->SetToPlay(pTo, fSpeed);
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}
