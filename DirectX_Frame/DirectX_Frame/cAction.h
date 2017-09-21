#pragma once

class cPlayer;
class cAction;

//액션이 끝난후에 진행할 액션
class iActionDelegate
{
public:
	virtual void OnFinish(cAction* pSender) = 0;
};

//액션 타이머
class cAction : public cObject
{
private:
	float m_fElapsedTime;
	float m_fActionTime;
	cPlayer* m_pTarget;
	iActionDelegate* m_pDelegate;

public:
	virtual void Play(void);
	virtual void Stop(void);
	virtual void Update(void);

	virtual void SetElapsedTime(float fElapsedTime) final { m_fElapsedTime = fElapsedTime; }
	virtual float GetElapseTime(void) final { return m_fElapsedTime; }
	virtual void SetMoveTo(void) { m_fElapsedTime = m_fActionTime; }
	virtual void SetActionTime(float fActionTime) final { m_fActionTime = fActionTime; }
	virtual float GetActionTime(void) final { return m_fActionTime; }
	virtual void SetTarget(cPlayer* pTarget) final { m_pTarget = pTarget; }
	virtual cPlayer* GetTarget(void) final { return m_pTarget; }
	virtual void SetDelegate(iActionDelegate* pDelegate) final { m_pDelegate = pDelegate; }
	virtual iActionDelegate* GetDelegate(void) final { return m_pDelegate; }

	virtual float GetTravelTime(void) final { return (m_fActionTime ? m_fElapsedTime / m_fActionTime : 1.0f); }

	virtual bool IsPlay(void) { return  m_fActionTime ? true : false; }

	static cAction* Create(void);
protected:
	cAction(void);
	virtual ~cAction(void);
};

