#pragma once

#define ANI_MATRIX 32

class cCamera;
class cPlayer : public cObject
{
public:
	enum ANIMATION_STAND
	{
		ANIMATION_NULL,
		ANIMATION_IDLE,
		ANIMATION_2,
		ANIMATION_3,
		ANIMATION_4,
		ANIMATION_5,
		ANIMATION_6,
		ANIMATION_END,
	};
	enum MESH_PART
	{
		MESH_DUMMY,
		MESH_HAIR,
		MESH_FACE,
		MESH_BODY,
		MESH_HAND,
		MESH_SHOES,
		MESH_SIZE,
	};
private:
	D3DXMATRIXA16 m_matWorld;

	cCamera* m_pCamera;

	std::vector<DWORD> m_vecAnimationKey;
	std::vector<cSkinnedMesh*> m_vecMesh;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController;
	bool m_bCurrentTrack;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	void ChangeMeshPart(IN DWORD dwPart, IN LPCSTR szFolder, IN LPCSTR szFilename);
	cSkinnedMesh* GetMeshPart(IN DWORD dwPart) { return m_vecMesh[dwPart]; }

	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	LPD3DXANIMATIONCONTROLLER GetAnimationController(void) { return m_pAnimationController; }
	void SetAnimation(IN DWORD dwAnimationKey);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	cCamera* GetCamera(void) { return m_pCamera; }

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

