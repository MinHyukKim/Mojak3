#include "stdafx.h"
#include "cMapObject.h"

cMapObject::cMapObject(void)
	: m_pVertexBuffer(NULL)
	, m_pIndexBufer(NULL)
	, m_texHeight(NULL)
	, m_texDiffuse(NULL)
	, m_dwCol(0)
	, m_dwRow(0)
{
}

cMapObject::~cMapObject(void)
{
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

void cMapObject::Update(void)
{
}

void cMapObject::Render(void)
{
}

HRESULT cMapObject::InitVB(void)
{
	D3DSURFACE_DESC surfaceDesc;
	D3DLOCKED_RECT lockedRect;

	//���̸� ũ���� ���� ����
	m_texHeight->GetLevelDesc(0, &surfaceDesc);
	m_dwCol = surfaceDesc.Width;
	m_dwRow = surfaceDesc.Height;
	DWORD dwBufferSize = m_dwCol * m_dwRow * sizeof(ST_PNT_VERTEX);
	if (FAILED(g_pD3DDevice->CreateVertexBuffer(dwBufferSize, 0,
		ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	//�ؽ�ó �޸� ��
	m_texHeight->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
	//���� ���� ��
	LPVOID pVertices;
	if (FAILED(m_pVertexBuffer->Lock(0, dwBufferSize, (LPVOID*)&pVertices, 0)))
	{
		m_texHeight->UnlockRect(0);
		return E_FAIL;
	}

	//���̰� ���
	const float fColHalf = (float)m_dwCol / 2.0f;
	const float fRowHalf = (float)m_dwRow / 2.0f;
	ST_PNT_VERTEX* pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 0; z < m_dwRow; z++)
	{
		for (DWORD x = 0; x < m_dwCol; x++)
		{
			float fY = (*((LPDWORD)lockedRect.pBits + x + z * (lockedRect.Pitch / 4)) & 0x000000ff);

			ST_PNT_VERTEX vVertex(
				D3DXVECTOR3((float)x - fColHalf, fY, fRowHalf - (float)z),
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				D3DXVECTOR2((float)x / (m_dwCol - 1), (float)z / (m_dwRow - 1)));

			(*pVertexBuffer) = vVertex;
			++pVertexBuffer;
		}
	}

	//�븻�� ���
	pVertexBuffer = (ST_PNT_VERTEX*)pVertices;
	for (DWORD z = 1; z < (m_dwRow - 1); z++)
	{
		for (DWORD x = 1; x < (m_dwCol - 1); x++)
		{
			//�̱���
			(*pVertexBuffer).n;
			++pVertexBuffer;
		}
	}

	m_pVertexBuffer->Unlock();
	m_texHeight->UnlockRect(0);
	return S_OK;
}

HRESULT cMapObject::InitIB(void)
{
	return E_NOTIMPL;
}

cMapObject* cMapObject::Create(void)
{
	cMapObject* newClass = new cMapObject;
	newClass->AddRef();
	return newClass;
}