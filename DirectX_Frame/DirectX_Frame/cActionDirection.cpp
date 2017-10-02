#include "stdafx.h"
#include "cActionDirection.h"
#include "cPlayer.h"

cActionDirection::cActionDirection(void)
{

}

cActionDirection::~cActionDirection(void)
{
}


void cActionDirection::Play(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (pTarget)
	{
		D3DXVec3Normalize(&m_vFrom, &m_vFrom);
		D3DXVec3Normalize(&m_vTo, &m_vTo);
		//pTarget->SetDirection(&m_vFrom);
	}
	this->cAction::Play();
}

void cActionDirection::Stop(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	m_vTo = m_vFrom = pTarget->GetDirection();
	this->cAction::Stop();
}

void cActionDirection::Update(void)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	this->cAction::Update();
	if (this->GetElapseTime() < this->GetActionTime())
	{
		float fTravelTime = this->GetElapseTime() / this->GetActionTime();

		D3DXVECTOR3 vPosition;
		D3DXVec3Normalize(&vPosition, D3DXVec3Lerp(&vPosition, &m_vFrom, &m_vTo, this->GetTravelTime()));
		pTarget->SetDirection(&vPosition);
	}
	else if (this->cAction::GetActionTime())
	{

		if (m_vTo != D3DXVECTOR3(0.0f, 0.0f, 0.0f))	pTarget->SetDirection(&m_vTo);
		else pTarget->SetDirection(&this->GetTarget()->GetDirection());
	
		iActionDelegate* pDelegate = this->GetDelegate();
		if (pDelegate) pDelegate->OnFinish(this);

		this->cAction::SetActionTime(0.0f);
	}
}

void cActionDirection::SetToPlay(IN LPD3DXVECTOR3 vTo, IN float fSpeed)
{
	cPlayer* pTarget = this->GetTarget();
	if (!pTarget) return;

	D3DXVec3Normalize(&m_vFrom, &(pTarget->GetDirection()));
	D3DXVec3Normalize(&m_vTo, vTo);

	if (m_vTo != m_vFrom)
	{
		this->cAction::SetActionTime(D3DXVec3Length(&(m_vTo - m_vFrom)) / fSpeed);
		this->cAction::Play();
	}
}

cActionDirection* cActionDirection::Create(void)
{
	cActionDirection* newAction = new cActionDirection;
	newAction->AddRef();
	return newAction;
}
