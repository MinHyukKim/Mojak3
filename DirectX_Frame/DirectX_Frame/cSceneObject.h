#pragma once
#include "cObject.h"

class cSceneObject : public cObject
{
private:

public:
	virtual HRESULT Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cSceneObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cSceneObject(void);						//������ ����
	virtual ~cSceneObject(void);			//�Ҹ��� ����
};
