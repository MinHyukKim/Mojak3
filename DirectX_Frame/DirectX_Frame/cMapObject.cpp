#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
	: m_pVertexBuffer(NULL)
	, m_pIndexBufer(NULL)
	, m_texHeight(NULL)
	, m_texDiffuse(NULL)
	, m_dwNumVertex(0)
	, m_dwNumFace(0)
	, m_dwCol(0)
	, m_dwRow(0)
	, m_fMinHeight(-8.0)
	, m_fMaxHeight(8.0)
{
}

cMapObject::~cMapObject(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBufer);
}

HRESULT cMapObject::Setup(IN LPCSTR szHeightMap)
{
	//하이맵 로더
	m_texHeight = g_pTexture->GetHeightMap(szHeightMap);
	if (!m_texHeight) return E_FAIL;

	//버텍스 초기화
	if (FAILED(this->InitVB())) return E_FAIL;

	//인덱스 초기화
	if (FAILED(this->InitIB())) return E_FAIL;

	return S_OK;
}

HRESULT cMapObject::Setup(IN DWORD dwCol, IN DWORD dwRow)
{

	//버텍스 초기화
	if (FAILED(this->InitVB(dwCol + 1, dwRow + 1))) return E_FAIL;

	//인덱스 초기화
	if (FAILED(this->InitIB())) return E_FAIL;

	return E_NOTIMPL;
}

void cMapObject::Update(void)
{
}

void cMapObject::Render(void)
{
	D3DXMATRIXA16 mat;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&mat));
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetIndices(m_pIndexBufer);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwNumVertex, 0, m_dwNumFace);
}

HRESULT cMapObject::InitVB(void)
{
	LPDIRECT3DVERTEXBUFFER9 pPrevBuffer = m_pVertexBuffer;
	D3DSURFACE_DESC surfaceDesc;
	D3DLOCKED_RECT lockedRect;

	//하이맵 크기의 정점 생성
	m_texHeight->GetLevelDesc(0, &surfaceDesc);
	m_dwCol = surfaceDesc.Width;
	m_dwRow = surfaceDesc.Height;
	m_dwNumVertex = m_dwCol * m_dwRow;
	DWORD dwBufferSize = m_dwNumVertex * sizeof(ST_PNT_VERTEX);
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(dwBufferSize, 0,
		ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
	{
		m_pVertexBuffer = pPrevBuffer;
		return E_FAIL;
	}

	//텍스처 메모리 락
	m_texHeight->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
	//버텍스 락
	LPVOID pVertices;
	if (FAILED(m_pVertexBuffer->Lock(0, dwBufferSize, (LPVOID*)&pVertices, 0)))
	{
		SAFE_RELEASE(m_pVertexBuffer);
		m_pVertexBuffer = pPrevBuffer;
		m_texHeight->UnlockRect(0);
		return E_FAIL;
	}

	//버텍스 좌표 계산
	const float fColHalf = (float)m_dwCol / 2.0f;
	const float fRowHalf = (float)m_dwRow / 2.0f;
	const float fScale = (m_fMaxHeight - m_fMinHeight) / 255.0f;
	ST_PNT_VERTEX* pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			float fY = (*((LPDWORD)lockedRect.pBits + x + z * (lockedRect.Pitch / 4)) & 0x000000ff);

			ST_PNT_VERTEX vVertex(
				D3DXVECTOR3((float)x - fColHalf, fY * fScale + m_fMinHeight, fRowHalf - (float)z),
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				D3DXVECTOR2((float)x / (m_dwCol - 1), (float)z / (m_dwRow - 1)));

			(*pVertexBuffer) = vVertex;
			//포인터 이동
			++pVertexBuffer;
		}
	}

	//노말값 계산
	pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 1; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 1; x < (m_dwCol - 1); x++)
		{
			D3DXVec3Cross(&pVertexBuffer->n,
				&((pVertexBuffer - 1)->p - (pVertexBuffer + 1)->p),
				&((pVertexBuffer - m_dwCol)->p - (pVertexBuffer + m_dwCol)->p));
			D3DXVec3Normalize(&pVertexBuffer->n, &pVertexBuffer->n);
			//포인터 이동
			++pVertexBuffer;
		}
	}

	m_pVertexBuffer->Unlock();
	m_texHeight->UnlockRect(0);
	SAFE_RELEASE(pPrevBuffer);
	return S_OK;
}

