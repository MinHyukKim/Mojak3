#pragma once
#include "cObject.h"
class cCamera :
	public cObject
{
private:
	static RECT m_rc;
	//ī�޶� �Ÿ�
	float m_fDistance;

public:
	cCamera();
	~cCamera();
};

