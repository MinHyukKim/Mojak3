#include "stdafx.h"
#include "cActionMove.h"
#include "cObject.h"

cActionMove::cActionMove(void)
	: m_vFrom(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vTo(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

cActionMove::~cActionMove(void)
{
}

void cActionMove::Play(void)
{
	cObject* pTarget = this->GetObjectTarget();
	if (pTarget)
	{
		//pTarget->SetPosition(m_vFrom);
	}
	this->cAction::Play();
}

void cActionMove::Update(void)
{
	cObject* pTarget = this->GetObjectTarget();
	if (!pTarget) return;
	this->cAction::Update();
	if (this->GetElapseTime() < this->GetActionTime())
	{
		float fTravelTime = this->GetElapseTime() / this->GetActionTime();

		D3DXVECTOR3 vPosition;
		D3DXVec3Lerp(&vPosition, &m_vFrom, &m_vTo, this->GetTravelTime());
		//pTarget->SetPosition(vPosition);
	}
	else
	{
		//pTarget->SetPosition(m_vTo);

		iActionDelegate* pDelegate = this->GetDelegate();
		if (pDelegate)
		{
			pDelegate->OnFinish(this);
		}
	}
}

//cActionMove* cActionMove::AddRef(void)
//{
//	//return (cActionMove*) this->cNode::AddRef();
//}

cActionMove* cActionMove::Create(void)
{
	cActionMove* newAction = new cActionMove;
	return (cActionMove*)newAction->AutoRelease();
}

