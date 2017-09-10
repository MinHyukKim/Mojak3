#pragma once
class cQuadTree
{
private:
	//4���� �ڽĳ��
	cQuadTree* m_pChild[4];
	//�߾Ӱ� 4���� �ڳʰ�(center, leftTop, rightTop, leftBottom, RightBottom)
	int m_nCenter;
	int m_nCorner[4];

public:
	//����Ʈ���� �����Ѵ�. (�ڸ�ƴ�)
	bool TreeBuild(void);

	cQuadTree(int nX, int nY);
	cQuadTree(cQuadTree* pParent);
	~cQuadTree(void);

private:
	enum E_CORNER
	{
		E_LEFT_TOP,
		E_RIGHT_TOP,
		E_LEFT_BOTTOM,
		E_RIGHT_BOTTOM,
	};

	//�ڽĳ�带 �߰��Ѵ�, 4���� �ڳʰ�(�ε���)�� �����Ѵ�.
	inline cQuadTree* _AddChild(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB);
	//�ڽ��� �ڳʰ�(�ε���)�� �缳���Ѵ�.
	inline bool _SetCorners(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB);
	//����Ʈ�� ��Ȱ
	inline bool _SubDivide(void);
	//��°��ɿ��� üũ
	inline bool _IsVisible(void) { return (m_nCorner[E_RIGHT_TOP] - m_nCorner[E_LEFT_TOP] <= 1); }
	//����� �������� �ε��� ����
	inline int _GetTriIndex(int nTriangles, LPVOID pIndex);
	//����Ʈ�� �޸� ����
	inline void _Destroy(void);
};

