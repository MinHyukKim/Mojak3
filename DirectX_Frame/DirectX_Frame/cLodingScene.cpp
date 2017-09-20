#include "stdafx.h"
#include "cLodingScene.h"

#include "cDataLoder.h"
#include "cImage.h"

cLodingScene::cLodingScene(void)
	: m_pData(nullptr)
	, m_pSprite(nullptr)
	, m_pLodingImage(nullptr)
{
	D3DXMatrixIdentity(&m_matWorldMatrix);
}

cLodingScene::~cLodingScene(void)
{
	this->Reset();
}

HRESULT cLodingScene::Setup(void)
{
	SAFE_RELEASE(m_pSprite);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//m_pTexture = ;
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 imageData;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	imageData = g_pTexture->GetTextureEx("./Texture/Title.jpg",&imageInfo);

	m_pLodingImage = cImage::Create();
	m_pLodingImage->Setup(imageInfo, imageData);
	m_pLodingImage->SetSize(rc.right, rc.bottom);
	//m_matWorldMatrix._41 = rc.right / 2.0f;

	SAFE_RELEASE(m_pData);
	m_pData = cDataLoder::Create();
	m_pData->RegisterData("./Data/SetupData.txt");

	InitializeCriticalSection(&m_cs);
	DWORD dwThID;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)m_pData->LoadCallBack, m_pData, NULL, &dwThID));
	return S_OK;
}

void cLodingScene::Reset(void)
{
	SAFE_RELEASE(m_pData);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pLodingImage);
}

void cLodingScene::Update(void)
{
	if (m_pData && m_pData->GetLodingGauge() < 1.0f)
	{

	}
	else
	{
		g_pSceneManager->ChangeScene("cChareterCustomScene");
	}
}

void cLodingScene::Render(void)
{
	m_pSprite->SetTransform(&m_matWorldMatrix);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (m_pLodingImage) m_pLodingImage->Draw(m_pSprite);

	m_pSprite->End();
}

cLodingScene* cLodingScene::Create(void)
{
	cLodingScene* newClass = new cLodingScene;
	newClass->AddRef();
	return newClass;
}

