#pragma once
class cPlayer : public cObject
{
private:
	cSkinnedMesh* m_pMesh;

public:
	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void CreateMesh(LPSTR foler)

	static cPlayer* Create(void);
protected:
	cPlayer(void);
	virtual ~cPlayer(void);
};

