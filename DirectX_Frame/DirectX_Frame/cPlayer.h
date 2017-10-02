#pragma once
#include "cAbilityParamter.h"

#define ANI_MATRIX 32

#define PATTERN_NULL		0x00000000
#define PATTERN_FRIENDLY	0x00000001	//�ϻ���
#define PATTERN_WALK		0x00000004	//�ȱⰡ��
#define PATTERN_RUN			0x00000008	//�޸��Ⱑ��
#define PATTERN_ATTACK		0x00000020	//���ݰ���

#define PATTERN_OFFENSIVE	0x00000002	//�������
#define PATTERN_STOP		0x00000010	//��������
#define PATTERN_TARGET		0x00000040	//�������
#define PATTERN_BACKMOVE	0x00000080	//�з���, ���ư�
#define PATTERN_SMASH		0x00000100	//���Ž�
#define PATTERN_DEFENCE		0x00000200	//���潺
#define PATTERN_COUNTER		0x00000400	//ī����

#define PATTERN_NORMAL		0x0000002d	//�⺻����

struct ST_CONTAINER
{
	DWORD dwKey;
	float fSpeed;

	ST_CONTAINER(DWORD _dwKey = 0, float _fSpeed = 1.0f) : dwKey(_dwKey), fSpeed(_fSpeed) {}
};

//struct ST_CONTAINER2
//{
//	DWORD dwKey;
//	double worldTime;
//
//	ST_CONTAINER2(DWORD _dwKey = 0, double _Time = 1.0f) : dwKey(_dwKey), worldTime(_Time) {}
//};

class cCamera;
class cActionMove;
class cActionDirection;
class cPlayer : public cObject
{
public:
	enum ORDER_STATE
	{
		ORDER_NULL,
		ORDER_FRIENDLY,
		ORDER_OFFENSIVE,
		ORDER_HIT,
		ORDER_SPIN,
		ORDER_DOWND,
		ORDER_STANDUP,
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
		ANIMATION_ATTACK_01,
		ANIMATION_ATTACK_02,
		ANIMATION_SMASH,
		ANIMATION_COUNTER,
		ANIMATION_HIT_01,
		ANIMATION_HIT_02,
		ANIMATION_SPIN,
		ANIMATION_GROGGY,
		ANIMATION_DOWND,
		ANIMATION_DOWN_TO_STAND,
		ANIMATION_ENDURE_01,
		ANIMATION_ENDURE_02,
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

	//������ ��ġ�� ȸ�� ��
	D3DXMATRIXA16 m_matWorld;
	//�浹ü ũ��
	float m_fRadius;
	//ĳ������ ��� ����
	D3DMATERIAL9 m_stHairMaterial;
	//�� ������ �ؽ��� �̸�
	std::string m_sCurrentEyeTextureName;
	std::string m_sCurrentMouthTextureName;
	std::string m_sCurrentHairTextureName;
	//ĳ���Ϳ� �ٿ��ִ� ī�޶�
	cCamera* m_pCamera;
	//ĳ���Ͱ� ������� ĳ����
	cPlayer* m_pTarget;
	//ĳ���Ϳ� ��ǥ�� �̵���ų �׼�
	cActionMove* m_pActionMove;
	cActionDirection* m_pActionDirection;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController;
	//������ ��Ų�� �޽�
	std::vector<cSkinnedMesh*> m_vecMesh;
	//��ɾ� �˻�
	std::vector<DWORD> m_vecOrderStack;
	//�ִϸ��̼� ��Ʈ�ѷ����� �ִϸ��̼��� ��ȣ
	std::vector<ST_CONTAINER> m_vecAnimationKey;
	//�ִϸ��̼� ��Ʈ�ѷ��� Ʈ���� ��ȣ
	DWORD m_dwNumMainAnimation;
	DWORD m_dwNumSubAnimation;
	//�ൿ ���� ��ȣ
	DWORD m_dwNumRealdyTrue;
	DWORD m_dwNumRealdyFalse;
	DWORD m_dwNumRealdyState;
	DWORD m_dwNumRealdyParam;
	DWORD m_dwNumPattern;
	DWORD m_dwNumState;
	//�ִϸ��̼� ��Ʈ�ѷ��� ���� Ʈ�� ��ȣ (0 �Ǵ� 1 Ʈ���� 2���� ���)
	bool m_bCurrentTrack;
	//�ǰ���Ʈ�ѷ�
	bool m_bHitAnimation;

	//���� �÷� ����
	D3DXCOLOR m_mainColor;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetupAnimationController(LPCSTR szBoneKey = "����");


	//���� ��ȯ�� 1ȸ�� ����
	void SetupFriendly(void);
	void SetupOffnsive(void);
	void SetupHit(void);
	void SetupSpin(void);
	void SetupDownd(void);
	void SetupStandUp(void);
	//���� ��ȯ�� �ൿ�� �ݺ���
	void PatternUpdate(void);
	//���� ��ȭ
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

