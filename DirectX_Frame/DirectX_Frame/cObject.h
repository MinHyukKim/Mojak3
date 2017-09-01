#pragma once

class cObject
{
private:
	int m_nReferenceCount;

public:
// ���� ���۷������� ��ȯ�մϴ�. (�ڽ��� �����ϰ� �ִ� Ƚ���� �����մϴ�.)
	virtual int GetReferenceCount(void) final { return m_nReferenceCount; }

// Release()�� �����ε��� �Լ��ȿ��� �� �Լ��� ȣ���� �ּ���.
	virtual void Release(void) final;		// Delete ��� ���

// �� �Լ��� �����ε� �Ͻ� �� �����ϴ�. (���丱����Ǯ ����Ʈ�� this�� �߰��մϴ�.)	
	virtual cObject* AutoRelease(void) final;


// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cObject* Create(void);		// *�ܺ� ������
// �� �Լ��� ȣ���� �ݵ�� Release ���ּ���.
	virtual cObject* AddRef(void);
protected:							// ��ӹ����� ������ ������ �� �����ϴ�.
	cObject(void);					//������ ����
	virtual ~cObject(void);			//�Ҹ��� ����
};

