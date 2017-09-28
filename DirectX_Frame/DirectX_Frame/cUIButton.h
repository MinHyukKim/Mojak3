#pragma once
#include "cUiObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) {};
	virtual void OnMouseOver(cUIButton* pSender) {};
};

class cUIButton : public cUiObject
{
private:


protected:

	enum eButtonStatus
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATUS_COUNT,
	};

	eButtonStatus m_eButtonStatus;
	std::string m_aTexture[E_STATUS_COUNT];
	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);

public:

	//enum eButtonStatus
	//{
	//	E_NORMAL,
	//	E_MOUSEOVER,
	//	E_SELECTED,
	//	E_STATUS_COUNT,
	//};
	//eButtonStatus m_eButtonStatus;
	//std::string m_aTexture[E_STATUS_COUNT];
	
	enum eIfItemKinds
	{
		E_ITEM_NONE, 
		E_ITEM_WEAR,
		E_ITEM_SHOES,
		E_ITEM_WEAPON,
		E_ITEM_END
	};

	enum eItemAbility
	{
		E_ITEM_STATS_NONE,
		E_ITEM_STATS_WEAR_NONE,
		E_ITEM_STATS_WEAR_01,
		E_ITEM_STATS_WEAR_02,
		E_ITEM_STATS_WEAR_03,
		E_ITEM_STATS_SHOES_NONE,
		E_ITEM_STATS_SHOES_01,
		E_ITEM_STATS_WEAPON_NONE,
		E_ITEM_STATS_WEAPON_01,
		E_ITEM_STATS_END
	};

	virtual void SetTexture(std::string sNor, std::string sOvr, std::string sSel);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;

//	eButtonStatus GetButtonStatus(void) { return m_eButtonStatus; }


	D3DXIMAGE_INFO stImageInfo;
	RECT rc;
	bool isOver;
	bool isClick;
	eIfItemKinds m_eItem;
	eItemAbility m_eItemStats;
	D3DXVECTOR3 m_vItemPrevPos;

	int m_Alpha;
	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUIButton* Create(void);		//메모리관리용 생성자 
protected:
	cUIButton(void);
	virtual ~cUIButton(void);
};