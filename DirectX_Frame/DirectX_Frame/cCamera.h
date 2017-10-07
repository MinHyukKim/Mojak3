#pragma once
#include "cObject.h"

//��å 275p ����
class cCamera : public cObject
{
public:
	enum CAMERA_TYPE
	{
		E_LANDOBJECT,
		E_AIRCRAFT,
	};

private:
	CAMERA_TYPE m_eCameraType;
	float m_fMoveSpeed;

	D3DXVECTOR3 m_vAxisX;
	D3DXVECTOR3 m_vAxisY;
	D3DXVECTOR3 m_vAxisZ;
	D3DXVECTOR3 m_vPosition;

	D3DXMATRIXA16 m_matViewMatrix;

	LPD3DXMATRIX m_pParentMatrix;

public:
	virtual HRESULT Setup(void);
	virtual void Update(void);

	void TestController(void);
	void MouseController(void);
	void WheelController(void);

	//�θ� ��Ʈ���� ����
	void SetupParentMatrix(IN LPD3DXMATRIX pWorldMatrix);
	void SetParentMatrix(IN LPD3DXMATRIX pWorldMatrix) { m_pParentMatrix = pWorldMatrix; }
	LPD3DXMATRIX GetParentMatrix(void) { return m_pParentMatrix; }
	void SetPosition(IN LPD3DXVECTOR3 pPosition) { m_vPosition = *pPosition; }

	//��� �̵�
	void MovePositionX(OUT float fUnits);						// ��/�� �̵�
	void MovePositionY(OUT float fUnits);						// ��/�� �̵�
	void MovePositionZ(OUT float fUnits);						// ��/�� �̵�

	//��� ȸ��
	void AxisDirectionX(OUT float fAngle);						// ��/�� ȸ��
	void AxisDirectionY(OUT float fAngle);						// ��/�� ȸ��
	void AxisDirectionZ(OUT float fAngle);						// ���� ȸ��

	void SetCameraType(IN CAMERA_TYPE eCameraType) { m_eCameraType = eCameraType; }
	LPD3DXMATRIX GetViewMatrix(void) { return &m_matViewMatrix; }

	LPD3DXVECTOR3 GetPosition(void) { return &m_vPosition; }
	LPD3DXVECTOR3 GetAxisX(void) { return &m_vAxisX; }
	LPD3DXVECTOR3 GetAxisY(void) { return &m_vAxisY; }
	LPD3DXVECTOR3 GetAxisZ(void) { return &m_vAxisZ; }

	void UpdateViewSpace(IN const CAMERA_TYPE eCameraType);
	void UpdateViewSpace(void);

	static void UpdateProjection(IN float fMinZ = 1.0f, IN float fMaxZ = 1000.0f, IN float fAngle = D3DX_PI / 4.0f);
	
	//ī�޶� ���� �Լ�
	static cCamera* Create(void);
protected:
	cCamera(void);
	virtual ~cCamera(void);
};

