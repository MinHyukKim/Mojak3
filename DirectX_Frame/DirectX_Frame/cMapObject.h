#pragma once
#include "cObject.h"

class cMapObject : public cObject
{
private:

public:


	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);			//�Ҹ��� ����
};