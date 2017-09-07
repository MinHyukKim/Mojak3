#pragma once
#include "cObject.h"

class cMapObject : public cObject
{
private:

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void);					//������ ���
	virtual void Update(void) override;
	virtual void Render(void) override;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);			//�Ҹ��� ����
};