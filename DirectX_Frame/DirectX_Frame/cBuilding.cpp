#include "stdafx.h"
#include "cBuilding.h"

HRESULT cBuilding::Setup(void)
{
	return S_OK;
}

LPD3DXMESH cBuilding::LoadModel(const char * filename)
{
	//g_pSkinnedMeshManager->RegisterSkinnedMesh("", "scene_building_tirchonaill_church.x", "build");

	LPD3DXBUFFER pD3DXMtrlBuffer;

	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pBuild)));
	{
		OutputDebugString("모델 로딩 실패");
	}

	D3DXMATERIAL* d3dxMaterials =
		(D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	// 텍스쳐 로딩
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(g_pD3DDevice, d3dxMaterials[i].pTextureFilename,
				&m_pMeshTextures[i]);
		}
	}

	pD3DXMtrlBuffer->Release();  // 머티리얼 버퍼 해제

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff); // 흰색 주변광
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return nullptr;
}

void cBuilding::Reset(void)
{
}

void cBuilding::Update(void)
{
}

void cBuilding::Render(void)
{
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	D3DXMATRIXA16 matView, matProjection, matViewProj, matWorldViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		g_pD3DDevice->SetMaterial(&m_pMeshMaterials[i]);
		g_pD3DDevice->SetTexture(0, m_pMeshTextures[i]);

		m_pBuild->DrawSubset(i);
	}
}

cBuilding::cBuilding(void)
	:m_pBuild(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cBuilding::~cBuilding(void)
{
	this->Reset();
	for (int i = 0; i < m_dwNumMaterials; i++)
	{
		SAFE_RELEASE(m_pMeshTextures[i]);
	}
	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	SAFE_DELETE_ARRAY(m_pMeshTextures);
	
	m_pBuild->Release();
}

cBuilding* cBuilding::Create(void)
{
	cBuilding* newClass = new cBuilding;
	newClass->AddRef();
	return newClass;
}
