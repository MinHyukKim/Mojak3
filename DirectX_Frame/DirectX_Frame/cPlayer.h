#pragma once
#include "cAbilityParamter.h"

#define ANI_MATRIX 32

#define PATTERN_NULL		0x00000000
#define PATTERN_FRIENDLY	0x00000001	//일상모드
#define PATTERN_WALK		0x00000004	//걷기가능
#define PATTERN_RUN			0x00000008	//달리기가능
#define PATTERN_ATTACK		0x00000020	//공격가능

#define PATTERN_OFFENSIVE	0x00000002	//전투모드
#define PATTERN_STOP		0x00000010	//정지가능
#define PATTERN_TARGET		0x00000040	//추적모드

#define PATTERN_NORMAL		0x0000002d	//기본상태

struct ST_ANIMATIONKEY
{
	DWORD dwKey;
	float fSpeed;

	ST_ANIMATIONKEY(DWORD _dwKey = 0, float _fSpeed = 1.0f) : dwKey(_dwKey), fSpeed(_fSpeed) {}
};

class cCamera;
class cActionMove;
class cActionDirection;
class cPlayer : public cObject
{
public:
	enum ORDER_STATE
	{
		ORDER_NULL,
		ORDER_IDLE_FRIENDLY,
		ORDER_IDLE_OFFENSIVE,
	};
	enum ANIMATION_STATE
	{
		ANIMATION_NULL,
		ANIMATION_IDLE_OFFENSIVE,
		ANIMATION_IDLE_FRIENDLY,
		ANIMATION_WALK_OFFENSIVE,
		ANIMATION_WALK_FRIENDLY,
		ANIMATION_RUN_OFFENSIVE,
		ANIMATION_RUN_FRIENDLY,
		ANIMATION_ATTACK_OFFENSIVE,
		ANIMATION_ATTACK_FRIENDLY,
		ANIMATION_TEST1,
		ANIMATION_TEST2,
		ANIMATION_TEST3,
		ANIMATION_TEST4,
		ANIMATION_TEST5,
		ANIMATION_END,
	};
	enum MESH_PART
	{
		MESH_DUMMY,
		MESH_HAND,
		MESH_SHOES,
		MESH_BODY,
		MESH_FACE,
		MESH_HAIR,
		MESH_SIZE,
	};
private:
	cAbilityParamter m_AbilityParamter;

	//월드의 위치와 회전 값
	D3DXMATRIXA16 m_matWorld;
	//충돌체 크기
	float m_fRadius;
	//캐릭터의 헤어 색상
	D3DMATERIAL9 m_stHairMaterial;
	//각 부위에 텍스쳐 이름
	std::string m_sCurrentEyeTextureName;
	std::string m_sCurrentMouthTextureName;
	std::string m_sCurrentHairTextureName;
	//캐릭터에 붙여있는 카메라
	cCamera* m_pCamera;
	//캐릭터가 경계중인 캐릭터
	cPlayer* m_pTarget;
	//캐릭터에 좌표를 이동시킬 액션
	cActionMove* m_pActionMove;
	cActionDirection* m_pActionDirection;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController;
	//부위별 스킨드 메시
	std::vector<cSkinnedMesh*> m_vecMesh;
	//명령어 검사
	std::vector<DWORD> m_vecOrderStack;
	//애니메이션 컨트롤러에서 애니메이션의 번호
	std::vector<ST_ANIMATIONKEY> m_vecAnimationKey;
	//애니메이션 컨트롤러의 트랙의 번호
	DWORD m_dwNumMainAnimation;
	DWORD m_dwNumSubAnimation;
	//행동 패턴 번호
	DWORD m_dwNumPattern;
	DWORD m_dwNumState;
	//애니메이션 컨트롤러에 메인 트랙 번호 (0 또는 1 트랙을 2개만 사용)
	bool m_bCurrentTrack;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetupAnimationController(LPCSTR szBoneKey = "더미");


	//상태 변환시 1회만 적용
	void SetupFriendly(void);
	void SetupOffnsive(void);
	//상태 변환시 행동을 반복함
	void PatternUpdate(void);
	//상태 변화
	void SetStatePattern(DWORD dwPattern);

