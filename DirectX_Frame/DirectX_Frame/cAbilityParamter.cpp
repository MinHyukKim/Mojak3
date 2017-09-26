#include "stdafx.h"
#include "cAbilityParamter.h"

cAbilityParamter::cAbilityParamter(void)
	: m_dwUnitID(0), m_dwPlayerID(0), m_dwAICodeID(0)
	, m_nMinLife(60), m_nMinMana(50), m_nMinStamina(49)
	, m_nMaxLife(69), m_nMaxMana(59), m_nMaxStamina(54)
	, m_nLevel(1), m_nAP(0), m_fMaxEXP(100.0f), m_fEXP(0.0f)
	, m_fMaxAdventureEXP(100.0f), m_fAdventureEXP(0.0f)
	, m_nMinDamage(12), m_nBonusDamage(0), m_nMagicDamage(2)
	, m_nDefence(9), m_nProtecte(1), m_nWoumd(0)
	, m_nMagicDefence(3) , m_nMagicProtecte(2)
	, m_fStr(31.0f) , m_fInt(23.0f) , m_fDex(26.0f) , m_fWill(33.0f) , m_fLuk(10.0f)
	, m_fInjury(1.0f) , m_fBalance(53.0f) , m_fPenetration(1.0f) , m_fCritical(17.2f)
	, m_fRange(1.0f), m_fFood(0.0f) , m_fDownGauge(0.0f) , m_fMoveSpeed(1.0f)
	, m_fDelayTime(0.0f)
	, m_bEffective(true)
{
}

cAbilityParamter::~cAbilityParamter(void)
{
}

void cAbilityParamter::Update(void)
{
	if (m_fDelayTime > 0.0f) m_fDelayTime -= g_pTimeManager->GetElapsedTime();
}
