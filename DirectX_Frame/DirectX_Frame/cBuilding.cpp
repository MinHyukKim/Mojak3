#include "stdafx.h"
#include "cBuilding.h"

HRESULT cBuilding::Setup(void)
{
	return S_OK;
}

LPD3DXMESH cBuilding::LoadModel(const char * filename)
{
	//g_pSkinnedMeshManager->RegisterSkinnedMesh("", "scene_building_tirchonaill_church.x", "build");
	SAFE_RELEASE(m_pEffect);
	m_pEffect = LoadEffect("MultiAnimation.hpp");
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	LPD3DXBUFFER pD3DXMtrlBuffer;

	//LPD3DXMESH ret = NULL;
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

	return m_pBuild;
}

LPD3DXMESH cBuilding::LoadModel(char * szFolder, char * szFilename)
{
	SAFE_RELEASE(m_pEffect);
	m_pEffect = LoadEffect("MultiAnimation.hpp");
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	LPD3DXBUFFER pD3DXMtrlBuffer;

	//LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(sFullPath.c_str(), D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pBuild)));
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


	return m_pBuild;
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
	, m_pEffect(NULL)
	, m_pMeshMaterials(NULL)
	, m_pMeshTextures(NULL)
	, m_dwNumMaterials(0)
	, angleX(0.0f)
	, angleY(0.0f)
	, angleZ(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRot);

}

cBuilding::~cBuilding(void)
{

}

//cBuilding* cBuilding::Create(void)
//{
//	cBuilding* newClass = new cBuilding;
//	newClass->AddRef();
//	return newClass;
//}


void cBuilding::Destroy()
{
	//계별적으로 관리함
	for (int i = 0; i < m_dwNumMaterials; i++)
	{
		//SAFE_RELEASE(m_pMeshTextures[i]);
	}
	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	SAFE_DELETE_ARRAY(m_pMeshTextures);

	m_pBuild->Release();
	SAFE_RELEASE(m_pEffect);
}

LPD3DXEFFECT cBuilding::LoadEffect(char * szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}