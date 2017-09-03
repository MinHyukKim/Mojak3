#pragma once
#include "cObject.h"

class cCamera : public cObject
{
private:
	static RECT m_rc;
	//카메라 거리
	float m_fDistance;

public:
//	virtual void Setup(void) override;
//	virtual void Update(void) override;
//	virtual void Render(void) override;
	
	//카메라 시점 설정
//	virtual void SetView(void) final;
	//입력기에 의한 카메라 시점 변경을 받아주는 함수
//	virtual void SetControl(void);
	//카메라가 보는 방향에서 쏘는 광선
//	virtual void GetRayDirection(OUT D3DXVECTOR3* vPosition, OUT D3DXVECTOR3* vDirection, POINT& ptPosition);
	//카메라 시야각 설정 함수
	static void SetFovLH(void);

	//카메라 생성 함수
	static cCamera* Create(void);


protected:
	cCamera(void);
	virtual ~cCamera(void);
};

