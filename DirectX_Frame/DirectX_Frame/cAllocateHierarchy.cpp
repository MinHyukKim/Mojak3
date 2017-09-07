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
	//생성
	ST_BONE* pNewFrame = new ST_BONE;
	cAllocateHierarchy::CopyString(&pNewFrame->Name, Name);
	(*ppNewFrame) = pNewFrame;

	return D3D_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
	assert(pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH);

	//생성
	ST_BONE_MESH* pNewMeshContainer = new ST_BONE_MESH;
	cAllocateHierarchy::CopyString(&pNewMeshContainer->Name, Name);
	int NumFaces = 0;

	//재질정보 저장
	if (pMaterials && NumMaterials)
	{
		pNewMeshContainer->pMaterials = new D3DXMATERIAL[NumMaterials];																//생성
		memcpy(pNewMeshContainer->pMaterials, pMaterials, NumMaterials * sizeof(D3DXMATERIAL));										//재질 복사
		for (DWORD i = 0; i < NumMaterials; ++i)
		{
			cAllocateHierarchy::CopyString(&pNewMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);		//텍스쳐 이름 복사
		}
		
		pNewMeshContainer->NumMaterials = NumMaterials;																				//갯수
	}

	//셰이더 저장
	if (pEffectInstances)
	{
		pNewMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
		*pNewMeshContainer->pEffects = *pEffectInstances;
	}

	//매니저에 메시등록 및 워킹 메시복사
	LPD3DXMESH pMesh = pMeshData->pMesh;
	if (pMesh)
	{
		//저장(오리진)
		NumFaces = pMesh->GetNumFaces(); //면의 갯수 (인덱스 버퍼의 3분의 1);
		pNewMeshContainer->MeshData = *pMeshData;
		pMesh->AddRef();

		//복사(워킹)
		pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), g_pD3DDevice, &pNewMeshContainer->pWorkingMesh);
	}

	//인접정보 복사
	if (pAdjacency && NumFaces)
	{
		pNewMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	}

	//반환
	*ppNewMeshContainer = pNewMeshContainer;
	return D3D_OK;
}

HRESULT cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	if (pFrameToFree)
	{
		//제거
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
		//캐스팅
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

		if (pMeshContainerToFree->MeshData.pMesh)
		{
			//인접정보 제거
			SAFE_DELETE_ARRAY(pMeshContainerToFree->pAdjacency);
			
			//원본 메시(최적화를 위해 메시매니저에서 처리 예정)
			pMeshContainerToFree->MeshData.pMesh->Release();
		}

		//복사된 워킹 메시 제거
		SAFE_RELEASE(pBoneMesh->pWorkingMesh);

		//임펙트 제거
		SAFE_DELETE(pMeshContainerToFree->pEffects);

		//재질정보 제거
		if (pMeshContainerToFree->pMaterials && pMeshContainerToFree->NumMaterials)
		{
			//텍스쳐 이름 제거
			for (DWORD i = 0; i < pMeshContainerToFree->NumMaterials; ++i)
			{
				SAFE_DELETE_ARRAY(pMeshContainerToFree->pMaterials[i].pTextureFilename);				//
			}

			//재질배열 제거
			SAFE_DELETE_ARRAY(pMeshContainerToFree->pMaterials);																			//갯수
		}

		//제거
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
