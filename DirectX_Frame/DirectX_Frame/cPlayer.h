#pragma once

#define ANI_MATRIX 32

class cCamera;
class cPlayer : public cObject
{
public:
	enum PATTE_STAND
	{
		PATTE_IDEN,
		PATTE_OFFENSIVE,
	};
	enum ANIMATION_STAND
	{
		ANIMATION_NULL,
		ANIMATION_IDLE_PEACEFUL,
		ANIMATION_IDLE_OFFENSIVE,
		ANIMATION_WALK_PEACEFUL,
		ANIMATION_WALK_OFFENSIVE,
		ANIMATION_RUN_PEACEFUL,
		ANIMATION_RUN_OFFENSIVE,
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
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;

	std::string m_sCurrentEyeTextureName;
	std::string m_sCurrentMouthTextureName;
	std::string m_sCurrentHairTextureName;

	D3DMATERIAL9 m_stHairMaterial;

	cCamera* m_pCamera;

	std::vector<DWORD> m_vecAnimationKey;
	std::vector<cSkinnedMesh*> m_vecMesh;

	LPD3DXANIMATIONCONTROLLER m_pAnimationController;

	bool m_bCurrentTrack;

	DWORD m_CurrentAnimation;
	DWORD m_PrevAnimation;


public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	void ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename);
	void ChangeMeshPart(IN DWORD dwPart, IN cSkinnedMesh* pSkinnedMesh);
	void ChangeMeshPartColor(IN DWORD dwPart, IN LPCSTR TextureName, IN LPD3DXCOLOR pColor);
	cSkinnedMesh* GetMeshPart(IN DWORD dwPart) { return m_vecMesh[dwPart]; }

	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	void SetBlendingAnimation(int nAnimationKey, float fTravelTime = 0.1f);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	void SetTextureEye(LPCSTR szEyeName);
	void SetTextureEyeColor(D3DMATERIAL9* pMaterial);
	void SetTextureEyeColor(LPD3DXCOLOR pColor);
	void SetTextureMouth(LPCSTR szEyeName);
	void SetTextureMouthColor(D3DMATERIAL9* pMaterial);
	void SetTextureMouthColor(LPD3DXCOLOR pColor);
	void SetTextureHair(LPCSTR szHairName);
	void SetTextureHairColor(D3DMATERIAL9* pMaterial);
	void SetTextureHairColor(LPD3DXCOLOR pColor);


	D3DXVECTOR3 GetPosition(void) { return m_vPosition; }
	void SetPosition(LPD3DXVECTOR3 pPosition) { m_vPosition = *pPosition; }
	void SetPosX(float fX) { m_vPosition.x = fX; }
	void SetPosY(float fY) { m_vPosition.y = fY; }
	void SetPosZ(float fZ) { m_vPosition.z = fZ; }
	float GetPosX(void) { return m_vPosition.x; }
	float GetPosY(void) { return m_vPosition.y; }
	float GetPosZ(void) { return m_vPosition.z; }

	cCamera* GetCamera(void) { return m_pCamera; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

