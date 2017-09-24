#include "stdafx.h"
#include "cLodingScene.h"

#include "cDataLoder.h"
#include "cImage.h"
#include "cFont.h"

cLodingScene::cLodingScene(void)
	: m_pData(nullptr)
	, m_pSprite(nullptr)
	, m_pLodingImage(nullptr)
	, m_pFont(nullptr)
	, m_pThread(nullptr)
	, m_pLoadingGaugeImage(nullptr)
	, m_pLoadingBarImage(nullptr)
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

	m_pFont = cFont::Create();
	m_pFont->Setup();
	m_pFont->SetColor(D3DCOLOR_XRGB(255, 255, 255));

	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 imageData;
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	imageData = g_pTexture->GetTextureEx("./Texture/Title.jpg",&imageInfo);
	m_pLodingImage = cImage::Create();
	m_pLodingImage->Setup(imageInfo, imageData);
	m_matWorldMatrix._41 = rc.right / 2.0f;
	m_matWorldMatrix._42 = rc.bottom / 2.0f;
	m_matWorldMatrix._11 = (float)rc.right / (float)imageInfo.Width;
	m_matWorldMatrix._22 = (float)rc.bottom / (float)imageInfo.Height;
	m_pLodingImage->SetWorldMatrix(&m_matWorldMatrix);

	//로딩
	D3DXMatrixIdentity(&m_matWorldMatrix);
	imageData = g_pTexture->GetTextureEx("./Texture/loading_bar.dds", &imageInfo);
	m_pLoadingGaugeImage = cImage::Create();
	m_pLoadingGaugeImage->Setup(imageInfo, imageData);
	m_matWorldMatrix._41 = rc.right / 2.0f;
	m_matWorldMatrix._42 = rc.bottom / 2.0f;
	m_pLoadingGaugeImage->SetWorldMatrix(&m_matWorldMatrix);

	SAFE_RELEASE(m_pData);
	m_pData = cDataLoder::Create();
	m_pData->RegisterData("./Data/SetupData.txt");

	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
	}
	m_pThread = new thread(&cDataLoder::LoaderDataLoop, m_pData);
	return S_OK;
}

void cLodingScene::Reset(void)
{
	//쓰레드 먼저 해제
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}

	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pData);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pLodingImage);
	SAFE_RELEASE(m_pLoadingGaugeImage);
	SAFE_RELEASE(m_pLoadingBarImage);
}

void cLodingScene::Update(void)
{
	if (m_pFont)
	{
		char szText[256] = {};
		sprintf(szText, "로딩중 %2.2f %%", m_pData->GetLodingGauge() * 100.0f);
		m_pFont->DrawFont(500, 250, szText);
	}
	if (m_pData && m_pData->GetLodingGauge() > 1.0f - FLT_EPSILON)
	{
		this->Render();
		g_pSceneManager->ChangeScene(NEXT_SCENE);
	}
}

void cLodingScene::Render(void)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (m_pLoadingGaugeImage) m_pLoadingGaugeImage->Draw(m_pSprite);

	//if (m_pLodingImage) m_pLodingImage->Draw(m_pSprite);
	m_pSprite->End();
	

	SAFE_RENDER(m_pFont);
}

cLodingScene* cLodingScene::Create(void)
{
	cLodingScene* newClass = new cLodingScene;
	newClass->AddRef();
	return newClass;
}

