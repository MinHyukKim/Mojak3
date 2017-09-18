#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh(char * szFolder, char * szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
	, m_isCurrentTrack(false)
{
	cSkinnedMesh* pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);

//	g_pAllocateHierarchy->CloneHierarchy((LPD3DXFRAME*)&m_pRootFrame, pSkinnedMesh->m_pRootFrame);
//	this->SetupBoneMatrixPtrs(m_pRootFrame);
	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	pSkinnedMesh->SetTrack(true);

	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;

	SAFE_RELEASE(m_pEffect);
	m_pEffect = pSkinnedMesh->m_pEffect;
	
	if (pSkinnedMesh->m_pAnimController)
	{
		pSkinnedMesh->m_pAnimController->CloneAnimationController(
			pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
			pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
			pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
			pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
			&m_pAnimController);
	}
}

cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_isCurrentTrack(false)
{
}

void cSkinnedMesh::Load(char * szFolder, char * szFilename)
{
	g_pAllocateHierarchy->Reset();

	SAFE_RELEASE(m_pEffect);
	m_pEffect = LoadEffect("MultiAnimation.hpp");
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	g_pAllocateHierarchy->setFolder(szFolder);
	g_pAllocateHierarchy->setDefaultPaletteSize(nPaletteSize);

	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);
	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		g_pAllocateHierarchy,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	m_dwWorkingPaletteSize = g_pAllocateHierarchy->getMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];

	if (m_pmWorkingPalette == NULL) m_dwWorkingPaletteSize = 0;

	if (m_pRootFrame)
	{
		DEBUG_TEXT("계층구조 : " << szFolder << szFilename);
		SetupBoneMatrixPtrs(m_pRootFrame);
		//D3DXMatrixRotationX(&m_pRootFrame->TransformationMatrix, -D3DX_PI / 2.0f);
	}
}

LPD3DXEFFECT cSkinnedMesh::LoadEffect(char * szFilename)
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

void cSkinnedMesh::_Update(ST_BONE * pCurrent, D3DXMATRIX * pmatParent)
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix = pCurrent->CombinedTransformationMatrix *(*pmatParent);
	}
	//형제 노드가 있으면 업데이트를 부르고 부모 매트리스를 줌.
	if (pCurrent->pFrameSibling)
	{
		_Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}
	//자식 노드가 있으면 업데이트를 부르고 자기 매트리스를 줌.
	if (pCurrent->pFrameFirstChild)
	{
		_Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cSkinnedMesh::_Render(ST_BONE * pBone)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);


		g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
		g_pD3DDevice->SetMaterial(&(pBoneMesh->pMaterials->MatD3D));
		g_pD3DDevice->SetTexture(0, g_pTexture->GetTexture(pBoneMesh->pMaterials->pTextureFilename));
		pBoneMesh->pWorkingMesh->DrawSubset(0);
	}

	if (pBone->pFrameFirstChild)
	{
		_Render((ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		_Render((ST_BONE*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh::ShaderRender(ST_BONE * pBone)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for (DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib)
		{
			// set each transform into the palette
			for (DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry)
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if (dwMatrixIndex != UINT_MAX)
				{
					m_pmWorkingPalette[dwPalEntry] = pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] * (*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray("amPalette", m_pmWorkingPalette, pBoneMesh->dwNumPaletteEntries);

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));		//빛의 밝기
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));	//빛의 위치
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));					//카메라 위치
			//m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			//m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			m_pEffect->SetVector("vMaterialAmbient", (D3DXVECTOR4*)&pBoneMesh->pMaterials[dwAttrib].MatD3D.Ambient);
			m_pEffect->SetVector("vMaterialDiffuse", (D3DXVECTOR4*)&pBoneMesh->pMaterials[dwAttrib].MatD3D.Diffuse);

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

			// set the technique we use to draw
			m_pEffect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin(&uiPasses, 0);
			for (uiPass = 0; uiPass < uiPasses; ++uiPass)
			{
				m_pEffect->BeginPass(uiPass);
				
				pBoneMesh->pWorkingMesh->DrawSubset(dwAttrib);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
	{
		ShaderRender((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		ShaderRender((ST_BONE*)pBone->pFrameFirstChild);
	}

}

void cSkinnedMesh::SetupBoneMatrixPtrs(ST_BONE * pBone)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
#ifdef CONSOLE_DEBUG_TEST
	if (pBone->Name) DEBUG_TEXT_EX("본 이름 : " << pBone->Name)
	else DEBUG_TEXT_EX("이름없음");
#endif
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if (szBoneName == NULL || strlen(szBoneName) == 0) continue;

				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
#ifdef CONSOLE_DEBUG_TEST
			if (pBone->pMeshContainer->Name) DEBUG_TEXT_EX("메쉬 이름 : " << pBone->pMeshContainer->Name);
			DEBUG_ADD_COUNT();
			for (DWORD i = 0; i < pBoneMesh->NumMaterials; i++)
			{
				LPD3DXMATERIAL pMaterial = &pBoneMesh->pMaterials[i];
				DEBUG_TEXT_EX("텍스처 이름 : " << pMaterial->pTextureFilename << '(' << pMaterial->MatD3D.Diffuse.r << ", " << pMaterial->MatD3D.Diffuse.g << ", " << pMaterial->MatD3D.Diffuse.b << ", " << pMaterial->MatD3D.Diffuse.a << ')')
			}
			DEBUG_SUB_COUNT();
#endif // CONSOLE_DEBUG_TEST
		}
	}
	//재귀적으로 모든 프레임에 대해서 실행.
	DEBUG_ADD_COUNT();
//	DEBUG_TEXT_EX('{');
	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}
