#include "stdafx.h"
#include "cAllocateHierarchy.h"

void cAllocateHierarchy::Reset(void)
{
	m_dwDefaultPalette = 0;
	m_dwNumMaxPalette = 0;
	m_sFolder.clear();
}

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
	CopyString(&pNewFrame->Name, Name);

	//반환
	(*ppNewFrame) = pNewFrame;
	return D3D_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
	assert(pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH);
	*ppNewMeshContainer = NULL;

	//생성
	ST_BONE_MESH* pNewMeshContainer = new ST_BONE_MESH;
	CopyString(&pNewMeshContainer->Name, Name);
	int NumFaces = 0;

	//재질정보 저장
	if (pMaterials && NumMaterials)
	{
		pNewMeshContainer->pMaterials = new D3DXMATERIAL[NumMaterials];
		pNewMeshContainer->vecTexture.resize(NumMaterials);
		for (DWORD i = 0; i < NumMaterials; ++i)
		{
			pNewMeshContainer->pMaterials[i].pTextureFilename = nullptr;
			memcpy(&pNewMeshContainer->pMaterials[i].MatD3D, &pMaterials[i].MatD3D, sizeof(D3DMATERIAL9));
			CopyString(&pNewMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);		//텍스쳐 이름 복사
			pNewMeshContainer->vecTexture[i] = g_pTexture->GetTexture(pNewMeshContainer->pMaterials[i].pTextureFilename);
		}
		pNewMeshContainer->NumMaterials = NumMaterials;																				//갯수
	}

	//이펙트 저장
	if (pEffectInstances)
	{
		pNewMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
		*pNewMeshContainer->pEffects = *pEffectInstances;
	}

	//워킹 메시복사
	LPD3DXMESH pMesh = pMeshData->pMesh;
	if (pMesh)
	{
		//저장(오리진)
		NumFaces = pMesh->GetNumFaces(); //면의 갯수 (인덱스 버퍼의 3분의 1);
		pNewMeshContainer->MeshData.Type = pMeshData->Type;
		pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), g_pD3DDevice, &pNewMeshContainer->MeshData.pMesh);
		pMesh = pNewMeshContainer->MeshData.pMesh;
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

//HRESULT cAllocateHierarchy::CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin)
//{
//	if (pTextOrigin && ppTextCopy)
//	{
//		int nLength = lstrlen(pTextOrigin) + 1;
//		(*ppTextCopy) = new char[nLength];
//		memcpy(*ppTextCopy, pTextOrigin, nLength * sizeof(char));
//		return D3D_OK;
//	}
//	return E_FAIL;
//}

