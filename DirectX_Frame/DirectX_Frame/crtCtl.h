#pragma once

class iMap;

class cCrtCtrl
{
private:
	//방향
	D3DXVECTOR3 m_vDir;
	//위치
	D3DXVECTOR3 m_vPos;
	//속도
	float		m_fSpeed;
	//각도
	float		m_fAngle;
	int			m_nSize;

protected:
	//월드 매트릭스
	D3DXMATRIX	m_matWorld;

public:
	void SetWorldTM(D3DXMATRIX value) { m_matWorld = value; };
	D3DXMATRIX GetWorldTM() {return m_matWorld;	};
	
	void Update(iMap* pMap = NULL);

	D3DXVECTOR3* GetPosition();

	cCrtCtrl(void);
	~cCrtCtrl(void);
};
