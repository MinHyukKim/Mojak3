#include "stdafx.h"
#include "cMapTerrain.h"

#include "cQuadTree.h"
#include "cFrustum.h"

cMapTerrain::cMapTerrain(void)
	: m_pVertexBuffer(nullptr)
	, m_pIndexBufer(nullptr)
	, m_pQuadTree(nullptr)
	, m_vScale(1.0f, 10.0f, 1.0f)
	, m_fMaxTerrainX(0.0f)
	, m_fMaxTerrainZ(0.0f)
	, m_dwCol(0)
	, m_dwRow(0)
	, m_dwTriangles(0)
	, m_dwIndexBuffer(0) // 임시 버퍼용
{
}

cMapTerrain::~cMapTerrain(void)
{
	this->_Destroy();
}


HRESULT cMapTerrain::Setup(IN LPCSTR szHeightMapName, IN D3DXMATERIAL* pMaterial, IN LPD3DXVECTOR3 pScale)
{
	this->m_vScale = *pScale;
	this->_BuildHeightMap(szHeightMapName);
	this->_LoadTexture(pMaterial);
	this->_CreateVertexBuffer();
	this->_CreateIndexBuffer();
//	SAFE_DELETE(m_pQuadTree);
//	m_pQuadTree = new cQuadTree(m_dwCol, m_dwRow);
//	this->_BuilldQuadTree();

	return S_OK;
}

void cMapTerrain::Update(void)
{
//	if (!g_pInputManager->IsStayKeyDown(VK_SPACE))
//	{
//		LPDWORD pIndex;
//		if (FAILED(m_pIndexBufer->Lock(0, (m_dwCol - 1) * (m_dwRow - 1) * 6 * sizeof(DWORD), (LPVOID*)&pIndex, 0))) return;
//		m_dwTriangles = m_pQuadTree->GenerateIndex(pIndex, &m_vecPosition, g_pFrustum);
//		m_pIndexBufer->Unlock();
//	}
}

void cMapTerrain::Render(void)
{
	this->_Draw();
}

bool cMapTerrain::GetHeight(OUT float* fY, IN float fX, IN float fZ)
{
	const float fColHalf = m_fMaxTerrainX / 2.0f;
	const float fRowHalf = m_fMaxTerrainZ / 2.0f;
	if (fX < -fColHalf || -fZ < -fRowHalf || fX > fColHalf || -fZ > fRowHalf) return false;

	if (fY)
	{
		DWORD dwX = (DWORD)(fX + fColHalf);
		DWORD dwZ = (DWORD)(fRowHalf - fZ);

		float fDeltaX = (fX + fColHalf) - (float)dwX;
		float fDeltaZ = (fRowHalf - fZ) - (float)dwZ;

		DWORD _dw0 = ((dwX + 0) + (dwZ + 0) * m_dwCol);
		DWORD _dw1 = ((dwX + 1) + (dwZ + 0) * m_dwCol);
		DWORD _dw2 = ((dwX + 0) + (dwZ + 1) * m_dwCol);
		DWORD _dw3 = ((dwX + 1) + (dwZ + 1) * m_dwCol);

		if (1.0f > (fDeltaX + fDeltaZ))
		{
			D3DXVECTOR3 _v01 = m_vecPosition[_dw1].p - m_vecPosition[_dw0].p;
			D3DXVECTOR3 _v02 = m_vecPosition[_dw2].p - m_vecPosition[_dw0].p;
			(*fY) = (_v01 * fDeltaX + _v02 * fDeltaZ + m_vecPosition[_dw0].p).y;
		}
		else
		{
			D3DXVECTOR3 _32 = m_vecPosition[_dw2].p - m_vecPosition[_dw3].p;
			D3DXVECTOR3 _31 = m_vecPosition[_dw1].p - m_vecPosition[_dw3].p;
			fDeltaX = 1.0f - fDeltaX;
			fDeltaZ = 1.0f - fDeltaZ;
			(*fY) = (_32 * fDeltaX + _31 * fDeltaZ + m_vecPosition[_dw3].p).y;
		}
	}
	return true;
}


