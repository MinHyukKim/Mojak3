#include "stdafx.h"
#include "cPlayer.h"

#include "cSkinnedMesh.h"

cPlayer::cPlayer(void)
	: m_pMesh(nullptr)
{
}

cPlayer::~cPlayer(void)
{
}

HRESULT cPlayer::Setup(void)
{
	return S_OK;
}

void cPlayer::Update(void)
{
}

void cPlayer::Render(void)
{
}

cPlayer* cPlayer::Create(void)
{
	cPlayer* newClass = new cPlayer;
	newClass->AddRef();
	return newClass;
}

