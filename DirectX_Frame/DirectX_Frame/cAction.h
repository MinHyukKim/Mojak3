#pragma once

class cObject;
class cAction;

//�׼��� �����Ŀ� ������ �׼�
class iActionDelegate
{
public:
	virtual void OnFinish(cAction* pSender) = 0;
};

//�׼� Ÿ�̸�
class cAction : public cObject
{
private:
	float m_fElapsedTime;
	float m_fActionTime;
	cObject* m_pObjectTarget;
	iActionDelegate* m_pDelegate;

public:
	virtual void Play(void);
	virtual void Update(void);

	virtual void SetElapsedTime(float fElapsedTime) final { m_fElapsedTime = fElapsedTime; }
	virtual float GetElapseTime(void) final { return m_fElapsedTime; }
	virtual void SetMoveTo(void) { m_fElapsedTime = m_fActionTime; }
	virtual void SetActionTime(float fActionTime) final { m_fActionTime = fActionTime; }
	virtual float GetActionTime(void) final { return m_fActionTime; }
	virtual void SetObjectTarget(cObject* pTarget) final { m_pObjectTarget = pTarget; }
	virtual cObject* GetObjectTarget(void) final { return m_pObjectTarget; }
	virtual void SetDelegate(iActionDelegate* pDelegate) final { m_pDelegate = pDelegate; }
	virtual iActionDelegate* GetDelegate(void) final { return m_pDelegate; }

	virtual float GetTravelTime(void) final { return m_fElapsedTime / m_fActionTime; }
	virtual bool IsPlay(void) { return (m_fElapsedTime / m_fActionTime) < 1.0f; }

	static cAction* Create(void);
protected:
	cAction(void);
	virtual ~cAction(void);
};