//	DEBUG_TEXT_EX('}');
	DEBUG_SUB_COUNT();

	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}

}

void cSkinnedMesh::Destroy()
{
	//계별적으로 관리함
	if (m_pRootFrame)
	{
		D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, g_pAllocateHierarchy);
		m_pRootFrame = nullptr;
	}

	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}

HRESULT cSkinnedMesh::CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin)
{
	if (pTextOrigin && ppTextCopy)
	{
		SAFE_DELETE_ARRAY(*ppTextCopy);
		int nLength = lstrlen(pTextOrigin) + 1;
		(*ppTextCopy) = new char[nLength];
		memcpy(*ppTextCopy, pTextOrigin, nLength * sizeof(char));
		return D3D_OK;
	}
	return E_FAIL;
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);
//	if (m_pRootFrame)
//	{
//		D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, g_pAllocateHierarchy);
//		m_pRootFrame = nullptr;
//	}
}

void cSkinnedMesh::UpdateAndRender()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	this->UpdateAndRender(&mat);
}

void cSkinnedMesh::UpdateAndRender(LPD3DXMATRIX pMatrix)
{
	if (m_isCurrentTrack && m_pAnimController)
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	}

	if (m_pRootFrame)
	{
		_Update(m_pRootFrame, pMatrix);
		//_Render(m_pRootFrame);
		ShaderRender(m_pRootFrame); //쉐이더렌더 적용
	}
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	if (!m_pAnimController)
		return;
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetBlendingAnimation(int nAnimationKey, float fTravalTime)
{
	//미구현
}

bool cSkinnedMesh::FrameClone(OUT LPD3DXFRAME* ppClone, IN LPD3DXFRAME pOrigin)
{
	if (!ppClone || pOrigin) return false;

	return true;
}

DWORD cSkinnedMesh::AddAnimationSet(LPD3DXANIMATIONSET pAnimation)
{
	if (!m_pAnimController)
	{
		assert(false && "애니메이션 컨트롤러가 존재하지 않습니다.");
//		D3DXCreateAnimationController(24, 1, 2, 32, &m_pAnimController); // 실패작
		return 0;
	}

	//애니메이션 컨트롤러 재설정
	if (1 > m_pAnimController->GetMaxNumAnimationSets() - m_pAnimController->GetNumAnimationSets())
	{
		int count = m_pAnimController->GetMaxNumAnimationSets();
		LPD3DXANIMATIONCONTROLLER pController;
		m_pAnimController->CloneAnimationController(
			m_pAnimController->GetMaxNumAnimationOutputs(),
			count ? count * 2 : count + 1,
			2, 32, &pController);
		SAFE_RELEASE(m_pAnimController);
		m_pAnimController = pController;
	}

	//애니메이션 등록
	m_pAnimController->RegisterAnimationSet(pAnimation);
	return m_pAnimController->GetNumAnimationSets() - 1;
}

void cSkinnedMesh::SetAnimationController(LPD3DXANIMATIONCONTROLLER pAnimationController)
{
	SAFE_RELEASE(m_pAnimController);
	m_pAnimController = pAnimationController;
	m_pAnimController->AddRef();
}

