#include "stdafx.h"
#include "cAbilityParamter.h"

cAbilityParamter::cAbilityParamter(void)
	: m_dwUnitID(0) , m_dwPlayerID(0), m_dwAICodeID(0)
	, m_nMinLife(68) , m_nMinMana(58) , m_nMinStamina(52)
	, m_nMaxLife(69) , m_nMaxMana(59) , m_nMaxStamina(54)
	, m_nMinDamage(0), m_nBonusDamage(0), m_nMagicDamage(0)
	, m_nDefence(0), m_nProtecte(0), m_nWoumd(0)
	, m_nMagicDefence(0) , m_nMagicProtecte(0)
	, m_fStr(31.0f) , m_fInt(23.0f) , m_fDex(26.0f) , m_fWill(33.0f) , m_fLuk(10.0f)
	, m_fInjury(0.0f) , m_fBalance(0.0f) , m_fPenetration(0.0f)
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
