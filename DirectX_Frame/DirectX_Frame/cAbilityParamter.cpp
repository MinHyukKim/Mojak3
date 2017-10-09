#include "stdafx.h"
#include "cAbilityParamter.h"

cAbilityParamter::cAbilityParamter(void)
	: m_dwUnitID(0), m_dwPlayerID(0), m_dwAICodeID(0)
	, m_nMinLife(60), m_nMinMana(50), m_nMinStamina(40)
	, m_nMaxLife(69), m_nMaxMana(59), m_nMaxStamina(54)
	, m_nLevel(1), m_nAP(125), m_fMaxEXP(100.0f), m_fEXP(16.0f)
	, m_fMaxAdventureEXP(100.0f), m_fAdventureEXP(0.0f)
	, m_nMinDamage(12), m_nBonusDamage(8), m_nMagicDamage(2)
	, m_nDefence(7), m_nProtecte(1), m_nWoumd(0)
	, m_nMagicDefence(3), m_nMagicProtecte(2)
	, m_fStr(31.0f), m_fInt(23.0f), m_fDex(26.0f), m_fWill(33.0f), m_fLuk(10.0f)
	, m_fInjury(7.0f), m_fBalance(53.0f), m_fPenetration(1.0f), m_fCritical(10.2f)
	, m_fAttackRange(0.5f), m_fFood(0.0f), m_fDownGauge(0.0f), m_fPower(2.25f), m_fMoveSpeed(1.0f)
	, m_fSoundDelay(0.0f), m_fDelayTime(0.0f)

	, m_isHaveSkillSmash(true), m_isHaveSkillCounter(true), m_isHaveSkillDefense(true)
	, m_isHaveSkillDownAttack(true), m_isHaveSkillWindmill(true)
	, m_nSkillLevelCombat(1), m_nSKillLevelCounter(1), m_nSkillLevelDefense(1)
	, m_nSkillLevelSmash(1), m_nSkillLevelWindmill(1), m_nSkillLevelDownAttack(1)
	, m_fMaxSkillExpCombat(100), m_fMaxSKillExpCounter(100), m_fMaxSkillExplDefense(100)
	, m_fMaxSkillExpSmash(100), m_fMaxSkillExpWindmill(100), m_fMaxSkillExpDownAttack(100)
	, m_fMinSkillExpCombat(10), m_fMinSKillExpCounter(20), m_fMinSkillExplDefense(7)
	, m_fMinSkillExpSmash(5), m_fMinSkillExpWindmill(6), m_fMinSkillExpDownAttack(13)
	, m_isDialogOpen(false), m_isQuestTempOn(false)

	, m_nKillCountMax(3), m_nKillCount(0)

	, m_bEffective(true)
{
}

cAbilityParamter::~cAbilityParamter(void)
{
}

void cAbilityParamter::Update(void)
{
	float fElapsedTime = g_pTimeManager->GetElapsedTime();
	if (m_fDelayTime > 0.0f) m_fDelayTime -= fElapsedTime;
	if (m_fSoundDelay > 0.0f) m_fSoundDelay -= fElapsedTime;
	if (m_fDownGauge)
	{
		if (m_fDownGauge > 0.0f) m_fDownGauge -= fElapsedTime;
		else m_fDownGauge = 0.0f;
	}
}
