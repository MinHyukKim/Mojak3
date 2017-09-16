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
	//����
	ST_BONE* pNewFrame = new ST_BONE;
	cAllocateHierarchy::CopyString(&pNewFrame->Name, Name);

#ifdef CONSOLE_DEBUG_TEST
	if (Name)
	{
		DEBUG_TEXT(Name);
	}
#endif

	//��ȯ
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
		pNewMeshContainer->vecTexture.resize(NumMaterials);
		for (DWORD i = 0; i < NumMaterials; ++i)
		{
			cAllocateHierarchy::CopyString(&pNewMeshContainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);		//�ؽ��� �̸� ����
			//���̶�Ű�� ���� �̸��� ���� �ؽ��Ĵ� Setup����
		}
		pNewMeshContainer->NumMaterials = NumMaterials;																				//����
	}

	//����Ʈ ����
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
	}

	//�������� ����
	if (pAdjacency && NumFaces)
	{
		pNewMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
		memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	}

	// ��Ų���� ����
	if (pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pNewMeshContainer->pSkinInfo = pSkinInfo;
		pNewMeshContainer->pSkinInfo->AddRef();

		//��Ʈ���� �����Ҵ�
		pNewMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIXA16*[dwNumBones];
		pNewMeshContainer->pBoneOffsetMatrices = new D3DXMATRIXA16[dwNumBones];
		//��Ʈ���� ����
		for (int i = 0; i < dwNumBones; i++)
		{
			pNewMeshContainer->ppBoneMatrixPtrs[i] = NULL;
			pNewMeshContainer->pBoneOffsetMatrices[i] = *pSkinInfo->GetBoneOffsetMatrix(i);
		}

		pNewMeshContainer->dwNumPaletteEntries = min(m_dwDefaultPalette, pSkinInfo->GetNumBones());

		if (m_dwNumMaxPalette < pNewMeshContainer->dwNumPaletteEntries) m_dwNumMaxPalette = pNewMeshContainer->dwNumPaletteEntries;
		
		//��ŷ �޽� ���� �� �缳�� (����߰�)
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
	
		//�� �� ���� (���̴����� ����ϴ°� ����)
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

	//��ȯ
	(*ppNewMeshContainer) = pNewMeshContainer;
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

HRESULT cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	//ĳ����
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

	//����� ��ŷ �޽� ����
	SAFE_RELEASE(pBoneMesh->pWorkingMesh);

	//��Ʈ���� ����
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_RELEASE(pBoneMesh->pSkinInfo);

	//�������� ����
	SAFE_DELETE_ARRAY(pBoneMesh->pAdjacency);
	//���� �޽�
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh)

	//����Ʈ ����
	SAFE_DELETE(pBoneMesh->pEffects);

	//�������� ����
	if (pBoneMesh->pMaterials && pBoneMesh->NumMaterials)
	{
		//�ؽ��� �̸� ����
		for (DWORD i = 0; i < pBoneMesh->NumMaterials; ++i)
		{
			SAFE_DELETE_ARRAY(pBoneMesh->pMaterials[i].pTextureFilename);				//
		}

		//�����迭 ����
		SAFE_DELETE_ARRAY(pBoneMesh->pMaterials);																			//����
	}

	//����
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
