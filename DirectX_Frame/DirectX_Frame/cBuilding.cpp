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
		OutputDebugString("�� �ε� ����");
	}
	m_pFilename = filename;
	m_pFoldername = "";

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	// �ؽ��� �ε�
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			m_pMeshTextures[i] = g_pTexture->GetTexture(d3dxMaterials[i].pTextureFilename);
			//D3DXCreateTextureFromFile(g_pD3DDevice, d3dxMaterials[i].pTextureFilename,
			//	&m_pMeshTextures[i]);
		}
	}

	pD3DXMtrlBuffer->Release();  // ��Ƽ���� ���� ����

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff); // ��� �ֺ���
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ���� �޽��� ��ü ���ؽ� ������ �޾ƿɴϴ�.
	DWORD dwVertexNum = m_pBuild->GetNumVertices();

	// ���ؽ� ���۸� �����մϴ�^^
	LPDIRECT3DVERTEXBUFFER9 pVB;
	m_pBuild->GetVertexBuffer(&pVB);

	VOID* pVertices;

	minX = FLT_MAX;
	maxX = FLT_MIN;
	minY = FLT_MAX;
	maxY = FLT_MIN;
	minZ = FLT_MAX;
	maxZ = FLT_MIN;

	pVB->Lock(0, sizeof(ST_PNT_VERTEX) * m_pBuild->GetNumVertices(), (void**)&pVertices, 0);
	ST_PNT_VERTEX* pVertex = (ST_PNT_VERTEX*)pVertices;

	// ������ pVertex�� ���� �޽��� ��� ��ġ������ ���������Ƿ�, �̷������� �����ؼ� �ۼ��մϴ�.
	for (DWORD i = 0; i < dwVertexNum;i++)
	{
		if (pVertex[i].p.x > maxX)
			maxX = pVertex[i].p.x;
		if (pVertex[i].p.x < minX)
			minX = pVertex[i].p.x;

		if (pVertex[i].p.y > maxY)
			maxY = pVertex[i].p.y;
		if (pVertex[i].p.y < minX)
			minY = pVertex[i].p.y;

		if (pVertex[i].p.z > maxZ)
			maxZ = pVertex[i].p.z;
		if (pVertex[i].p.z < minZ)
			minZ = pVertex[i].p.z;
	}
	DEBUG_TEXT("min : " << minX << " max : " << maxX << " max-min :" << maxX - minX);
	DEBUG_TEXT("min : " << minY << " max : " << maxY << " max-min :" << maxY - minY);
	DEBUG_TEXT("min : " << minZ << " max : " << maxZ << " max-min :" << maxZ - minZ);
	DEBUG_TEXT("");
	// ���� �� ������ ���ؽ������� ���� ��������߰���.
	pVB->Unlock();
	pVB->Release();

	D3DXCreateBox(g_pD3DDevice, maxX - minX, maxY - minY, maxZ - minZ, &m_pBoundBox, NULL);
	//D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pBoundBox, NULL);
	//D3DXCreateSphere(g_pD3DDevice, 50.0f, 5, 5, &m_pBoundBox, nullptr);

	return m_pBuild;
}

LPD3DXMESH cBuilding::LoadModel(char * szFolder, char * szFilename)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);
	return LoadModel(sFullPath.c_str());
}


void cBuilding::Reset(void)
{
}

void cBuilding::Update(void)
{
}

void cBuilding::Render(void)
{


	D3DXMATRIXA16 mat = m_matWorld;
	mat._42 += m_fOffsetY;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//D3DXMATRIXA16 matView, matProjection, matViewProj, matWorldViewProjection;

	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		g_pD3DDevice->SetMaterial(&m_pMeshMaterials[i]);
		g_pD3DDevice->SetTexture(0, m_pMeshTextures[i]);

		m_pBuild->DrawSubset(i);
	}
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	if (m_pBoundBox != NULL)
	{
		D3DXMATRIXA16 mat = m_matWorld;
		mat._42 += (maxY - minY) / 2.0f;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		D3DMATERIAL9 mtl = {};
		mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f,0.3f);
		g_pD3DDevice->SetMaterial(&mtl);
		m_pBoundBox->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	}

}

void cBuilding::SetAngleX(float fX)
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationAxis(&matR, (LPD3DXVECTOR3)&m_matWorld._11, fX);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._21, (LPD3DXVECTOR3)&m_matWorld._21, &matR);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._31, (LPD3DXVECTOR3)&m_matWorld._31, &matR);
}

void cBuilding::SetAngleY(float fY)
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationAxis(&matR, (LPD3DXVECTOR3)&m_matWorld._21, fY);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._11, (LPD3DXVECTOR3)&m_matWorld._11, &matR);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._31, (LPD3DXVECTOR3)&m_matWorld._31, &matR);
}

void cBuilding::SetAngleZ(float fZ)
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationAxis(&matR, (LPD3DXVECTOR3)&m_matWorld._31, fZ);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._11, (LPD3DXVECTOR3)&m_matWorld._11, &matR);
	D3DXVec3TransformCoord((LPD3DXVECTOR3)&m_matWorld._21, (LPD3DXVECTOR3)&m_matWorld._21, &matR);
}

cBuilding::cBuilding(void)
	:m_pBuild(NULL)
	, m_pEffect(NULL)
	, m_pMaterials(nullptr)
	, m_pMeshMaterials(NULL)
	, m_pMeshTextures(NULL)
	, m_dwNumMaterials(0)
	, angleX(0.0f)
	, angleY(0.0f)
	, angleZ(0.0f)
	, m_fOffsetY(0.0f)
	, m_pBoundBox(NULL)
	, m_pFilename("")
	, m_pFoldername("")
	, m_fScale(1.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cBuilding::cBuilding(cBuilding* pBuilding) : cBuilding(*pBuilding)
{
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


void cBuilding::OffsetScale(float scale)
{
	m_fScale += scale;
	D3DXVECTOR3 v = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
	D3DXMatrixScaling(&m_matWorld, m_fScale, m_fScale, m_fScale);
	memcpy(&m_matWorld._41, &v, sizeof(D3DXVECTOR3));
}

void cBuilding::Destroy(void)
{
	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	SAFE_DELETE_ARRAY(m_pMeshTextures);

	SAFE_RELEASE(m_pBuild);
	SAFE_RELEASE(m_pBoundBox);
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

cBuilding* cBuilding::Create(void)
{
	cBuilding* newClass = new cBuilding;
	newClass->AddRef();
	return newClass;
}

cBuilding* cBuilding::Create(cBuilding* pBuilding)
{
	cBuilding* newClass = new cBuilding(pBuilding);
	newClass->AddRef();
	return newClass;
}