void cSkinnedMesh::SetRandomTrackPosition()
{
	if (!m_pAnimController) return;
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame, D3DXMATRIX * pPMat)
{
	//	// pCurrentBoneMatrices 를 계산하시오
	//// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
	//assert(pFrame);

	//if (pPMat == NULL)
	//{
	//	pPMat = new D3DXMATRIX;
	//	D3DXMatrixIdentity(pPMat);
	//}

	//ST_BONE* pBone = (ST_BONE*)pFrame;
	//if(pBone->pMeshContainer)
	//{
	//	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	//	if(pBoneMesh->pSkinInfo)
	//	{
	//		LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
	//		DWORD dwNumBones = pSkinInfo->GetNumBones();
	//		for (DWORD i = 0; i < dwNumBones; ++i)
	//		{
	//			pBoneMesh->pCurrentBoneMatrices[i] = 
	//				pBoneMesh->pBoneOffsetMatrices[i] *
	//				*(pBoneMesh->ppBoneMatrixPtrs[i]) * *pPMat;
	//		}

	//		BYTE* src = NULL;
	//		BYTE* dest = NULL;

	//		pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
	//		pBoneMesh->pWorkMesh->LockVertexBuffer( 0, (void**)&dest );

	//		//pWorkMesh을 업데이트 시켜준다.
	//		pSkinInfo->UpdateSkinnedMesh(
	//			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

	//		pBoneMesh->pWorkMesh->UnlockVertexBuffer();
	//		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	//	}
	//}

	////재귀적으로 모든 프레임에 대해서 실행.
	//if(pFrame->pFrameFirstChild)
	//{
	//	UpdateSkinnedMesh(pFrame->pFrameFirstChild, pPMat);
	//}

	//if(pFrame->pFrameSibling)
	//{
	//	UpdateSkinnedMesh(pFrame->pFrameSibling, pPMat);
	//}


}

void cSkinnedMesh::FrameChange(LPD3DXFRAME pFrame)
{
	(ST_BONE*)g_pAllocateHierarchy->ChangeFrame((LPD3DXFRAME*)&m_pRootFrame, pFrame);
	this->SetupBoneMatrixPtrs(m_pRootFrame);
}

void cSkinnedMesh::SetTextureColor(LPCSTR szTextureName, LPD3DXCOLOR pColor)
{
	cSkinnedMesh::SetTextureColor(m_pRootFrame, szTextureName, pColor);
}

void cSkinnedMesh::SetTextureColor(LPCSTR szTextureName, LPD3DXMATRIX pColor)
{
	cSkinnedMesh::SetTextureColor(m_pRootFrame, szTextureName, pColor);
}

void cSkinnedMesh::SetTextureDiffuse(LPCSTR szTextureName, LPD3DXCOLOR pDiffuse)
{
	cSkinnedMesh::SetTextureDiffuse(m_pRootFrame, szTextureName, pDiffuse);
}

void cSkinnedMesh::SetTextureAmbient(LPCSTR szTextureName, LPD3DXCOLOR pAmbient)
{
	cSkinnedMesh::SetTextureAmbient(m_pRootFrame, szTextureName, pAmbient);
}

void cSkinnedMesh::SetTextureSpecular(LPCSTR szTextureName, LPD3DXCOLOR pSpecular)
{
	cSkinnedMesh::SetTextureSpecular(m_pRootFrame, szTextureName, pSpecular);
}

void cSkinnedMesh::SetTextureChange(LPCSTR szPrevTextureName, LPCSTR szNextTextureName)
{
	cSkinnedMesh::SetTextureChange(m_pRootFrame, szPrevTextureName, szNextTextureName);
}

void cSkinnedMesh::SetTextureDiffuse(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pDiffuse)
{
	if (!pRoot) return;
	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szTextureName))
			{
				//색상변경
				pMaterial->MatD3D.Diffuse = *pDiffuse;
			}
		}
	}

	//자식 찾기
	if (pRoot->pFrameFirstChild)
	{
		cSkinnedMesh::SetTextureDiffuse(pRoot->pFrameFirstChild, szTextureName, pDiffuse);
	}

	//형제 찾기
	if (pRoot->pFrameSibling)
	{
		cSkinnedMesh::SetTextureDiffuse(pRoot->pFrameSibling, szTextureName, pDiffuse);
	}
}

void cSkinnedMesh::SetTextureAmbient(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pAmbient)
{
	if (!pRoot) return;
	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szTextureName))
			{
				//색상변경
				pMaterial->MatD3D.Ambient = *pAmbient;
			}
		}
	}

	//자식 찾기
	if (pRoot->pFrameFirstChild)
	{
		cSkinnedMesh::SetTextureAmbient(pRoot->pFrameFirstChild, szTextureName, pAmbient);
	}

	//형제 찾기
	if (pRoot->pFrameSibling)
	{
		cSkinnedMesh::SetTextureAmbient(pRoot->pFrameSibling, szTextureName, pAmbient);
	}
}

void cSkinnedMesh::SetTextureSpecular(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pSpecular)
{
	if (!pRoot) return;

	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szTextureName))
			{
				//색상변경
				pMaterial->MatD3D.Specular = *pSpecular;
			}
		}
	}

	//자식 찾기
	if (pRoot->pFrameFirstChild)
	{
		cSkinnedMesh::SetTextureSpecular(pRoot->pFrameFirstChild, szTextureName, pSpecular);
	}

	//형제 찾기
	if (pRoot->pFrameSibling)
	{
		cSkinnedMesh::SetTextureSpecular(pRoot->pFrameSibling, szTextureName, pSpecular);
	}
}

