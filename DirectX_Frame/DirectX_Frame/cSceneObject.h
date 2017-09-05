#pragma once
#include "cObject.h"

class cSceneObject : public cObject
{
private:

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void);					//������ ���
	virtual void Update(void) override;
	virtual void Render(void) override;	

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cSceneObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cSceneObject(void);						//������ ����
	virtual ~cSceneObject(void);			//�Ҹ��� ����
};
