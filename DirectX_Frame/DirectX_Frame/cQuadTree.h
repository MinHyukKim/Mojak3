#pragma once
class cQuadTree
{
private:
	//4개의 자식노드
	cQuadTree* m_pChild[4];
	//중앙과 4개의 코너값(center, leftTop, rightTop, leftBottom, RightBottom)
	DWORD m_dwCenter;
	DWORD m_dwCorner[4];

public:
	//퀴드트리를 구축한다. (박멸아님)
	bool TreeBuild(void);
	//삼각형 갯수와 인덱스 반환
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

	//자식노드를 추가한다, 4개의 코너값(인덱스)을 설정한다.
	inline cQuadTree* _AddChild(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB);
	//자신의 코너값(인덱스)을 재설정한다.
	inline bool _SetCorners(IN int nCornerLT, IN int nCornerRT, IN int nCornerLB, IN int nCornerRB);
	//쿼드트리 분활
	inline bool _SubDivide(void);
	//출력가능여부 체크
	inline bool _IsVisible(void) { return (1 >= m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] - m_dwCorner[cQuadTree::CORNER_LEFT_TOP]); }
	//출력할 폴리곤의 인덱스 생성
	inline int _GenTriIndex(OUT LPDWORD pIndex, IN DWORD dwTriangles);
	//쿼드트리 메모리 삭제
	inline void _Destroy(void);
//절두체 컬링
	// 충돌체크
	int _IsInFrustum();

};

