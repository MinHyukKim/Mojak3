#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer(void)
{
}

cTimer::~cTimer(void)
{
}

void cTimer::Setup(void)
{
	//프레임 해제
	this->SetLockFPS();
}

void cTimer::Update(void)
{
}

float cTimer::GetWorldCheck(void)
{
	return 0.0f;
}
