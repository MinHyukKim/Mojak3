#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer(void)
{
	//������ ���ÿ� ����
	this->Setup();
}

cTimer::~cTimer(void)
{
}

void cTimer::Setup(void)
{
	//������ ����
	this->SetLockFPS();
}

void cTimer::Update(void)
{
}

float cTimer::GetWorldCheck(void)
{
	return 0.0f;
}
