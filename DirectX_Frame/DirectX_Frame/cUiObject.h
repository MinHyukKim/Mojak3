#pragma once
#include "cObject.h"

class cUiObject : public cObject
{
private:

public:
	virtual HRESULT Setup(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cUiObject* Create(void);		//�޸𸮰����� ������ 
protected:
	cUiObject(void);
	virtual ~cUiObject(void);
};