	void SetState(int dwNumPattern) { m_dwNumPattern = dwNumPattern; }
	void SetStateFalse(int dwNumPattern) { m_dwNumPattern &= (~dwNumPattern); }
	void SetStateTrue(int dwNumPattern) { m_dwNumPattern |= dwNumPattern; }
	int GetState(void) const { return m_dwNumPattern; }
	bool CheckState(int dwNumPattern) const { return ((m_dwNumPattern & dwNumPattern) == dwNumPattern); }
	void SetSwitch(int dwNumPattern, bool _isCheck) { if (_isCheck) m_dwNumPattern |= (0x1 << dwNumPattern); else m_dwNumPattern &= ~(0x1 << dwNumPattern); }
	bool GetSwitch(int dwNumPattern) const { if (dwNumPattern < 0 || dwNumPattern > 31) return false; return (m_dwNumPattern & (0x1 << dwNumPattern)); }

	void OrderFriendly(void);
	void OrderOffensive(void);
	void OrderIden(void);
	void OrderIdenChange(void);
	void OrderWalk(LPD3DXVECTOR3 pTo);
	void OrderMove(LPD3DXVECTOR3 pTo);
	void OrderAttack(cPlayer* pTarget);

	//애니메이션 함수
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation, IN float fSpeed = 1.0f);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	float SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fSpeed = 1.0f, IN float fTravel = 0.1f);
	float ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	//형상 함수
	void ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename);
	void ChangeMeshPart(IN DWORD dwPart, IN cSkinnedMesh* pSkinnedMesh);
	void ChangeMeshPartColor(IN DWORD dwPart, IN LPCSTR TextureName, IN LPD3DXCOLOR pColor);
	cSkinnedMesh* GetMeshPart(IN DWORD dwPart) { return m_vecMesh[dwPart]; }

	//초기화 함수
	void SetTextureEye(LPCSTR szEyeName);
	void SetTextureEyeColor(D3DMATERIAL9* pMaterial);
	void SetTextureEyeColor(LPD3DXCOLOR pColor);
	void SetTextureMouth(LPCSTR szEyeName);
	void SetTextureMouthColor(D3DMATERIAL9* pMaterial);
	void SetTextureMouthColor(LPD3DXCOLOR pColor);
	void SetTextureHair(LPCSTR szHairName);
	void SetTextureHairColor(D3DMATERIAL9* pMaterial);
	void SetTextureHairColor(LPD3DXCOLOR pColor);

	//좌표 함수
	
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }
	void SetDirection(LPD3DXVECTOR3 pDirection);
	D3DXVECTOR3 GetDirection(void) { return D3DXVECTOR3(-m_matWorld._31, -m_matWorld._32, -m_matWorld._33); }
	//이동 함수
	void MoveEx(LPD3DXVECTOR3 pTo, float fSpeed = 1.0f);
	void Move(LPD3DXVECTOR3 pTo);
	void Rotation(LPD3DXVECTOR3 pTo, float fSpeed = 10.0f);
	void MoveStop(void);





	//액션 인공지능 함수
	bool TargetAttack(void);

	void PlayerToTarget(float fRange);	//타겟변경
	void TargetView(void) { this->SetDirection(&(m_pTarget->GetPosition() - this->GetPosition()));}
	void AutoTarget(float fRange);	//타겟변경
	void GoToTarget(void);	//타겟에게 이동
	void GoToTarget(float fSpeed);
	void KeepToTarget(float fRange);	//타겟과 일정거리 유지
	void KeepToTarget(float fRange, float fSpeed);
	void RotationToTarget(float fAngle);	//타겟을 해당각도방향으로 직선이동합니다. (범위 : -D3DX_PI ~ D3DX_PI)
	void RotationToTarget(float fAngle, float fSpeed);
	//조건 함수
	bool DistSqTarget(OUT float* pDist); //타겟과 거리를 구하는 함수
	bool DistTarget(OUT float* pDist);
	bool DistTarget(OUT DWORD dwTarget, OUT float fRange); //거리를 확인하는 함수 0중립, 1플레이어, 2컴퓨터, 3타겟

	//충돌함수
	bool IsCollision(IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir);
	//충돌체 반지름
	void SetRadius(float fValue) { m_fRadius = fValue; }
	float GetRadius(void) { return m_fRadius; }

	//상태값
	void SetPattern(DWORD fValue) { m_dwNumPattern = fValue; }
	DWORD GetPattern(void) { return m_dwNumPattern; }
	void SetState(DWORD fValue) { m_dwNumState = fValue; }
	DWORD GetState(void) { return m_dwNumState; }

	//반환함수
	cAbilityParamter* GetAbilityParamter(void) { return &m_AbilityParamter; }
	cCamera* GetCamera(void) { return m_pCamera; }
	void SetTarget(cPlayer* pTarget);
	cPlayer* GetTarget(void) { return m_pTarget; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