bool cMapTerrain::IsCollision(OUT LPD3DXVECTOR3 pPos, IN LPD3DXVECTOR3 pOrg, IN LPD3DXVECTOR3 pDir)
{
	float fDist = 1000.0f;
	bool bCheck = false;

	for (DWORD i = 0; i < m_vecIndex.size(); i+=3)
	{
		D3DXVECTOR3 vPos1 = m_vecPosition[m_vecIndex[i + 0]].p;
		D3DXVECTOR3 vPos2 = m_vecPosition[m_vecIndex[i + 1]].p;
		D3DXVECTOR3 vPos3 = m_vecPosition[m_vecIndex[i + 2]].p;

		float fTemp = 0.0f;

		if (D3DXIntersectTri(&vPos1, &vPos2, &vPos3,
			pOrg, pDir, nullptr, nullptr, &fTemp))
		{
			if (fDist > fTemp) fDist = fTemp;

			bCheck = true;
		}
	}
	if (bCheck) (*pPos) = (*pOrg) + (*pDir) * fDist;
	return bCheck;
}

cMapTerrain* cMapTerrain::Create(void)
{
	cMapTerrain* newClass = new cMapTerrain;
	newClass->AddRef();
	return newClass;
}


inline HRESULT cMapTerrain::_Destroy(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBufer);


	return S_OK;
}
inline HRESULT cMapTerrain::_LoadTexture(D3DXMATERIAL* pMaterial)
{
	m_vecMaterals.push_back(*pMaterial);
	m_vecTextures.push_back(g_pTexture->GetTexture(pMaterial->pTextureFilename));

	return S_OK;
}

inline HRESULT cMapTerrain::_BuildHeightMap(LPCSTR szMapName)
{
	ST_HEIGHT_MAP* pHeightMap = g_pTexture->GetHeightMap(szMapName);
	if (!pHeightMap) return E_FAIL;

	//바닥 높이정보 (surfaceInfo);
	DWORD dwNumVertex = pHeightMap->dwSize / pHeightMap->dwByte;
	m_dwRow = sqrt(dwNumVertex + FLT_EPSILON);
	if (dwNumVertex != m_dwRow * m_dwRow)
	{
		assert(false && "정사각형태의 RAW파일만 사용 가능합니다.");
		return E_FAIL;
	}
	m_dwCol = m_dwRow;

	//버텍스 배열 생성
	m_vecPosition.clear();
	m_vecPosition.resize(dwNumVertex);

	//버텍스 좌표 계산
	m_fMaxTerrainX = (float)(m_dwCol - 1) * m_vScale.x;
	m_fMaxTerrainZ = (float)(m_dwRow - 1) * m_vScale.z;
	const float fColHalf = m_fMaxTerrainX / 2.0f;
	const float fRowHalf = m_fMaxTerrainZ / 2.0f;
	const float fHighHalf = (float)m_vScale.y / 2.0f;
	const float fScaleY = m_vScale.y / 255.0f;
	DWORD dwNumIndex = 0;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			m_vecPosition[dwNumIndex].p.x = (float)x * m_vScale.x - fColHalf;
			m_vecPosition[dwNumIndex].p.y = pHeightMap->pBytes[dwNumIndex] * fScaleY - fHighHalf;
			m_vecPosition[dwNumIndex].p.z = fRowHalf - (float)z * m_vScale.z;

			m_vecPosition[dwNumIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			m_vecPosition[dwNumIndex].t = D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1));

			++dwNumIndex;
		}
	}

	//노말값 계산
	for (DWORD z = 1; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 1; x < (m_dwCol - 1); x++)
		{
			//인덱스
			DWORD dwNumIndex = x + z * m_dwCol;

			//노말값
			D3DXVec3Cross(&m_vecPosition[dwNumIndex].n,
				&(m_vecPosition[dwNumIndex - 1].p - m_vecPosition[dwNumIndex + 1].p),
				&(m_vecPosition[dwNumIndex - m_dwCol].p - m_vecPosition[dwNumIndex + m_dwCol].p));
			D3DXVec3Normalize(&m_vecPosition[dwNumIndex].n, &m_vecPosition[dwNumIndex].n);
		}
	}

	return S_OK;
}

