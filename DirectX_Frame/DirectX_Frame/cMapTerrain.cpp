#include "stdafx.h"
#include "cMapTerrain.h"

#include "cQuadTree.h"
#include "cFrustum.h"

cMapTerrain::cMapTerrain(void)
	: m_pVertexBuffer(nullptr)
	, m_pIndexBufer(nullptr)
	, m_pHeightMap(nullptr)
	, m_pQuadTree(nullptr)
	, m_vScale(1.0f, 10.0f, 1.0f)
	, m_dwCol(0)
	, m_dwRow(0)
	, m_dwTriangles(0)
{
}

cMapTerrain::~cMapTerrain(void)
{
	this->_Destroy();
}


HRESULT cMapTerrain::Setup(LPCSTR szHeightMapName, D3DXMATERIAL* pMaterial, LPD3DXVECTOR3 pScale)
{
	this->m_vScale = *pScale;
	this->_BuildHeightMap(szHeightMapName);
	this->_LoadTexture(pMaterial);
	this->_CreateVertexBuffer();
	this->_CreateIndexBuffer();
	SAFE_DELETE(m_pQuadTree);
//	m_pQuadTree = new cQuadTree(m_dwCol, m_dwRow);
//	this->_BuilldQuadTree();

	return S_OK;
}

void cMapTerrain::Update(void)
{
//	LPDWORD pIndex;
//	if (FAILED(m_pIndexBufer->Lock(0, (m_dwCol - 1) * (m_dwRow - 1) * 6 * sizeof(DWORD), (LPVOID*)&pIndex, 0))) return;
//	m_dwTriangles = m_pQuadTree->GenerateIndex(pIndex, &m_pHeightMap, m_pFrustum);
//	m_pIndexBufer->Unlock();
}

void cMapTerrain::Render(void)
{
	this->_Draw();
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

	SAFE_DELETE_ARRAY(m_pHeightMap);

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
	SAFE_DELETE_ARRAY(m_pHeightMap);
	m_pHeightMap = new ST_PNT_VERTEX[dwNumVertex];

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
			m_pHeightMap[dwNumIndex].p.x = (float)x * m_vScale.x - fColHalf;
			m_pHeightMap[dwNumIndex].p.y = pHeightMap->pBytes[dwNumIndex] * fScaleY - fHighHalf;
			m_pHeightMap[dwNumIndex].p.z = fRowHalf - (float)z * m_vScale.z;

			m_pHeightMap[dwNumIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			m_pHeightMap[dwNumIndex].t = D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1));

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
			D3DXVec3Cross(&m_pHeightMap[dwNumIndex].n,
				&(m_pHeightMap[dwNumIndex - 1].p - m_pHeightMap[dwNumIndex + 1].p),
				&(m_pHeightMap[dwNumIndex - m_dwCol].p - m_pHeightMap[dwNumIndex + m_dwCol].p));
			D3DXVec3Normalize(&m_pHeightMap[dwNumIndex].n, &m_pHeightMap[dwNumIndex].n);
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
			m_pHeightMap[dwNumIndex].p.x = (float)x * m_vScale.x - fColHalf;
			m_pHeightMap[dwNumIndex].p.y = 0.0f;
			m_pHeightMap[dwNumIndex].p.z = fRowHalf - (float)z * m_vScale.z;

			m_pHeightMap[dwNumIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			m_pHeightMap[dwNumIndex].t = D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1));

			++dwNumIndex;
		}
	}
	return S_OK;
}

inline HRESULT cMapTerrain::_BuilldQuadTree(void)
{
	if (m_pQuadTree)
	{
		m_pQuadTree->TreeBuild(m_pHeightMap);
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

	//맴카피
	memcpy(pVertices, &m_pHeightMap[0], m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX));

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
	m_pIndexBufer->Lock(0, dwNumIndex * sizeof(DWORD), (LPVOID*)&pIndices, 0);

	//인덱스 연결
	for (DWORD z = 0; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 0; x < (m_dwCol - 1); x++)
		{
			//삼각형 2개 인덱스
			pIndices[0] = x + z * m_dwCol;
			pIndices[1] = (x + 1) + z * m_dwCol;
			pIndices[2] = x + (z + 1) * m_dwCol;
			pIndices[3] = x + (z + 1) * m_dwCol;
			pIndices[4] = (x + 1) + z * m_dwCol;
			pIndices[5] = (x + 1) + (z + 1) * m_dwCol;

			//포인터 이동
			pIndices += 6;
		}
	}

	m_dwTriangles = dwNumIndex / 3;

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
