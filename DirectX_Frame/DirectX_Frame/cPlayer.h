#pragma once

#define ANI_MATRIX 32

class cActionMove;
class cCamera;
class cPlayer : public cObject
{
public:
	enum PATTERN_STAND
	{
		PATTERN_NULL,
		PATTERN_IDEN_OFFENSIVE,
		PATTERN_IDEN_PEACEFUL,
		PATTERN_RUN_OFFENSIVE,
		PATTERN_RUN_PEACEFUL,
	};
	//홀수 = OFFENSIVE, 짝수 = PEACEFUL
	enum ANIMATION_STAND
	{
		ANIMATION_NULL,
		ANIMATION_IDLE_OFFENSIVE,
		ANIMATION_IDLE_PEACEFUL,
		ANIMATION_WALK_OFFENSIVE,
		ANIMATION_WALK_PEACEFUL,
		ANIMATION_RUN_OFFENSIVE,
		ANIMATION_RUN_PEACEFUL,
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
	//월드의 위치와 회전 값
	D3DXMATRIXA16 m_matWorld;
	//캐릭터의 헤어 색상
	D3DMATERIAL9 m_stHairMaterial;
	//각 부위에 텍스쳐 이름
	std::string m_sCurrentEyeTextureName;
	std::string m_sCurrentMouthTextureName;
	std::string m_sCurrentHairTextureName;
	//캐릭터에 붙여있는 카메라
	cCamera* m_pCamera;
	//캐릭터에 좌표를 이동시킬 액션
	cActionMove* m_pActionMove;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController;
	//부위별 스킨드 메시
	std::vector<cSkinnedMesh*> m_vecMesh;
	//애니메이션 컨트롤러에서 애니메이션의 번호
	std::vector<DWORD> m_vecAnimationKey;
	//애니메이션 컨트롤러의 트랙의 번호
	DWORD m_dwNumMainAnimation;
	DWORD m_dwNumSubAnimation;
	//행동 패턴 번호
	DWORD m_dwNumPattern;
	//애니메이션 컨트롤러에 메인 트랙 번호 (0 또는 1 트랙을 2개만 사용)
	bool m_bCurrentTrack;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	//상태 변환시 1회만 적용
	void SetIdenOffensive(void);
	void SetIdenPeaceful(void);
	void SetRuningOffensive(void);
	void SetRuningPeaceful(void);
	//상태 변환시 행동을 반복함
	void PatternIdenOffensive(void);
	void PatternIdenPeaceful(void);
	void PatternRuningOffensive(void);
	void PatternRuningPeaceful(void);
	//상태 변화
	void SetPatternState(DWORD dwPattern);

	//애니메이션 함수
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	void SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fTravelTime = 0.1f);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

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
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }
	//이동 함수
	void MoveToPlayer(LPD3DXVECTOR3 pTo, float fSpeed);

	cCamera* GetCamera(void) { return m_pCamera; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

