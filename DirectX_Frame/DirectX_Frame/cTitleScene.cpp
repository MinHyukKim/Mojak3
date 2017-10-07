#include "stdafx.h"
#include "cTitleScene.h"

#include "cCamera.h"
#include "cMapTerrain.h"
#include "cPlayer.h"

#include "cImage.h"
#include "cFont.h"

//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

//테스트용
#include "cBuilding.h"
#include "cSkybox.h"

cTitleScene::cTitleScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pBuild(NULL)
	, m_pTexture(NULL)
	, m_pSkybox(nullptr)
	, m_pSprite(nullptr)
	, m_pTitleImage(nullptr)
	, m_pUIRoot(NULL)

{
	D3DXMatrixIdentity(&m_matWorldMatrix);
}

cTitleScene::~cTitleScene(void)
{
	this->Reset();

}

HRESULT cTitleScene::Setup(void)
{
	SAFE_RELEASE(m_pSprite);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	LPDIRECT3DTEXTURE9 imageData;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//타이틀 그림
	imageData = g_pTexture->GetTextureEx("./Texture/fs_title.png", &m_stImageInfo);
	SAFE_RELEASE(m_pTitleImage);
	m_pTitleImage = cImage::Create();
	m_pTitleImage->Setup(m_stImageInfo, imageData);
	m_matWorldMatrix._41 = rc.right / 2.0f;
	m_matWorldMatrix._42 = rc.bottom / 2.0f;
	m_matWorldMatrix._43 = 1.0f;
	m_matWorldMatrix._11 = (float)rc.right / (float)m_stImageInfo.Width;
	m_matWorldMatrix._22 = (float)rc.bottom / (float)m_stImageInfo.Height;
	m_pTitleImage->SetWorldMatrix(&m_matWorldMatrix);

	//UI세팅
	rootBase = cUIImageView::Create();
	rootBase->SetTexture("UI/test_pannel.png");
	rootBase->SetPosition((float)rc.right/2-rootBase->stImageInfo.Width/2 , 
		(float)rc.bottom/2 - rootBase->stImageInfo.Height / 2 + (float)rc.bottom / 4);

	m_pUIRoot = rootBase;







	return S_OK;
}

void cTitleScene::Reset(void)
{
	SAFE_RELEASE(m_pCamera);
	//테스트용
	SAFE_RELEASE(m_pMapTerrain);
	SAFE_RELEASE(m_pSkybox);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTitleImage);
	//g_pMapObjectManager->Destroy();
	SAFE_RELEASE(m_pUIRoot);


}

void cTitleScene::Update(void)
{
	if (m_pUIRoot) m_pUIRoot->Update();


}

void cTitleScene::Render(void)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (m_pTitleImage) m_pTitleImage->Draw(m_pSprite);

	if (m_pUIRoot) m_pUIRoot->Render(m_pSprite);

	m_pSprite->End();

}

cTitleScene* cTitleScene::Create(void)
{
	cTitleScene* newClass = new cTitleScene;
	newClass->AddRef();
	return newClass;
}

