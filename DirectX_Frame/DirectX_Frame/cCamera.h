#pragma once
#include "cObject.h"

class cCamera : public cObject
{
private:
	static RECT m_rc;
	//ī�޶� �Ÿ�
	float m_fDistance;

public:
//	virtual void Setup(void) override;
//	virtual void Update(void) override;
//	virtual void Render(void) override;
	
	//ī�޶� ���� ����
//	virtual void SetView(void) final;
	//�Է±⿡ ���� ī�޶� ���� ������ �޾��ִ� �Լ�
//	virtual void SetControl(void);
	//ī�޶� ���� ���⿡�� ��� ����
//	virtual void GetRayDirection(OUT D3DXVECTOR3* vPosition, OUT D3DXVECTOR3* vDirection, POINT& ptPosition);
	//ī�޶� �þ߰� ���� �Լ�
	static void SetFovLH(void);

	//ī�޶� ���� �Լ�
	static cCamera* Create(void);


protected:
	cCamera(void);
	virtual ~cCamera(void);
};

