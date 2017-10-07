#pragma once
#include "cObject.h"

//용책 275p 참고
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

	//부모 매트릭스 설정
	void SetupParentMatrix(IN LPD3DXMATRIX pWorldMatrix);
	void SetParentMatrix(IN LPD3DXMATRIX pWorldMatrix) { m_pParentMatrix = pWorldMatrix; }
	LPD3DXMATRIX GetParentMatrix(void) { return m_pParentMatrix; }
	void SetPosition(IN LPD3DXVECTOR3 pPosition) { m_vPosition = *pPosition; }

	//상대 이동
	void MovePositionX(OUT float fUnits);						// 좌/우 이동
	void MovePositionY(OUT float fUnits);						// 상/하 이동
	void MovePositionZ(OUT float fUnits);						// 앞/뒤 이동

	//상대 회전
	void AxisDirectionX(OUT float fAngle);						// 상/하 회전
	void AxisDirectionY(OUT float fAngle);						// 좌/우 회전
	void AxisDirectionZ(OUT float fAngle);						// 뱅기용 회전

	void SetCameraType(IN CAMERA_TYPE eCameraType) { m_eCameraType = eCameraType; }
	LPD3DXMATRIX GetViewMatrix(void) { return &m_matViewMatrix; }

	LPD3DXVECTOR3 GetPosition(void) { return &m_vPosition; }
	LPD3DXVECTOR3 GetAxisX(void) { return &m_vAxisX; }
	LPD3DXVECTOR3 GetAxisY(void) { return &m_vAxisY; }
	LPD3DXVECTOR3 GetAxisZ(void) { return &m_vAxisZ; }

	void UpdateViewSpace(IN const CAMERA_TYPE eCameraType);
	void UpdateViewSpace(void);

	static void UpdateProjection(IN float fMinZ = 1.0f, IN float fMaxZ = 1000.0f, IN float fAngle = D3DX_PI / 4.0f);
	
	//카메라 생성 함수
	static cCamera* Create(void);
protected:
	cCamera(void);
	virtual ~cCamera(void);
};

