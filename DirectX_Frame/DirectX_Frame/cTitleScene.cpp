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

void cTitleScene::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == cTitleScene::E_MAPTOOL_BUTTON)
	{
		m_pNextScene = new string("cMapToolScene");
	}
	else if (pSender->GetTag() == cTitleScene::E_START_BUTTON)
	{
		g_pObjectManager->RegisterPlayer(nullptr);
		m_pNextScene = new string("cUiCustomizingScene");
		DEBUG_TEXT("시작버튼");
	}
	else if (pSender->GetTag() == cTitleScene::E_CONTINUE_BUTTON)
	{
		DEBUG_TEXT("이어하기 버튼");
	}
	else if (pSender->GetTag() == cTitleScene::E_EXIT_BUTTON)
	{
		DestroyWindow(g_hWnd);

		DEBUG_TEXT("종료버튼");
	}

}

cTitleScene::cTitleScene(void)
	: m_pCamera(NULL)
	, m_pMapTerrain(NULL)
	, m_pBuild(NULL)
	, m_pTexture(NULL)
	, m_pSkybox(nullptr)
	, m_pSprite(nullptr)
	, m_pTitleImage(nullptr)
	, m_pUIRoot(NULL)
	, m_pNextScene(NULL)

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
		(float)rc.bottom - rootBase->stImageInfo.Height - (float)rc.bottom / 20);
	m_pUIRoot = rootBase;

	m_pMaptoolButton = cUIButton::Create();
	m_pMaptoolButton->SetTexture("UI/btn-maptool-up.png",
		"UI/btn-maptool-over.png",
		"UI/btn-maptool-down.png");
	m_pMaptoolButton->SetPosition(rootBase->stImageInfo.Width / 2- m_pMaptoolButton->GetSize().fWidth/2, 30);
	m_pMaptoolButton->SetDelegate(this);
	m_pMaptoolButton->SetTag(cTitleScene::E_MAPTOOL_BUTTON);
	m_pUIRoot->AddChild(m_pMaptoolButton);

	m_pStartButton = cUIButton::Create();
	m_pStartButton->SetTexture("UI/btn-start-up.png",
		"UI/btn-start-over.png",
		"UI/btn-start-down.png");
	m_pStartButton->SetPosition(rootBase->stImageInfo.Width / 2 - m_pStartButton->GetSize().fWidth / 2, 
		m_pMaptoolButton->GetPosition().y + m_pMaptoolButton->GetSize().fHeight+ 15);
	m_pStartButton->SetDelegate(this);
	m_pStartButton->SetTag(cTitleScene::E_START_BUTTON);
	m_pUIRoot->AddChild(m_pStartButton);

	m_pContinueButton = cUIButton::Create();
	m_pContinueButton->SetTexture("UI/btn-continue-up.png",
		"UI/btn-continue-over.png",
		"UI/btn-continue-down.png");
	m_pContinueButton->SetPosition(rootBase->stImageInfo.Width / 2 - m_pContinueButton->GetSize().fWidth / 2, 
		m_pStartButton->GetPosition().y + m_pStartButton->GetSize().fHeight + 15);
	m_pContinueButton->SetDelegate(this);
	m_pContinueButton->SetTag(cTitleScene::E_CONTINUE_BUTTON);
	m_pUIRoot->AddChild(m_pContinueButton);

	m_pExitButton = cUIButton::Create();
	m_pExitButton->SetTexture("UI/btn-exit-up.png",
		"UI/btn-exit-over.png",
		"UI/btn-exit-down.png");
	m_pExitButton->SetPosition(rootBase->stImageInfo.Width / 2 - m_pExitButton->GetSize().fWidth / 2, 
		m_pContinueButton->GetPosition().y + m_pContinueButton->GetSize().fHeight + 15);
	m_pExitButton->SetDelegate(this);
	m_pExitButton->SetTag(cTitleScene::E_EXIT_BUTTON);
	m_pUIRoot->AddChild(m_pExitButton);

	
	g_pSoundManager->Play("titleBGM");
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
	SAFE_DELETE(m_pNextScene);

	g_pSoundManager->Stop("titleBGM");

}

void cTitleScene::Update(void)
{
	if (m_pUIRoot) m_pUIRoot->Update();

	if (m_pNextScene) g_pSceneManager->ChangeScene(m_pNextScene->c_str());
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

