#pragma once

#define g_pAnimationManager cAnimationManager::GetInstance()

class cAnimationManager
{
private:
	std::map<std::string, LPD3DXANIMATIONSET> m_mapAnimationSet;
public:
	LPD3DXANIMATIONSET RegisterAnimation(LPCSTR szFullPath, LPCSTR szKeyName);
	LPD3DXANIMATIONSET GetAnimation(LPCSTR szKeyName);
	LPD3DXANIMATIONSET GetAnimation(std::string& sKeyName);

	void Destroy(void);

	static cAnimationManager* GetInstance() { static cAnimationManager instance; return &instance; }
private:
	cAnimationManager(void);
	virtual ~cAnimationManager(void);
};

