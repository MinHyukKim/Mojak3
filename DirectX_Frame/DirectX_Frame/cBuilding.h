/*���� ���� �ҷ��� �����ϴ� Ŭ����*/
#pragma once

class cBuilding : public cObject
{
private:
	//������ ��ġ�� ȸ�� ��
	D3DXMATRIXA16 m_matWorld;


public:
	virtual HRESULT Setup(void) override;
	LPD3DXMESH LoadModel(const char * filename);
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	//��ǥ �Լ�
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
	void SetPosition(LPD3DXVECTOR3 pPosition) { memcpy(&m_matWorld._41, pPosition, sizeof(D3DXVECTOR3)); }
	void SetPosX(float fX) { m_matWorld._41 = fX; }
	void SetPosY(float fY) { m_matWorld._42 = fY; }
	void SetPosZ(float fZ) { m_matWorld._43 = fZ; }
	float GetPosX(void) { return m_matWorld._41; }
	float GetPosY(void) { return m_matWorld._42; }
	float GetPosZ(void) { return m_matWorld._43; }

	static cBuilding* Create(void);

protected:
	cBuilding(void);
	virtual ~cBuilding(void);

};