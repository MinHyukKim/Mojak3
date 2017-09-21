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
	//Ȧ�� = OFFENSIVE, ¦�� = PEACEFUL
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
	//������ ��ġ�� ȸ�� ��
	D3DXMATRIXA16 m_matWorld;
	//ĳ������ ��� ����
	D3DMATERIAL9 m_stHairMaterial;
	//�� ������ �ؽ��� �̸�
	std::string m_sCurrentEyeTextureName;
	std::string m_sCurrentMouthTextureName;
	std::string m_sCurrentHairTextureName;
	//ĳ���Ϳ� �ٿ��ִ� ī�޶�
	cCamera* m_pCamera;
	//ĳ���Ϳ� ��ǥ�� �̵���ų �׼�
	cActionMove* m_pActionMove;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController;
	//������ ��Ų�� �޽�
	std::vector<cSkinnedMesh*> m_vecMesh;
	//�ִϸ��̼� ��Ʈ�ѷ����� �ִϸ��̼��� ��ȣ
	std::vector<DWORD> m_vecAnimationKey;
	//�ִϸ��̼� ��Ʈ�ѷ��� Ʈ���� ��ȣ
	DWORD m_dwNumMainAnimation;
	DWORD m_dwNumSubAnimation;
	//�ൿ ���� ��ȣ
	DWORD m_dwNumPattern;
	//�ִϸ��̼� ��Ʈ�ѷ��� ���� Ʈ�� ��ȣ (0 �Ǵ� 1 Ʈ���� 2���� ���)
	bool m_bCurrentTrack;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	//���� ��ȯ�� 1ȸ�� ����
	void SetIdenOffensive(void);
	void SetIdenPeaceful(void);
	void SetRuningOffensive(void);
	void SetRuningPeaceful(void);
	//���� ��ȯ�� �ൿ�� �ݺ���
	void PatternIdenOffensive(void);
	void PatternIdenPeaceful(void);
	void PatternRuningOffensive(void);
	void PatternRuningPeaceful(void);
	//���� ��ȭ
	void SetPatternState(DWORD dwPattern);

	//�ִϸ��̼� �Լ�
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	void SetBlendingAnimation(IN DWORD dwAnimationKey, IN float fTravelTime = 0.1f);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	//���� �Լ�
	void ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename);
	void ChangeMeshPart(IN DWORD dwPart, IN cSkinnedMesh* pSkinnedMesh);
	void ChangeMeshPartColor(IN DWORD dwPart, IN LPCSTR TextureName, IN LPD3DXCOLOR pColor);
	cSkinnedMesh* GetMeshPart(IN DWORD dwPart) { return m_vecMesh[dwPart]; }

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
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }
	//�̵� �Լ�
	void MoveToPlayer(LPD3DXVECTOR3 pTo, float fSpeed);

	cCamera* GetCamera(void) { return m_pCamera; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

