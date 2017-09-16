#include "stdafx.h"
#include "cAllocateHierarchy.h"

cAllocateHierarchy::cAllocateHierarchy(void)
	: m_dwDefaultPalette(0)
	, m_dwNumMaxPalette(0)
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

#ifdef CONSOLE_DEBUG_TEST
	if (Name)
	{
		DEBUG_TEXT(Name);
	}
#endif

	//반환
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
		pNewMeshContainer->vecTexture.resize(NumMaterials);
		for (DWORD i = 0; i < NumMaterials; ++i)
		{
			cAllocateHierarchy::CopyString(&pNewMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);		//텍스쳐 이름 복사
			//하이라키에 폴더 이름이 없음 텍스쳐는 Setup에서
		}
		pNewMeshContainer->NumMaterials = NumMaterials;																				//갯수
	}

	//이펙트 저장
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
	}

	//인접정보 복사
	if (pAdjacency && NumFaces)
	{
		pNewMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	}

	// 스킨정보 저장
	if (pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pNewMeshContainer->pSkinInfo = pSkinInfo;
		pNewMeshContainer->pSkinInfo->AddRef();

		//매트릭스 동적할당
		pNewMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIXA16*[dwNumBones];
		pNewMeshContainer->pBoneOffsetMatrices = new D3DXMATRIXA16[dwNumBones];
		//매트릭스 복사
		for (int i = 0; i < dwNumBones; i++)
		{
			pNewMeshContainer->ppBoneMatrixPtrs[i] = NULL;
			pNewMeshContainer->pBoneOffsetMatrices[i] = *pSkinInfo->GetBoneOffsetMatrix(i);
		}

		pNewMeshContainer->dwNumPaletteEntries = min(m_dwDefaultPalette, pSkinInfo->GetNumBones());

		if (m_dwNumMaxPalette < pNewMeshContainer->dwNumPaletteEntries) m_dwNumMaxPalette = pNewMeshContainer->dwNumPaletteEntries;
		
		//워킹 메시 복사 및 재설정 (기능추가)
		if (pMesh)
		{
			pNewMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh(
				pMesh,
				D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
				pNewMeshContainer->dwNumPaletteEntries,
				pNewMeshContainer->pAdjacency,
				NULL, NULL, NULL,
				&pNewMeshContainer->dwMaxNumFaceInfls,
				&pNewMeshContainer->dwNumAttrGroups,
				&pNewMeshContainer->pBufBoneCombos,
				&pNewMeshContainer->pWorkingMesh);

			DWORD dwOldFVF = pNewMeshContainer->pWorkingMesh->GetFVF();
			DWORD dwNewFVF = (dwOldFVF & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
			if (dwNewFVF != dwOldFVF)
			{
				LPD3DXMESH pMeshSetup = nullptr;
				pNewMeshContainer->pWorkingMesh->CloneMeshFVF(pNewMeshContainer->pWorkingMesh->GetOptions(), dwNewFVF, g_pD3DDevice, &pMeshSetup);
				if (pMeshSetup)
				{
					SAFE_RELEASE(pNewMeshContainer->pWorkingMesh);
					pNewMeshContainer->pWorkingMesh = pMeshSetup;
				}

				if (!(dwOldFVF & D3DFVF_NORMAL))
				{
					D3DXComputeNormals(pNewMeshContainer->pWorkingMesh, NULL);
				}
			}

		}
	
		//알 수 없음 (셰이더에서 사용하는거 같음)
		if (pNewMeshContainer->pWorkingMesh)
		{
			D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
			D3DVERTEXELEMENT9* pDeclCur;
			pNewMeshContainer->pWorkingMesh->GetDeclaration(pDecl);

			pDeclCur = pDecl;
			while (pDeclCur->Stream != 0xff)
			{
				if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) &&
					(pDeclCur->UsageIndex == 0))
					pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
				pDeclCur++;
			}

			pNewMeshContainer->pWorkingMesh->UpdateSemantics(pDecl);
		}

	}

	//반환
	(*ppNewMeshContainer) = pNewMeshContainer;
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

HRESULT cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	//캐스팅
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

	//복사된 워킹 메시 제거
	SAFE_RELEASE(pBoneMesh->pWorkingMesh);

	//매트릭스 제거
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_RELEASE(pBoneMesh->pSkinInfo);

	//인접정보 제거
	SAFE_DELETE_ARRAY(pBoneMesh->pAdjacency);
	//원본 메시
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh)

	//임펙트 제거
	SAFE_DELETE(pBoneMesh->pEffects);

	//재질정보 제거
	if (pBoneMesh->pMaterials && pBoneMesh->NumMaterials)
	{
		//텍스쳐 이름 제거
		for (DWORD i = 0; i < pBoneMesh->NumMaterials; ++i)
		{
			SAFE_DELETE_ARRAY(pBoneMesh->pMaterials[i].pTextureFilename);				//
		}

		//재질배열 제거
		SAFE_DELETE_ARRAY(pBoneMesh->pMaterials);																			//갯수
	}

	//제거
	SAFE_DELETE_ARRAY(pBoneMesh->Name);
	delete pBoneMesh;

	return D3D_OK;
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
