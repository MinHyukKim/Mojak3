#include "stdafx.h"
#include "cMapTerrain.h"

#include "cQuadTree.h"

cMapTerrain::cMapTerrain(void)
	: m_vScale(1.0f, 10.0f, 1.0f)
	, m_pVertexBuffer(nullptr)
	, m_pIndexBufer(nullptr)
	, m_pQuadTree(nullptr)
{
}

cMapTerrain::~cMapTerrain(void)
{
}


HRESULT cMapTerrain::Setup(void)
{
	return E_NOTIMPL;
}

void cMapTerrain::Update(void)
{
}

void cMapTerrain::Render(void)
{
}


cMapTerrain* cMapTerrain::Create(void)
{
	cMapTerrain* newClass = new cMapTerrain;
	newClass->AddRef();
	return newClass;
}


inline HRESULT cMapTerrain::_Destroy(void)
{
	SAFE_DELETE(m_pQuadTree);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBufer);
	return S_OK;
}
inline HRESULT cMapTerrain::_LoadTexture(LPSTR szTexFileName)
{
	return E_NOTIMPL;
}

inline HRESULT cMapTerrain::_BuildHeightMap(LPCSTR szMapName)
{
	ST_HEIGHT_MAP* pHeightMap = g_pTexture->GetHeightMap(szMapName);
	if (!pHeightMap) return E_FAIL;
	SAFE_RELEASE(m_pVertexBuffer);

	//�ٴ� �������� (surfaceInfo);
	DWORD dwNumVertex = pHeightMap->dwSize / pHeightMap->dwByte;
	m_dwRow = sqrt(dwNumVertex + FLT_EPSILON);
	if (dwNumVertex != m_dwRow * m_dwRow)
	{
		assert(false && "���簢������ RAW���ϸ� ��� �����մϴ�.");
	}
	m_dwCol = m_dwRow;

	//���ؽ� ��
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX),
		0, ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL))) return E_FAIL;
	
	//���ؽ� ��ǥ ���
	const float fColHalf = (float)m_dwCol * m_vScale.x / 2.0f;
	const float fRowHalf = (float)m_dwRow * m_vScale.z / 2.0f;
	const float fHighHalf = (float)m_vScale.y / 2.0f;
	const float fScaleY = m_vScale.y / 255.0f;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			float fY = (float)pHeightMap->pBytes[(x + z * m_dwCol) * pHeightMap->dwByte + pHeightMap->dwByte - 1];

			m_vecMapVertex.push_back(ST_PNT_VERTEX(
				D3DXVECTOR3((float)x * m_vScale.x - fColHalf, fY * fScaleY - fHighHalf, fRowHalf - (float)z * m_vScale.z),
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1))));
		}
	}

	//�븻�� ���
	for (DWORD z = 1; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 1; x < (m_dwCol - 1); x++)
		{
			//�ε���
			DWORD dwNumIndex = x + z * m_dwCol;
			//�븻��
			D3DXVec3Cross(&m_vecMapVertex[dwNumIndex].n,
				&(m_vecMapVertex[dwNumIndex - 1].p - m_vecMapVertex[dwNumIndex + 1].p),
				&(m_vecMapVertex[dwNumIndex - m_dwCol].p - m_vecMapVertex[dwNumIndex + m_dwCol].p));
			D3DXVec3Normalize(&m_vecMapVertex[dwNumIndex].n, &m_vecMapVertex[dwNumIndex].n);
		}
	}

	//���ؽ� �������
	m_pVertexBuffer->Unlock();
	return S_OK;
}

inline HRESULT cMapTerrain::_BuildHeightMap(DWORD dwCol, DWORD dwRow)
{
	SAFE_RELEASE(m_pVertexBuffer);

	//�ٴ� �������� (surfaceInfo);
	m_dwCol = dwCol;
	m_dwRow = dwRow;

	//���ؽ� ��
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX),
		0, ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL))) return E_FAIL;

	//���ؽ� ��ǥ ���
	const float fColHalf = (float)m_dwCol * m_vScale.x / 2.0f;
	const float fRowHalf = (float)m_dwRow * m_vScale.z / 2.0f;
	const float fHighHalf = (float)m_vScale.y / 2.0f;
	const float fScaleY = m_vScale.y / 255.0f;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			m_vecMapVertex.push_back(ST_PNT_VERTEX(
				D3DXVECTOR3((float)x * m_vScale.x - fColHalf, 0.0f, fRowHalf - (float)z * m_vScale.z),
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				D3DXVECTOR2((float)(x & 0x1), (float)(z & 0x1))));
		}
	}

	//���ؽ� �������
	m_pVertexBuffer->Unlock();
	return S_OK;
}

inline HRESULT cMapTerrain::_BuilldQuadTree(void)
{
	if (m_pQuadTree)
	{
		m_pQuadTree->TreeBuild();
		return S_OK;
	}
	return E_FAIL;
}

inline HRESULT cMapTerrain::_CreateIndexBuffer(void)
{
	SAFE_RELEASE(m_pIndexBufer);


	return E_NOTIMPL;
}

inline HRESULT cMapTerrain::_Draw(void)
{
	return E_NOTIMPL;
}
