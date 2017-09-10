#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera(void)
	: m_eCameraType(cCamera::E_LANDOBJECT)
	, m_fMoveSpeed(5.0f)
	, m_vAxisX(1.0f, 0.0f, 0.0f)
	, m_vAxisY(0.0f, 1.0f, 0.0f)
	, m_vAxisZ(0.0f, 0.0f, 1.0f)
	, m_vPosition(0.0f, 1.0f, -10.0f)
	, m_pParentMatrix(NULL)
{
}

cCamera::~cCamera(void)
{
}

HRESULT cCamera::Setup(void)
{
	this->UpdateViewSpace();
	this->UpdateProjection();

	return D3D_OK;
}

void cCamera::Update(void)
{
	this->UpdateViewSpace();
}

void cCamera::TestController(void)
{
	//조작법 w,a,s,d,shift로 조작함
	//shift 가 눌리면 상, 하 이동
	if (g_pInputManager->IsStayKeyDown(VK_SHIFT))
	{
		//상하 이동
		if (g_pInputManager->IsStayKeyDown('W'))
		{
			this->MovePositionY(g_pTimeManager->GetElapsedTime());
		}
		if (g_pInputManager->IsStayKeyDown('S'))
		{
			this->MovePositionY(-g_pTimeManager->GetElapsedTime());
		}
	}
	else
	{
		//이동
		if (g_pInputManager->IsStayKeyDown('W'))
		{
			this->MovePositionZ(g_pTimeManager->GetElapsedTime());
		}
		if (g_pInputManager->IsStayKeyDown('S'))
		{
			this->MovePositionZ(-g_pTimeManager->GetElapsedTime());
		}
		if (g_pInputManager->IsStayKeyDown('A'))
		{
			this->AxisDirectionY(-g_pTimeManager->GetElapsedTime());
		}
		if (g_pInputManager->IsStayKeyDown('D'))
		{
			this->AxisDirectionY(g_pTimeManager->GetElapsedTime());
		}
	}
}

void cCamera::SetupParentMatrix(IN LPD3DXMATRIX pWorldMatrix)
{
	if (m_pParentMatrix && !pWorldMatrix)
	{
		m_vPosition = m_vPosition + D3DXVECTOR3(m_pParentMatrix->_41, m_pParentMatrix->_42, m_pParentMatrix->_43);
		D3DXVec3Normalize(&m_vAxisX, &(m_vAxisX + D3DXVECTOR3(m_pParentMatrix->_11, m_pParentMatrix->_12, m_pParentMatrix->_13)));
		D3DXVec3Normalize(&m_vAxisY, &(m_vAxisY + D3DXVECTOR3(m_pParentMatrix->_21, m_pParentMatrix->_22, m_pParentMatrix->_23)));
		D3DXVec3Normalize(&m_vAxisZ, &(m_vAxisZ + D3DXVECTOR3(m_pParentMatrix->_31, m_pParentMatrix->_32, m_pParentMatrix->_33)));
	}
	else if (!m_pParentMatrix && pWorldMatrix)
	{
		m_vPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		m_vAxisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vAxisZ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}

	this->SetParentMatrix(pWorldMatrix);
}

void cCamera::MovePositionX(OUT float fUnits)
{
	if (m_pParentMatrix) return;

	m_vPosition += m_vAxisX * (m_fMoveSpeed * fUnits);
}

void cCamera::MovePositionY(OUT float fUnits)
{
	if (m_pParentMatrix) return;

	m_vPosition += m_vAxisY * (m_fMoveSpeed * fUnits);
}

void cCamera::MovePositionZ(OUT float fUnits)
{
	if (m_pParentMatrix)
	{
		m_vPosition.z += (m_fMoveSpeed * fUnits);
	}
	else
	{
		m_vPosition += m_vAxisZ  * (m_fMoveSpeed * fUnits);
	}
}

void cCamera::AxisDirectionX(OUT float fAngle)
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationAxis(&matR, &m_vAxisX, fAngle);
	D3DXVec3TransformCoord(&m_vAxisY, &m_vAxisY, &matR);
	D3DXVec3TransformCoord(&m_vAxisZ, &m_vAxisZ, &matR);
}

void cCamera::AxisDirectionY(OUT float fAngle)
{
	D3DXMATRIXA16 matR;
	switch (m_eCameraType)
	{
	case cCamera::E_LANDOBJECT: D3DXMatrixRotationY(&matR, fAngle); break;
	case cCamera::E_AIRCRAFT: D3DXMatrixRotationAxis(&matR, &m_vAxisY, fAngle); break;
	default: return;
	}
	D3DXVec3TransformCoord(&m_vAxisX, &m_vAxisX, &matR);
	D3DXVec3TransformCoord(&m_vAxisZ, &m_vAxisZ, &matR);
}

void cCamera::AxisDirectionZ(OUT float fAngle)
{
	if (E_AIRCRAFT)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationAxis(&matR, &m_vAxisZ, fAngle);
		D3DXVec3TransformCoord(&m_vAxisX, &m_vAxisX, &matR);
		D3DXVec3TransformCoord(&m_vAxisY, &m_vAxisY, &matR);
	}
}

void cCamera::UpdateViewSpace(void)
{

	if (cCamera::E_LANDOBJECT == m_eCameraType)
	{
		if (m_pParentMatrix)
		{
			//고정 시점
			D3DXVECTOR3 vParentPosition(m_pParentMatrix->_41, m_pParentMatrix->_42, m_pParentMatrix->_43);
			D3DXVECTOR3 vParentAxisY(m_pParentMatrix->_31, m_pParentMatrix->_32, m_pParentMatrix->_33);
			D3DXMatrixLookAtLH(&m_matViewMatrix, &(vParentPosition + m_vPosition), &(vParentAxisY - m_vAxisZ), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		}
		else
		{
			//자유 시점
			D3DXMatrixLookAtLH(&m_matViewMatrix, &m_vPosition, &(m_vPosition + m_vAxisZ), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		}
	}
	else if (cCamera::E_AIRCRAFT == m_eCameraType)
	{
		if (m_pParentMatrix)
		{
			//고정 시점
			D3DXVECTOR3 vParentPosition(m_pParentMatrix->_41, m_pParentMatrix->_42, m_pParentMatrix->_43);
			D3DXVECTOR3 vParentAxisY(m_pParentMatrix->_31, m_pParentMatrix->_32, m_pParentMatrix->_33);
			D3DXMatrixLookAtLH(&m_matViewMatrix, &(vParentPosition + m_vPosition), &(vParentAxisY - m_vAxisZ), &m_vAxisY);
		}
		else
		{
			//자유 시점
			D3DXMatrixLookAtLH(&m_matViewMatrix, &m_vPosition, &(m_vPosition + m_vAxisZ), &m_vAxisY);
		}
	}

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matViewMatrix);
}

void cCamera::UpdateViewSpace(IN const CAMERA_TYPE eCameraType)
{
	m_eCameraType = eCameraType;
	this->UpdateViewSpace();
}

void cCamera::UpdateProjection(IN float fMinZ, IN float fMaxZ, IN float fAngle)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, fAngle, (float)rc.right / (float)rc.bottom, fMinZ, fMaxZ);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

cCamera* cCamera::Create(void)
{
	cCamera* newClass = new cCamera;
	newClass->AddRef();
	return newClass;
}