inline HRESULT cMapTerrain::_BuildHeightMap(DWORD dwCol, DWORD dwRow)
{
	SAFE_RELEASE(m_pVertexBuffer);

	//바닥 높이정보 (surfaceInfo);
	m_dwCol = dwCol;
	m_dwRow = dwRow;

	//버텍스 생성
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX),
		0, ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL))) return E_FAIL;

	//버텍스 좌표 계산
	const float fColHalf = (float)m_dwCol * m_vScale.x / 2.0f;
	const float fRowHalf = (float)m_dwRow * m_vScale.z / 2.0f;
	const float fHighHalf = (float)m_vScale.y / 2.0f;
	const float fScaleY = m_vScale.y / 255.0f;
	DWORD dwNumIndex = 0;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			m_vecPosition[dwNumIndex].p.x = (float)x * m_vScale.x - fColHalf;
			m_vecPosition[dwNumIndex].p.y = 0.0f;
			m_vecPosition[dwNumIndex].p.z = fRowHalf - (float)z * m_vScale.z;

			m_vecPosition[dwNumIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			m_vecPosition[dwNumIndex].t = D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1));

			++dwNumIndex;
		}
	}
	return S_OK;
}

inline HRESULT cMapTerrain::_BuilldQuadTree(void)
{
	if (m_pQuadTree)
	{
		m_pQuadTree->TreeBuild(m_vecPosition);
		return S_OK;
	}
	return E_FAIL;
}

inline HRESULT cMapTerrain::_CreateVertexBuffer(void)
{
	//버텍스 생성
	SAFE_RELEASE(m_pVertexBuffer);
	g_pD3DDevice->CreateVertexBuffer(m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX),
		0, ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);

	//버텍스 락
	ST_PNT_VERTEX* pVertices = NULL;
	m_pVertexBuffer->Lock(0, m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX), (LPVOID*)&pVertices, 0);

	//복사
	memcpy(pVertices, &m_vecPosition[0], m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX));

	//버텍스 잠금해제
	m_pVertexBuffer->Unlock();
	return S_OK;
}

inline HRESULT cMapTerrain::_CreateIndexBuffer(void)
{
	SAFE_RELEASE(m_pIndexBufer);
	DWORD dwNumIndex = (m_dwCol - 1) * (m_dwRow - 1) * 6;
	LPDWORD pIndices;
	g_pD3DDevice->CreateIndexBuffer(dwNumIndex * sizeof(DWORD), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBufer, NULL);
	m_vecIndex.clear();
	m_vecIndex.resize(dwNumIndex);
	m_pIndexBufer->Lock(0, dwNumIndex * sizeof(DWORD), (LPVOID*)&pIndices, 0);
	//인덱스 연결
	DWORD dwIndex = 0;
	for (DWORD z = 0; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 0; x < (m_dwCol - 1); x++)
		{
			//삼각형 2개 인덱스
			m_vecIndex[dwIndex + 0] = pIndices[dwIndex + 0] = x + z * m_dwCol;
			m_vecIndex[dwIndex + 1] = pIndices[dwIndex + 1] = (x + 1) + z * m_dwCol;
			m_vecIndex[dwIndex + 2] = pIndices[dwIndex + 2] = x + (z + 1) * m_dwCol;

			m_vecIndex[dwIndex + 3] = pIndices[dwIndex + 3] = x + (z + 1) * m_dwCol;
			m_vecIndex[dwIndex + 4] = pIndices[dwIndex + 4] = (x + 1) + z * m_dwCol;
			m_vecIndex[dwIndex + 5] = pIndices[dwIndex + 5] = (x + 1) + (z + 1) * m_dwCol;

			//포인터 이동
			dwIndex += 6;
		}
	}
	m_pIndexBufer->Unlock();
	m_dwTriangles = dwNumIndex / 3;

	m_dwIndexBuffer = dwNumIndex; //맵 랜더용

	return S_OK;
}

inline HRESULT cMapTerrain::_Draw(void)
{
	D3DXMATRIXA16 mat;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&mat));
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetMaterial(&m_vecMaterals[0].MatD3D);
	g_pD3DDevice->SetTexture(0, m_vecTextures[0]);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetIndices(m_pIndexBufer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwCol * m_dwRow, 0, m_dwTriangles * 3);

	return S_OK;
}
