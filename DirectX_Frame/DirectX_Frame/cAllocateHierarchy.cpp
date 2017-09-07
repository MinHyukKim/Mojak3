#include "stdafx.h"
#include "cAllocateHierarchy.h"

cAllocateHierarchy::cAllocateHierarchy(void)
	: m_dwDefaultPalette(0)
	, m_dwNumMaxPalette(0)
	, m_vMin(FLT_MAX, FLT_MAX, FLT_MAX)
	, m_vMax(FLT_MIN, FLT_MIN, FLT_MIN)
{
}

cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

HRESULT cAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
	//����
	ST_BONE* pNewFrame = new ST_BONE;
	cAllocateHierarchy::CopyString(&pNewFrame->Name, Name);
	(*ppNewFrame) = pNewFrame;

	return D3D_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
	assert(pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH);

	//����
	ST_BONE_MESH* pNewMeshContainer = new ST_BONE_MESH;
	cAllocateHierarchy::CopyString(&pNewMeshContainer->Name, Name);
	int NumFaces = 0;

	//�������� ����
	if (pMaterials && NumMaterials)
	{
		pNewMeshContainer->pMaterials = new D3DXMATERIAL[NumMaterials];																//����
		memcpy(pNewMeshContainer->pMaterials, pMaterials, NumMaterials * sizeof(D3DXMATERIAL));										//���� ����
		for (DWORD i = 0; i < NumMaterials; ++i)
		{
			cAllocateHierarchy::CopyString(&pNewMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);		//�ؽ��� �̸� ����
		}
		
		pNewMeshContainer->NumMaterials = NumMaterials;																				//����
	}

	//���̴� ����
	if (pEffectInstances)
	{
		pNewMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
		*pNewMeshContainer->pEffects = *pEffectInstances;
	}

	//�Ŵ����� �޽õ�� �� ��ŷ �޽ú���
	LPD3DXMESH pMesh = pMeshData->pMesh;
	if (pMesh)
	{
		//����(������)
		NumFaces = pMesh->GetNumFaces(); //���� ���� (�ε��� ������ 3���� 1);
		pNewMeshContainer->MeshData = *pMeshData;
		pMesh->AddRef();

		//����(��ŷ)
		pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), g_pD3DDevice, &pNewMeshContainer->pWorkingMesh);
	}

	//�������� ����
	if (pAdjacency && NumFaces)
	{
		pNewMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	}

	//��ȯ
	*ppNewMeshContainer = pNewMeshContainer;
	return D3D_OK;
}

HRESULT cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	if (pFrameToFree)
	{
		//����
		SAFE_DELETE_ARRAY(pFrameToFree->Name);
		delete pFrameToFree;

		return D3D_OK;
	}
	return E_FAIL;
}

HRESULT cAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	if (pMeshContainerToFree)
	{
		//ĳ����
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

		if (pMeshContainerToFree->MeshData.pMesh)
		{
			//�������� ����
			SAFE_DELETE_ARRAY(pMeshContainerToFree->pAdjacency);
			
			//���� �޽�(����ȭ�� ���� �޽øŴ������� ó�� ����)
			pMeshContainerToFree->MeshData.pMesh->Release();
		}

		//����� ��ŷ �޽� ����
		SAFE_RELEASE(pBoneMesh->pWorkingMesh);

		//����Ʈ ����
		SAFE_DELETE(pMeshContainerToFree->pEffects);

		//�������� ����
		if (pMeshContainerToFree->pMaterials && pMeshContainerToFree->NumMaterials)
		{
			//�ؽ��� �̸� ����
			for (DWORD i = 0; i < pMeshContainerToFree->NumMaterials; ++i)
			{
				SAFE_DELETE_ARRAY(pMeshContainerToFree->pMaterials[i].pTextureFilename);				//
			}

			//�����迭 ����
			SAFE_DELETE_ARRAY(pMeshContainerToFree->pMaterials);																			//����
		}

		//����
		SAFE_DELETE_ARRAY(pMeshContainerToFree->Name);
		delete pMeshContainerToFree;

		return D3D_OK;
	}
	return E_FAIL;
}

HRESULT cAllocateHierarchy::CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin)
{
	if (pTextOrigin && ppTextCopy)
	{
		int nLength = lstrlen(pTextOrigin) + 1;
		(*ppTextCopy) = new char[nLength];
		memcpy(*ppTextCopy, pTextOrigin, nLength * sizeof(char));
		return D3D_OK;
	}
	return E_FAIL;
}
