#pragma once
#include "cObject.h"

class cSkybox : public cObject
{
	cSkybox(const char* top, 
		const char* bottom,
		const char* left,
		const char* right, 
		const char* front,
		const char* back);


	virtual HRESULT Setup(void);
	virtual void Update(void);

	//스카이박스 생성 함수
	static cSkybox* Create(void);
protected:
	cSkybox(void);
	virtual ~cSkybox(void);
};
