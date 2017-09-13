#pragma once

class iMap;

class cCrtCtrl
{
private:
	//����
	D3DXVECTOR3 m_vDir;
	//��ġ
	D3DXVECTOR3 m_vPos;
	//�ӵ�
	float		m_fSpeed;
	//����
	float		m_fAngle;
	int			m_nSize;

protected:
	//���� ��Ʈ����
	D3DXMATRIX	m_matWorld;

public:
	void SetWorldTM(D3DXMATRIX value) { m_matWorld = value; };
	D3DXMATRIX GetWorldTM() {return m_matWorld;	};
	
	void Update(iMap* pMap = NULL);

	D3DXVECTOR3* GetPosition();

	cCrtCtrl(void);
	~cCrtCtrl(void);
};