void cSkinnedMesh::SetTextureColor(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXCOLOR pColor)
{
	if (!pRoot) return;
	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szTextureName))
			{
				//색상변경
				pMaterial->MatD3D.Ambient = *pColor;
				pMaterial->MatD3D.Diffuse = *pColor;
				pMaterial->MatD3D.Specular = *pColor;
			}
		}
	}

	//자식 찾기
	if (pRoot->pFrameFirstChild)
	{
		cSkinnedMesh::SetTextureColor(pRoot->pFrameFirstChild, szTextureName, pColor);
	}

	//형제 찾기
	if (pRoot->pFrameSibling)
	{
		cSkinnedMesh::SetTextureColor(pRoot->pFrameSibling, szTextureName, pColor);
	}
}

void cSkinnedMesh::SetTextureColor(LPD3DXFRAME pRoot, LPCSTR szTextureName, LPD3DXMATRIX pColor)
{
	if (!pRoot) return;
	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szTextureName))
			{
				//색상변경
				pMaterial->MatD3D.Ambient = D3DXCOLOR(pColor->_11, pColor->_12, pColor->_13, pColor->_14);
				pMaterial->MatD3D.Diffuse = D3DXCOLOR(pColor->_21, pColor->_22, pColor->_23, pColor->_24);
				pMaterial->MatD3D.Specular = D3DXCOLOR(pColor->_31, pColor->_32, pColor->_33, pColor->_34);
			}
		}
	}
}

void cSkinnedMesh::SetTextureChange(LPD3DXFRAME pRoot, LPCSTR szPrevTextureName, LPCSTR szNextTextureName)
{
	if (!pRoot || !strcmp(szPrevTextureName, szNextTextureName)) return;
	if (pRoot->pMeshContainer)
	{
		for (DWORD i = 0; i < pRoot->pMeshContainer->NumMaterials; i++)
		{
			LPD3DXMATERIAL pMaterial = &pRoot->pMeshContainer->pMaterials[i];
			//메트리얼->이름 == 찾는이름
			if (pMaterial && !strcmp(pMaterial->pTextureFilename, szPrevTextureName))
			{
				cSkinnedMesh::CopyString(&pMaterial->pTextureFilename, szNextTextureName);
				((ST_BONE_MESH*)pRoot->pMeshContainer)->vecTexture[i] = g_pTexture->GetTexture(szNextTextureName);
			}
		}
	}

	//자식 찾기
	if (pRoot->pFrameFirstChild)
	{
		cSkinnedMesh::SetTextureChange(pRoot->pFrameFirstChild, szPrevTextureName, szNextTextureName);
	}

	//형제 찾기
	if (pRoot->pFrameSibling)
	{
		cSkinnedMesh::SetTextureChange(pRoot->pFrameSibling, szPrevTextureName, szNextTextureName);
	}
}

void cSkinnedMesh::AddTexture(LPD3DXFRAME pRoot, LPCSTR szFrameName, LPCSTR szTextureName)
{
	if (!pRoot) return;
	//프레임 찾기
	ST_BONE_MESH* pFrame = (ST_BONE_MESH*)D3DXFrameFind(pRoot, szFrameName);
	if (!pFrame) return;

	//중복확인
	for (DWORD i = 0; i < pFrame->NumMaterials; i++)
	{
		if (strcmp(pFrame->pMaterials[i].pTextureFilename, szTextureName)) continue;
		return;
	}

	//얇은 복사
	LPD3DXMATERIAL pMaterials = new D3DXMATERIAL[pFrame->NumMaterials + 1];
	for (size_t i = 0; i < pFrame->NumMaterials; i++) pMaterials[i] = pFrame->pMaterials[i];

	//메트리얼 복사
	CopyString(&pMaterials[pFrame->NumMaterials].pTextureFilename, szTextureName);
	ZeroMemory(&pMaterials[pFrame->NumMaterials].MatD3D, sizeof(D3DMATERIAL9));
	pMaterials[pFrame->NumMaterials].MatD3D.Ambient = pMaterials[pFrame->NumMaterials].MatD3D.Diffuse =
		pMaterials[pFrame->NumMaterials].MatD3D.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SAFE_DELETE_ARRAY(pFrame->pMaterials);
	pFrame->pMaterials = pMaterials;

	//텍스쳐 추가
	pFrame->vecTexture.push_back(g_pTexture->GetTexture(szTextureName));

	//인덱스 추가
	++pFrame->NumMaterials;
}