HRESULT cAllocateHierarchy::CloneFrame(OUT LPD3DXFRAME* ppClone, IN LPD3DXFRAME pOrigin)
{
	//조건 검사
	if (!ppClone || !pOrigin) return E_FAIL;
	//프레임 생성
	if (!(*ppClone)) g_pAllocateHierarchy->CreateFrame(pOrigin->Name, ppClone);

	if (pOrigin->pMeshContainer)
	{

		ST_BONE_MESH* pMeshOrigin = (ST_BONE_MESH*)pOrigin->pMeshContainer;
		ST_BONE_MESH* pMeshClone = new ST_BONE_MESH;
		pMeshClone->dwMaxNumFaceInfls = pMeshOrigin->dwMaxNumFaceInfls;
		pMeshClone->dwNumAttrGroups = pMeshOrigin->dwNumAttrGroups;
		pMeshClone->dwNumPaletteEntries = pMeshOrigin->dwNumPaletteEntries;
		pMeshClone->MeshData.Type = pMeshOrigin->MeshData.Type;
		CopyString(&pMeshClone->Name, pMeshOrigin->Name); //pMeshClone->Name = pMeshOrigin->Name;
		if (pMeshOrigin->MeshData.pMesh)
		{
			//pMeshClone->MeshData = pMeshOrigin->MeshData;
			LPD3DXMESH pMesh = pMeshOrigin->MeshData.pMesh;
			pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), g_pD3DDevice, &pMeshClone->MeshData.pMesh);

			//pMeshClone->pAdjacency = pMeshOrigin->pAdjacency;
			DWORD NumFaces = pMesh->GetNumFaces();
			pMeshClone->pAdjacency = new DWORD[NumFaces * 3];
			memcpy(pMeshClone->pAdjacency, pMeshOrigin->pAdjacency, 3 * NumFaces * sizeof(DWORD));
		}
		if (pMeshOrigin->pSkinInfo)
		{
			//pMeshClone->pSkinInfo;
			DWORD dwNumBones = pMeshOrigin->pSkinInfo->GetNumBones();
			pMeshOrigin->pSkinInfo->Clone(&pMeshClone->pSkinInfo);

			//pMeshClone->ppBoneMatrixPtrs;
			//pMeshClone->pBoneOffsetMatrices = pMeshOrigin->pBoneOffsetMatrices;
			pMeshClone->ppBoneMatrixPtrs = new D3DXMATRIXA16*[dwNumBones];
			pMeshClone->pBoneOffsetMatrices = new D3DXMATRIXA16[dwNumBones];
			for (int i = 0; i < dwNumBones; i++)
			{
				pMeshClone->ppBoneMatrixPtrs[i] = NULL;
				pMeshClone->pBoneOffsetMatrices[i] = *pMeshClone->pSkinInfo->GetBoneOffsetMatrix(i);
			}
			//pMeshClone->pBufBoneCombos = pMeshOrigin->pBufBoneCombos;
			if (pMeshOrigin->pBufBoneCombos)
			{
				pMeshClone->pBufBoneCombos = pMeshOrigin->pBufBoneCombos;
				pMeshOrigin->pBufBoneCombos->AddRef();
			}

			//pMeshClone->pEffects = pMeshOrigin->pEffects;
			pMeshClone->pEffects = new D3DXEFFECTINSTANCE;
			*pMeshClone->pEffects = *pMeshOrigin->pEffects;
		}
		if (pMeshOrigin->pWorkingMesh)
		{
			//pMeshClone->pWorkingMesh = pMeshOrigin->pWorkingMesh;
			LPD3DXMESH pMesh = pMeshOrigin->pWorkingMesh;
			pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), g_pD3DDevice, &pMeshClone->pWorkingMesh);

		}
		if (pMeshOrigin->NumMaterials)
		{
			pMeshClone->NumMaterials = pMeshOrigin->NumMaterials;
			pMeshClone->pMaterials = new D3DXMATERIAL[pMeshClone->NumMaterials];
			pMeshClone->vecTexture.resize(pMeshClone->NumMaterials);
			for (DWORD i = 0; i < pMeshClone->NumMaterials; i++)
			{
				//pMeshClone->pMaterials = pMeshOrigin->pMaterials;
				pMeshClone->pMaterials[i].pTextureFilename = nullptr;
				memcpy(&pMeshClone->pMaterials[i].MatD3D, &pMeshOrigin->pMaterials[i].MatD3D, sizeof(D3DMATERIAL9));
				CopyString(&pMeshClone->pMaterials[i].pTextureFilename, pMeshOrigin->pMaterials[i].pTextureFilename);
				//pMeshClone->vecTexture = pMeshOrigin->vecTexture;
				pMeshClone->vecTexture[i] = g_pTexture->GetTexture(pMeshClone->pMaterials[i].pTextureFilename);
			}
		}

		//pMeshClone->pCurrentBoneMatrices;
		//pMeshClone->pNextMeshContainer = pMeshOrigin->pNextMeshContainer;
		(*ppClone)->pMeshContainer = pMeshClone;
	}
	return S_OK;
}

bool cAllocateHierarchy::ChangeFrame(LPD3DXFRAME* ppRoot, LPD3DXFRAME pOrigin)
{
	//예외처리
	if (!ppRoot || !(*ppRoot)) return false;

	//이름으로 찾기
	if (!strcmp((*ppRoot)->Name, pOrigin->Name))
	{
		//클론 생성
		LPD3DXFRAME pClone = nullptr;
		this->CloneFrame(&pClone, pOrigin);
		//링크 연결
		pClone->pFrameFirstChild = (*ppRoot)->pFrameFirstChild;
		pClone->pFrameSibling = (*ppRoot)->pFrameSibling;
		//링크 해제
		(*ppRoot)->pFrameFirstChild = nullptr;
		(*ppRoot)->pFrameSibling = nullptr;
		//기본 바디 제거
		D3DXFrameDestroy(*ppRoot, g_pAllocateHierarchy);
		//클론 연결
		*ppRoot = pClone;
		// 찾기 종료
		return true;
	}

	//형제 노드만 찾으러 다니기
	if ((*ppRoot)->pFrameSibling)
	{
		if (ChangeFrame(&(*ppRoot)->pFrameSibling, pOrigin)) return true;
	}
	//if ((*ppRoot)->pFrameFirstChild); 자식은 찾지 않는다.

	//찾기 실패
	return false;
}

HRESULT cAllocateHierarchy::CloneHierarchy(OUT LPD3DXFRAME* ppRoot, IN LPD3DXFRAME pOrigin)
{
	if (!ppRoot || !pOrigin) return E_FAIL;							//예외처리
	if ((*ppRoot)) D3DXFrameDestroy(*ppRoot, g_pAllocateHierarchy); // 0xcdcdcdcd 는 걸리지말자!
	this->CloneFrame(ppRoot, pOrigin);								//복사
	//형제
	if (pOrigin->pFrameSibling)
	{
		this->CloneHierarchy(&(*ppRoot)->pFrameSibling, pOrigin->pFrameSibling);
	}
	//자식
	if (pOrigin->pFrameFirstChild)
	{
		CloneHierarchy(&(*ppRoot)->pFrameFirstChild, pOrigin->pFrameFirstChild);
	}

	return S_OK;
}
