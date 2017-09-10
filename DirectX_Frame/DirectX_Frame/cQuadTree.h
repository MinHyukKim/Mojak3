#pragma once
class cQuadTree
{
private:
	//4���� �ڽĳ��
	cQuadTree* m_pChild[4];
	//�߾Ӱ� 4���� �ڳʰ�(center, leftTop, rightTop, leftBottom, RightBottom)
	DWORD m_dwCenter;
	DWORD m_dwCorner[4];

public:
	//����Ʈ���� �����Ѵ�. (�ڸ�ƴ�)
	bool TreeBuild(void);
	//�ﰢ�� ������ �ε��� ��ȯ
	int GenerateIndex(OUT LPDWORD pIndexBuffer);

	cQuadTree(IN int nX, IN int nY);
	cQuadTree(cQuadTree* pParent);
	~cQuadTree(void);

private:
	enum LOCATION_STATE
	{
		LOCATION_NULL = -1,
		LOCATION_OUT = 1,
		LOCATION_HALF = 2,
		LOCATION_IN = 2,
	};
	enum CORNER_LOCATION
	{
		CORNER_LEFT_TOP,
		CORNER_RIGHT_TOP,
		CORNER_LEFT_BOTTOM,
		CORNER_RIGHT_BOTTOM,
	};

	//�ڽĳ�带 �߰��Ѵ�, 4���� �ڳʰ�(�ε���)�� �����Ѵ�.
	inline cQuadTree* _AddChild(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB);
	//�ڽ��� �ڳʰ�(�ε���)�� �缳���Ѵ�.
	inline bool _SetCorners(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB);
	//����Ʈ�� ��Ȱ
	inline bool _SubDivide(void);
	//��°��ɿ��� üũ
	inline bool _IsVisible(void) { return (1 >= m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] - m_dwCorner[cQuadTree::CORNER_LEFT_TOP]); }
	//����� �������� �ε��� ����
	inline int _GenTriIndex(OUT LPDWORD pIndex, IN DWORD dwTriangles);
	//����Ʈ�� �޸� ����
	inline void _Destroy(void);
//����ü �ø�
	// �浹üũ
	int _IsInFrustum();

};

