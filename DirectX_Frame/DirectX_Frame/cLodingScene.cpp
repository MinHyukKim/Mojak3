#include "stdafx.h"
#include "cLodingScene.h"

#include "cDataLoder.h"
#include "cImage.h"
#include "cFont.h"

cLodingScene::cLodingScene(void)
	: m_pData(nullptr)
	, m_pSprite(nullptr)
	, m_pLoadingImage(nullptr)
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
	m_pFont->Setup(12);
	m_pFont->SetColor(D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 imageData;
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//Ÿ��Ʋ �׸�
	imageData = g_pTexture->GetTextureEx("./Texture/Title.jpg",&m_stLoadingBar);
	m_pLoadingImage = cImage::Create();
	m_pLoadingImage->Setup(m_stLoadingBar, imageData);
	m_matWorldMatrix._41 = rc.right / 2.0f;
	m_matWorldMatrix._42 = rc.bottom / 2.0f;
	m_matWorldMatrix._43 = 1.0f;
	m_matWorldMatrix._11 = (float)rc.right / (float)m_stLoadingBar.Width;
	m_matWorldMatrix._22 = (float)rc.bottom / (float)m_stLoadingBar.Height;
	m_pLoadingImage->SetWorldMatrix(&m_matWorldMatrix);

	//�ε� ������
	D3DXMatrixIdentity(&m_matWorldMatrix);
	imageData = g_pTexture->GetTextureEx("./Texture/loading_bar.dds", &m_stLoadingBar);
	m_pLoadingGaugeImage = cImage::Create();
	m_pLoadingGaugeImage->Setup(m_stLoadingBar, imageData);
	m_matWorldMatrix._41 = rc.right * 0.5f;
	m_matWorldMatrix._42 = rc.bottom * 0.66f;
	m_matWorldMatrix._43 = 0.5f;
	m_pLoadingGaugeImage->SetWorldMatrix(&m_matWorldMatrix);

	//�ε� ��
	imageData = g_pTexture->GetTextureEx("./Texture/loading_bar_color.dds", &m_stLoadingBar);
	m_pLoadingBarImage = cImage::Create();
	m_pLoadingBarImage->Setup(m_stLoadingBar, imageData);
	m_matWorldMatrix._41 = rc.right * 0.5f;
	m_matWorldMatrix._42 = rc.bottom * 0.66f;
	m_matWorldMatrix._43 = 0.0f;
	m_pLoadingBarImage->SetWorldMatrix(&m_matWorldMatrix);

	SAFE_RELEASE(m_pData);
	m_pData = cDataLoder::Create();
	m_pData->RegisterData("./Data/SetupData.txt");
	//�ǹ� ���(�ӽ�)
	m_pData->RegisterBuild("scene_building_tirchonaill_chiefhouse.x");
	m_pData->RegisterBuild("inn.x");
	m_pData->RegisterBuild("farm_appletree_01.x");
	m_pData->RegisterBuild("farm_level02_se_tree_01.x");
	m_pData->RegisterBuild("scene_building_tirchonaill_church.x");
	m_pData->RegisterBuild("smooth_appleTree.x");

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
	//������ ���� ����
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}

	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pData);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pLoadingImage);
	SAFE_RELEASE(m_pLoadingGaugeImage);
	SAFE_RELEASE(m_pLoadingBarImage);
}

void cLodingScene::Update(void)
{
	if (m_pFont)
	{
		//�ε� ������
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		D3DXMatrixIdentity(&m_matWorldMatrix);
		m_matWorldMatrix._41 = rc.right * 0.5f - m_stLoadingBar.Width * (1.0f - m_pData->GetLodingGauge()) * 0.5f;
		m_matWorldMatrix._42 = rc.bottom * 0.66f;
		m_matWorldMatrix._43 = 0.0f;
		m_pLoadingBarImage->SetWorldMatrix(&m_matWorldMatrix);
		m_pLoadingBarImage->SetSize(m_stLoadingBar.Width * m_pData->GetLodingGauge(), m_stLoadingBar.Height);

		//�ε� �޼���
		char szText[256] = {};
		sprintf(szText, "�ε��� %2.2f %%", m_pData->GetLodingGauge() * 100.0f);
		m_pFont->DrawFont(rc.right * 0.45f, rc.bottom * 0.65f, szText);
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

	if (m_pLoadingImage) m_pLoadingImage->Draw(m_pSprite);
	if (m_pLoadingGaugeImage) m_pLoadingGaugeImage->Draw(m_pSprite);
	if (m_pLoadingBarImage) m_pLoadingBarImage->Draw(m_pSprite);
	m_pSprite->End();
	

	SAFE_RENDER(m_pFont);
}

cLodingScene* cLodingScene::Create(void)
{
	cLodingScene* newClass = new cLodingScene;
	newClass->AddRef();
	return newClass;
}

