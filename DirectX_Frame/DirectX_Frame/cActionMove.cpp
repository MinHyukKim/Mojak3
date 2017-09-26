#include "stdafx.h"
#include "cActionMove.h"
#include "cPlayer.h"

cActionMove::cActionMove(void)
	: m_vFrom(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vTo(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vDir(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
{
}

cActionMove::~cActionMove(void)
{
}

void cActionMove::Play(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (pTarget)
	{
		pTarget->SetPosition(&m_vFrom);
	}
	this->cAction::Play();
}

void cActionMove::Stop(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	if (m_vTo != m_vFrom) D3DXVec3Normalize(&m_vDir, &(m_vTo - m_vFrom));	//각도를 계산함(필요 없을 수도 있음)
	m_vTo = m_vFrom = pTarget->GetPosition();
	this->cAction::Stop();
}

void cActionMove::Update(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	this->cAction::Update();
	if (this->GetElapseTime() < this->GetActionTime())
	{
		float fTravelTime = this->GetElapseTime() / this->GetActionTime();

		D3DXVECTOR3 vPosition;
		D3DXVec3Lerp(&vPosition, &m_vFrom, &m_vTo, this->GetTravelTime());
		pTarget->SetPosition(&vPosition);
	}
	else if (this->cAction::GetActionTime())
	{
		pTarget->SetPosition(&m_vTo);

		iActionDelegate* pDelegate = this->GetDelegate();
		if (pDelegate)
		{
			pDelegate->OnFinish(this);
		}

		this->cAction::SetActionTime(0.0f);
	}
}


void cActionMove::SetToPlay(IN LPD3DXVECTOR3 vTo, IN float fSpeed)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	m_vFrom = pTarget->GetPosition();
	m_vTo = *vTo;
	if (m_vTo != m_vFrom)
	{
		D3DXVec3Normalize(&m_vDir, &(m_vTo - m_vFrom));	//각도를 계산함(필요 없을 수도 있음)
		this->cAction::SetActionTime(D3DXVec3Length(&(m_vTo - m_vFrom)) / fSpeed);
		this->cAction::Play();
	}
}

D3DXVECTOR3 & cActionMove::GetDirection(void)
{ 
	if (m_vDir != D3DXVECTOR3(0.0f, 0.0f, 0.0f)) return m_vDir;
	return this->GetTarget()->GetDirection();
}

cActionMove* cActionMove::Create(void)
{
	cActionMove* newAction = new cActionMove;
	newAction->AddRef();
	return newAction;
}

