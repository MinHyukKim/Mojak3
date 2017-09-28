#pragma once

enum eItemStat
{
	ITEM_NONE,
	ITEM_WEAR_01,
	ITEM_WEAR_02,
	ITEM_WEAR_03,
	ITEM_WEAPON_01,
	ITEM_END
};

class cItemTemp
{
private:

public:

	static cItemTemp* Create(void);
protected:
	cItemTemp(void);
	virtual ~cItemTemp(void);

};