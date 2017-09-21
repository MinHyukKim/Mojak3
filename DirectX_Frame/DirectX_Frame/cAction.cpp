#include "stdafx.h"
#include "cAction.h"
#include "cTimer.h"

cAction::cAction(void)
	: m_fElapsedTime(0.0f)
	, m_fActionTime(0.0)
	, m_pObjectTarget(NULL)
	, m_pDelegate(NULL)
{
}

cAction::~cAction(void)
{
}

void cAction::Play(void)
{
	m_fElapsedTime = 0.0f;
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

