#pragma once
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
	cSkinnedMesh* m_pMesh;
	std::vector<DWORD> m_vecAnimationKey;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	void CreateMesh(IN LPCSTR szFolder, IN LPCSTR szFilename);
	DWORD RegisterAnimation(IN DWORD dwAnimationKey, IN LPD3DXANIMATIONSET pAnimation);
	bool ExportAnimation(OUT LPD3DXANIMATIONSET* ppAnimation, IN DWORD dwAnimationKey = 0);

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

