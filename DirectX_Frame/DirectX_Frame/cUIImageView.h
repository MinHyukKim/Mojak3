#pragma once
#include "cUiObject.h"

class cUIImageView : public cUiObject
{
private:
	std::string m_sTexture;

public:
	virtual void SetTexture(std::string sFullPath);
	virtual void Render(LPD3DXSPRITE pSprite) override;
	D3DXIMAGE_INFO stImageInfo;
	int m_Alpha;
	RECT rc;
	RECT m_conRECT;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUIImageView* Create(void);		//�޸𸮰����� ������ 
protected:
	cUIImageView(void);
	virtual ~cUIImageView(void);
};