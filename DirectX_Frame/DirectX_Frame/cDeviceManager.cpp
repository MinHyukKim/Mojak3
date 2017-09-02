#include "stdafx.h"
#include "cDeviceManager.h"

cDeviceManager::~cDeviceManager(void)
{
}

cDeviceManager::cDeviceManager(void)
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{

}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	SAFE_RELEASE(m_pD3D);
	ULONG ul = m_pD3DDevice->Release();
//	assert(ul == 0 && "삭제되지 않은 COM 객체가 있습니다");
}
