#include "stdafx.h"
#include "cAbilityParamter.h"


cAbilityParamter::cAbilityParamter(void)
	: nMinLife(0) , nMinMana(0) , nMinStamina(0)
	, nMaxLife(0) , nMaxMana(0) , nMaxStamina(0)
	, nMinDamage(0), nBonusDamage(0), nMagicDamage(0)
	, nDefence(0), nProtecte(0), nWoumd(0)
	, nMagicDefence(0) , nMagicProtecte(0)
	,fStr(0.0f) ,fInt(0.0f) ,fDex(0.0f) ,fWill(0.0f) ,fLuk(0.0f)
	,fInjury(0.0f) ,fBalance(0.0f) ,fPenetration(0.0f)
	,fFood(0.0f) ,fDownGauge(0.0f)
{
}


cAbilityParamter::~cAbilityParamter(void)
{
}
