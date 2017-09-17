#include "stdafx.h"
#include "crtCtl.h"

void cCrtCtrl::Update(iMap * pMap)
{
	D3DXVECTOR3 vPos = m_vPos;

	if (GetKeyState('W') & 0x8000)
	{
		vPos = m_vPos + m_vDir * m_fSpeed;
	}
	if (GetKeyState('S') & 0x8000)
	{
		vPos = m_vPos - m_vDir * m_fSpeed;
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}
	//맵데이터에서 높이 정보를 받아와 높이를 높여준다
	//현재 맵 미구현으로 주석처리
	if (pMap)
	{
		if (pMap->GetHeight(vPos.x, vPos.y, vPos.z))
		{
			m_vPos = vPos;
		}
	}
	else
	{
		m_vPos = vPos;
	}
	m_vPos = vPos;

	m_vDir = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIX matR;
	//각도값 받아와 회전
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

	D3DXMATRIX matT;
	//pos값에 따라 이동
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	//월드 매트릭스 반영
	m_matWorld = matR * matT;


}

D3DXVECTOR3 * cCrtCtrl::GetPosition()
{
	return &m_vPos;
}

cCrtCtrl::cCrtCtrl(void)
	: m_vDir(0, 0, 1)
	, m_vPos(0, 0, 0)
	, m_fSpeed(0.1f)
	, m_fAngle(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCrtCtrl::~cCrtCtrl(void)
{
}