HRESULT cMapObject::InitVB(IN DWORD dwCol, IN DWORD dwRow)
{
	LPDIRECT3DVERTEXBUFFER9 pPrevBuffer = m_pVertexBuffer;
	D3DSURFACE_DESC surfaceDesc;
	D3DLOCKED_RECT lockedRect;

	//하이맵 크기의 정점 생성
	m_dwCol = dwCol;
	m_dwRow = dwRow;
	m_dwNumVertex = m_dwCol * m_dwRow;
	DWORD dwBufferSize = m_dwNumVertex * sizeof(ST_PNT_VERTEX);
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(dwBufferSize, 0,
		ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
	{
		m_pVertexBuffer = pPrevBuffer;
		return E_FAIL;
	}

	//버텍스 락
	LPVOID pVertices;
	if (FAILED(m_pVertexBuffer->Lock(0, dwBufferSize, (LPVOID*)&pVertices, 0)))
	{
		SAFE_RELEASE(m_pVertexBuffer);
		m_pVertexBuffer = pPrevBuffer;
		m_texHeight->UnlockRect(0);
		return E_FAIL;
	}

	//버텍스 좌표 계산
	const float fColHalf = (float)m_dwCol / 2.0f;
	const float fRowHalf = (float)m_dwRow / 2.0f;
	ST_PNT_VERTEX* pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			ST_PNT_VERTEX vVertex(
				D3DXVECTOR3((float)x - fColHalf, 0.0f, fRowHalf - (float)z),
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				D3DXVECTOR2((float)x / (m_dwCol - 1), (float)z / (m_dwRow - 1)));

			(*pVertexBuffer) = vVertex;
			//포인터 이동
			++pVertexBuffer;
		}
	}

	//마무리
	m_pVertexBuffer->Unlock();
	SAFE_RELEASE(pPrevBuffer);
	return S_OK;
}

HRESULT cMapObject::InitIB(void)
{
	LPDIRECT3DINDEXBUFFER9 pPrevBuffer = m_pIndexBufer;
	//생성
	m_dwNumFace = (m_dwCol - 1) * (m_dwRow - 1) * 2;
	DWORD dwBufferSize = m_dwNumFace * 3 * sizeof(DWORD);
	if (FAILED(g_pD3DDevice->CreateIndexBuffer(dwBufferSize, 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBufer, NULL)))
	{
		m_pIndexBufer = pPrevBuffer;
		return E_FAIL;
	}

	//인덱스 락
	LPDWORD pIndex;
	if (FAILED(m_pIndexBufer->Lock(0, dwBufferSize, (LPVOID*)&pIndex, 0)))
	{
		SAFE_RELEASE(m_pIndexBufer);
		m_pIndexBufer = pPrevBuffer;
		return E_FAIL;
	}

	//인덱스 연결
	for (DWORD z = 0; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 0; x < (m_dwCol - 1); x++)
		{
			//삼각형 2개 인덱스
			pIndex[0] = x + z * m_dwCol;
			pIndex[1] = (x + 1) + z * m_dwCol;
			pIndex[2] = x + (z + 1) * m_dwCol;
			pIndex[3] = x + (z + 1) * m_dwCol;
			pIndex[4] = (x + 1) + z * m_dwCol;
			pIndex[5] = (x + 1) + (z + 1) * m_dwCol;

			//포인터 이동
			pIndex += 6;
		}
	}
	
	//하이맵 생성(미구현)

	//마무리
	m_pIndexBufer->Unlock();
	SAFE_RELEASE(pPrevBuffer);
	return S_OK;
}

cMapObject* cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}