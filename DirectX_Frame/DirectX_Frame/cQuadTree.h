#pragma once

class cFrustum;
class cQuadTree
{
private:
	//4개의 자식노드
	cQuadTree* m_pChild[4];
	//중앙과 4개의 코너값(center, leftTop, rightTop, leftBottom, RightBottom)
	DWORD m_dwCenter;
	DWORD m_dwCorner[4];

	float m_fRadius;
	bool m_bCulled;

public:
	//퀴드트리를 구축한다.
	bool TreeBuild(std::vector<ST_PNT_VERTEX>* pVertex, DWORD dwUnit = 1);
	//삼각형 갯수와 인덱스 반환
	DWORD GenerateIndex(OUT LPDWORD pIndexBuffer, std::vector<ST_PNT_VERTEX>* pVertex, cFrustum* pFrustum, IN DWORD dwUnit);

	cQuadTree(IN int nX, IN int nY);
	cQuadTree(cQuadTree* pParent);
	virtual ~cQuadTree(void);

private:
	enum LOCATION_STATE
	{
		LOCATION_NULL = -1,
		LOCATION_OUT = 0,
		LOCATION_HALF = 1,
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
	inline bool _SubDivide(DWORD dwUnit);
	//출력가능여부 체크
	inline bool _IsVisible(DWORD dwUnit) { return (dwUnit >= m_dwCorner[cQuadTree::CORNER_RIGHT_TOP] - m_dwCorner[cQuadTree::CORNER_LEFT_TOP]); }
	//출력할 폴리곤의 인덱스 생성
	inline int _GenTriIndex(OUT LPDWORD pIndex, IN DWORD dwTriangles, IN DWORD dwUnit);
	//쿼드트리 메모리 삭제
	inline void _Destroy(void);
//절두체 컬링
	// 충돌체크
	int _IsInFrustum(std::vector<ST_PNT_VERTEX>* pVertex, cFrustum* pFrustum);
	// 컬링
	void _FrustumCull(std::vector<ST_PNT_VERTEX>* pVertex, cFrustum* pFrustum);
};

