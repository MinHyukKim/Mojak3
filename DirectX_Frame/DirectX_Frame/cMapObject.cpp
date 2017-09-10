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
	//���̸� �δ�
	m_texHeight = g_pTexture->GetHeightMap(szHeightMap);
	if (!m_texHeight) return E_FAIL;

	//���ؽ� �ʱ�ȭ
	if (FAILED(this->InitVB())) return E_FAIL;

	//�ε��� �ʱ�ȭ
	if (FAILED(this->InitIB())) return E_FAIL;

	return S_OK;
}

HRESULT cMapObject::Setup(IN DWORD dwCol, IN DWORD dwRow)
{

	//���ؽ� �ʱ�ȭ
	if (FAILED(this->InitVB(dwCol + 1, dwRow + 1))) return E_FAIL;

	//�ε��� �ʱ�ȭ
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

	//���̸� ũ���� ���� ����
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

	//�ؽ�ó �޸� ��
	m_texHeight->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
	//���ؽ� ��
	LPVOID pVertices;
	if (FAILED(m_pVertexBuffer->Lock(0, dwBufferSize, (LPVOID*)&pVertices, 0)))
	{
		SAFE_RELEASE(m_pVertexBuffer);
		m_pVertexBuffer = pPrevBuffer;
		m_texHeight->UnlockRect(0);
		return E_FAIL;
	}

	//���ؽ� ��ǥ ���
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
			//������ �̵�
			++pVertexBuffer;
		}
	}

	//�븻�� ���
	pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 1; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 1; x < (m_dwCol - 1); x++)
		{
			D3DXVec3Cross(&pVertexBuffer->n,
				&((pVertexBuffer - 1)->p - (pVertexBuffer + 1)->p),
				&((pVertexBuffer - m_dwCol)->p - (pVertexBuffer + m_dwCol)->p));
			D3DXVec3Normalize(&pVertexBuffer->n, &pVertexBuffer->n);
			//������ �̵�
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

	//���̸� ũ���� ���� ����
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

	//���ؽ� ��
	LPVOID pVertices;
	if (FAILED(m_pVertexBuffer->Lock(0, dwBufferSize, (LPVOID*)&pVertices, 0)))
	{
		SAFE_RELEASE(m_pVertexBuffer);
		m_pVertexBuffer = pPrevBuffer;
		m_texHeight->UnlockRect(0);
		return E_FAIL;
	}

	//���ؽ� ��ǥ ���
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
			//������ �̵�
			++pVertexBuffer;
		}
	}

	//������
	m_pVertexBuffer->Unlock();
	SAFE_RELEASE(pPrevBuffer);
	return S_OK;
}

HRESULT cMapObject::InitIB(void)
{
	LPDIRECT3DINDEXBUFFER9 pPrevBuffer = m_pIndexBufer;
	//����
	m_dwNumFace = (m_dwCol - 1) * (m_dwRow - 1) * 2;
	DWORD dwBufferSize = m_dwNumFace * 3 * sizeof(DWORD);
	if (FAILED(g_pD3DDevice->CreateIndexBuffer(dwBufferSize, 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBufer, NULL)))
	{
		m_pIndexBufer = pPrevBuffer;
		return E_FAIL;
	}

	//�ε��� ��
	LPDWORD pIndex;
	if (FAILED(m_pIndexBufer->Lock(0, dwBufferSize, (LPVOID*)&pIndex, 0)))
	{
		SAFE_RELEASE(m_pIndexBufer);
		m_pIndexBufer = pPrevBuffer;
		return E_FAIL;
	}

	//�ε��� ����
	for (DWORD z = 0; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 0; x < (m_dwCol - 1); x++)
		{
			//�ﰢ�� 2�� �ε���
			pIndex[0] = x + z * m_dwCol;
			pIndex[1] = (x + 1) + z * m_dwCol;
			pIndex[2] = x + (z + 1) * m_dwCol;
			pIndex[3] = x + (z + 1) * m_dwCol;
			pIndex[4] = (x + 1) + z * m_dwCol;
			pIndex[5] = (x + 1) + (z + 1) * m_dwCol;

			//������ �̵�
			pIndex += 6;
		}
	}
	
	//���̸� ����(�̱���)

	//������
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