#pragma once

class cCamera;

class cPlayer : public cObject
{
public:
	enum ANIMATION_STATE
	{
		ANIMATION_NULL,
		ANIMATION_IDLE,
		ANIMATION_END,
	};
private:
	cCamera* m_pCamera;
	cSkinnedMesh* m_pMesh;
	D3DXVECTOR3 m_vPos;

	D3DXMATRIXA16 m_matWorld;
	std::vector<DWORD> m_vecAnimationKey;

public:
	virtual HRESULT Setup(D3DXVECTOR3* pvTarget = NULL) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Update(D3DXVECTOR3 vPos);
	virtual void Render(void) override;

	cCamera* GetCamera(void) { return m_pCamera; }
	void CreateMesh(IN LPCSTR szFolder, IN LPCSTR szFilename);
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
	//HRESULT Setup(void);
};

