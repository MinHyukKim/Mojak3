#pragma once
class cQuadTree
{
private:
	//4개의 자식노드
	cQuadTree* m_pChild[4];
	//중앙과 4개의 코너값(center, leftTop, rightTop, leftBottom, RightBottom)
	int m_nCenter;
	int m_nCorner[4];

public:
	//퀴드트리를 구축한다. (박멸아님)
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

	//자식노드를 추가한다, 4개의 코너값(인덱스)을 설정한다.
	inline cQuadTree* _AddChild(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB);
	//자신의 코너값(인덱스)을 재설정한다.
	inline bool _SetCorners(int nCornerLT, int nCornerRT, int nCornerLB, int nCornerRB);
	//쿼드트리 분활
	inline bool _SubDivide(void);
	//출력가능여부 체크
	inline bool _IsVisible(void) { return (m_nCorner[E_RIGHT_TOP] - m_nCorner[E_LEFT_TOP] <= 1); }
	//출력할 폴리곤의 인덱스 생성
	inline int _GetTriIndex(int nTriangles, LPVOID pIndex);
	//쿼드트리 메모리 삭제
	inline void _Destroy(void);
};

