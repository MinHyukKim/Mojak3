#pragma once
#include "cObject.h"

class cCamera :
	public cObject
{
private:
	static RECT m_rc;
	//카메라 거리
	float m_fDistance;

public:

protected:
	cCamera(void);
	virtual ~cCamera(void);
};

