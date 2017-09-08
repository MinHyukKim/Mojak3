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

	// 오브젝트를 상속받은 모든 클래스는 아래와 같은 형식을 사용합니다. (오버로딩하여 사용하세요.)
	static cMapObject* Create(void);		//메모리관리용 생성자 
protected:									//상속받을수 있지만 생성할 수 없습니다.
	cMapObject(void);						//생성자 은닉
	virtual ~cMapObject(void);			//소멸자 은닉
};