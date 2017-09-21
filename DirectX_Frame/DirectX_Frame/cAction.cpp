#include "stdafx.h"
#include "cAction.h"
#include "cTimer.h"

cAction::cAction(void)
	: m_fElapsedTime(0.0f)
	, m_fActionTime(0.0)
	, m_pTarget(nullptr)
	, m_pDelegate(nullptr)
{
}

cAction::~cAction(void)
{
}

void cAction::Play(void)
{
	m_fElapsedTime = 0.0f;
}

void cAction::Stop(void)
{
	this->SetMoveTo();
}

void cAction::Update(void)
{
	this->SetElapsedTime(this->GetElapseTime() + g_pTimeManager->GetElapsedTime());
}


cAction* cAction::Create(void)
{
	cAction* newAction = new cAction;
	newAction->AddRef();
	return newAction;
}

