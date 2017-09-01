#pragma once
#define g_pRelasePool cReleasePool::GetInstance()

class cAutoReleasePool
{
private:
//	std::set<cObject*> m_setNode;

public:
	cAutoReleasePool(void);
	virtual ~cAutoReleasePool(void);
};

