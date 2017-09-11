#pragma once
#include "cUiObject.h"

class cUIImageView : public cUiObject
{
private:
	std::string m_sTexture;

public:
	virtual void SetTexture(std::string sFullPath);
	virtual void Render(LPD3DXSPRITE pSprite) override;


	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cUIImageView* Create(void);		//메모리관리용 생성자 
protected:
	cUIImageView(void);
	virtual ~cUIImageView(void);
};