	void OrderTarget(void);
	void OrderIden(void);
	void OrderIdenChange(void);
	void OrderWalk(LPD3DXVECTOR3 pTo);
	void OrderMove(LPD3DXVECTOR3 pTo);
	void OrderBackMove(LPD3DXVECTOR3 pTo);
	void OrderAttack(cPlayer* pTarget);

	//�ִϸ��̼� �Լ�
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation, IN float fSpeed = 1.0f);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	float SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fSpeed = 1.0f, IN float fTravel = 0.1f);
	float ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	//���� �Լ�
	void ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename);
	void ChangeMeshPart(IN DWORD dwPart, IN cSkinnedMesh* pSkinnedMesh);
	void ChangeMeshPartColor(IN DWORD dwPart, IN LPCSTR TextureName, IN LPD3DXCOLOR pColor);
	cSkinnedMesh* GetMeshPart(IN DWORD dwPart) { return m_vecMesh[dwPart]; }

	D3DXCOLOR GetMeshColor();

	//�ʱ�ȭ �Լ�
	void SetTextureEye(LPCSTR szEyeName);
	void SetTextureEyeColor(D3DMATERIAL9* pMaterial);
	void SetTextureEyeColor(LPD3DXCOLOR pColor);
	void SetTextureMouth(LPCSTR szEyeName);
	void SetTextureMouthColor(D3DMATERIAL9* pMaterial);
	void SetTextureMouthColor(LPD3DXCOLOR pColor);
	void SetTextureHair(LPCSTR szHairName);
	void SetTextureHairColor(D3DMATERIAL9* pMaterial);
	void SetTextureHairColor(LPD3DXCOLOR pColor);

	//��ǥ �Լ�
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
	//�̵� �Լ�
	void MoveEx(LPD3DXVECTOR3 pTo, float fSpeed = 1.0f);
	void Move(LPD3DXVECTOR3 pTo);
	void Rotation(LPD3DXVECTOR3 pTo, float fSpeed = 10.0f);
	void MoveStop(void);


	//�׼� �ΰ����� �Լ�
	void PlayerToTarget(float fRange);	//Ÿ�ٺ���
	void TargetView(void) { this->SetDirection(&(m_pTarget->GetPosition() - this->GetPosition()));}
	void AutoTarget(float fRange);	//Ÿ�ٺ���
	void GoToTarget(void);	//Ÿ�ٿ��� �̵�
	void GoToTarget(float fSpeed);
	void KeepToTarget(float fRange);	//Ÿ�ٰ� �����Ÿ� ����
	void KeepToTarget(float fRange, float fSpeed);
	void RotationToTarget(float fAngle);	//Ÿ���� �ش簢���������� �����̵��մϴ�. (���� : -D3DX_PI ~ D3DX_PI)
	void RotationToTarget(float fAngle, float fSpeed);
	//���� �Լ�
	bool DistSqTarget(OUT float* pDist); //Ÿ�ٰ� �Ÿ��� ���ϴ� �Լ�
	bool DistTarget(OUT float* pDist);
	bool DistTarget(OUT DWORD dwTarget, OUT float fRange); //�Ÿ��� Ȯ���ϴ� �Լ� 0�߸�, 1�÷��̾�, 2��ǻ��, 3Ÿ��

	//�浹�Լ�
	bool IsCollision(IN LPD3DXVECTOR3 pRay, IN LPD3DXVECTOR3 pDir);
	//�浹ü ������
	void SetRadius(float fValue) { m_fRadius = fValue; }
	float GetRadius(void) { return m_fRadius; }

	void SetHitAnimation(bool bValue) { m_bHitAnimation = bValue; }
	bool IsHitAnimation(void) { return m_bHitAnimation; }

	//���°�
	void SetPattern(DWORD dwValue) { m_dwNumPattern = dwValue; }
	DWORD GetPattern(void) { return m_dwNumPattern; }
	void SetState(DWORD dwValue) { m_dwNumState = dwValue; }
	DWORD GetState(void) { return m_dwNumState; }
	void SetParam(DWORD dwValue) { m_dwNumRealdyParam = dwValue; }
	DWORD GetParam(void) { return m_dwNumRealdyParam; }
	void SetRealdyTrue(DWORD dwValue) { m_dwNumRealdyTrue = dwValue; }
	DWORD GetRealdyTrue(void) { return m_dwNumRealdyTrue; }
	void SetRealdyFalse(DWORD dwValue) { m_dwNumRealdyFalse = dwValue; }
	DWORD GetRealdyFalse(void) { return m_dwNumRealdyFalse; }
	void SetRealdyState(DWORD dwValue) { m_dwNumRealdyState = dwValue; }
	DWORD GetRealdyState(void) { return m_dwNumRealdyState; }

	//��ȯ�Լ�
	cAbilityParamter* GetAbilityParamter(void) { return &m_AbilityParamter; }
	cCamera* GetCamera(void) { return m_pCamera; }
	void SetTarget(cPlayer* pTarget);
	cPlayer* GetTarget(void) { return m_pTarget; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

