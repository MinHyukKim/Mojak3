#include "stdafx.h"
#include "cObjectManager.h"

#include "cPlayer.h"

cObjectManager::cObjectManager(void)
	: m_pPlayer(nullptr)
{
}

cObjectManager::~cObjectManager(void)
{
}

void cObjectManager::RegisterPlayer(cPlayer* pPlayer)
{
	SAFE_RELEASE(m_pPlayer);
	m_pPlayer = pPlayer;
	m_pPlayer->AddRef();
}

void cObjectManager::SavePlayerData(LPCSTR FullPath)
{
	assert(false && "미구현");
}

void cObjectManager::LoadPlayerData(LPCSTR FullPath)
{
	assert(false && "미구현");
}

void cObjectManager::Destroy(void)
{
	SAFE_RELEASE(m_pPlayer);
}

