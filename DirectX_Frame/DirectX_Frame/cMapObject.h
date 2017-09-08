#pragma once
#include "cObject.h"

struct ST_TILE
{
	D3DXVECTOR3 vPosition;
	DWORD dwData;

	ST_TILE(D3DXVECTOR3& _vPosition, DWORD _dwData)
		: vPosition(_vPosition), dwData(_dwData)
	{

	}
};

class cMapObject : public cObject
{
private:
	std::vector<ST_TILE> m_vecTile;
	std::vector<LPD3DXMATERIAL> m_vecTexMtl;

	DWORD m_dwMapSize;
	float m_fMinHeight;
	float m_fMaxHeight;

public:
	virtual HRESULT Setup(void) override;
	void Reset(void);
	virtual void Update(void) override;
	virtual void Render(void) override;

	// ������Ʈ�� ��ӹ��� ��� Ŭ������ �Ʒ��� ���� ������ ����մϴ�. (�����ε��Ͽ� ����ϼ���.)
	static cMapObject* Create(void);		//�޸𸮰����� ������ 
protected:									//��ӹ����� ������ ������ �� �����ϴ�.
	cMapObject(void);						//������ ����
	virtual ~cMapObject(void);			//�Ҹ��� ����
};