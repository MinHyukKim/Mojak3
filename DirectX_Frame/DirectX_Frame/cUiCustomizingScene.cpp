
#include "stdafx.h"
#include "cUiCustomizingScene.h"
//폰트 용
#include "cFont.h"
//ui
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
//플레이어
#include "cPlayer.h"
#include "cCamera.h"

enum
{
	E_SERVER_TEXT_NEXT,
	E_SERVER_TEXT_CANCEL,
	E_SERVER_BUTTON_SERVER = 213,
	E_SERVER_BUTTON_NEXT = 214,
	E_SERVER_BUTTON_CANCEL = 215,

	E_CUSTOM_BUTTON_HAIR = 216,
	E_CUSTOM_BUTTON_EYE = 217,
	E_CUSTOM_BUTTON_MOUTH = 218
};

cUiCustomizingScene::cUiCustomizingScene(void)
	: m_mUiTest(NULL)
	, m_pUiTesterSize(NULL)
	, m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_pPlayer(NULL)
	, m_pMainCamera(NULL)

	, m_pServerSulastHeadImage(NULL)
	, m_pServerSulastImage(NULL)
	, m_pServerSulastButton(NULL)
	, m_pServerTextNext(NULL)
	, m_pServerTextCancel(NULL)
	, m_pServerSulastUi(NULL)

	, m_eCustomizingTab(E_CUSTOM_HAIR)
	, m_pCustomButtonHair(NULL)
	, m_pCustomButtonEye(NULL)
	, m_pCustomButtonMouth(NULL)
	, m_pCustomUi(NULL)
{
}

cUiCustomizingScene::~cUiCustomizingScene(void)
{
	this->Reset();
}


cUiCustomizingScene * cUiCustomizingScene::Create(void)
{
	cUiCustomizingScene* newClass = new cUiCustomizingScene;
	newClass->AddRef();
	return newClass;
}

HRESULT cUiCustomizingScene::Setup(void)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//이미지 크기 태스트
	m_pUiTesterSize = cUIImageView::Create();
	m_pUiTesterSize->SetTexture("Texture/Ui/buttonBase2Down.png");
	m_pUiTesterSize->SetPosition(100, 20);
	m_mUiTest = m_pUiTesterSize;

	//나중에 지울것
	//서버 창 머리
	m_pServerSulastHeadImage = cUIImageView::Create();
	m_pServerSulastHeadImage->SetTexture("Texture/Ui/customUiBaseHead1.png"); 
	m_pServerSulastHeadImage->SetPosition(20, 20);
	m_pServerSulastHeadImage->m_Alpha = 200;
	m_pServerSulastUi = m_pServerSulastHeadImage;
	//서버 창
	m_pServerSulastImage = cUIImageView::Create();
	m_pServerSulastImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pServerSulastImage->SetPosition(2, 48);
	m_pServerSulastImage->m_Alpha = 180;
	m_pServerSulastUi->AddChild(m_pServerSulastImage);
	//버튼1(다음)
	m_pServerSulastButton = cUIButton::Create();
	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonDown6024.png");
	m_pServerSulastButton->SetPosition(10, 370);
	m_pServerSulastButton->SetDelegate(this);
	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_NEXT);
	m_pServerSulastUi->AddChild(m_pServerSulastButton);
	//택스트
	m_pServerTextNext = cUITextView::Create();
	m_pServerTextNext->SetText("다음>>");
	m_pServerTextNext->SetFontType(g_pFontManager->E_INBUTTON);
	m_pServerTextNext->SetColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pServerTextNext->SetSize(ST_SIZE(50, 40));
	m_pServerTextNext->SetPosition(10, 363);
	m_pServerTextNext->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pServerTextNext->SetTag(E_SERVER_TEXT_NEXT);
	m_pServerSulastUi->AddChild(m_pServerTextNext);
	//버튼2(취소)
	m_pServerSulastButton = cUIButton::Create();
	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png",
		"Texture/Ui/textButtonUp6024.png");
	m_pServerSulastButton->SetPosition(164, 370);
	m_pServerSulastButton->SetDelegate(this);
	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_CANCEL);
	m_pServerSulastUi->AddChild(m_pServerSulastButton);
	//택스트
	m_pServerTextCancel = cUITextView::Create();
	m_pServerTextCancel->SetText("취소");
	m_pServerTextCancel->SetFontType(g_pFontManager->E_INBUTTON);
	m_pServerTextCancel->SetColor(D3DCOLOR_XRGB(180, 180, 180));
	m_pServerTextCancel->SetSize(ST_SIZE(50, 40));
	m_pServerTextCancel->SetPosition(169, 363);
	m_pServerTextCancel->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pServerTextCancel->SetTag(E_SERVER_TEXT_CANCEL);
	m_pServerSulastUi->AddChild(m_pServerTextCancel);

	//플레이어 설정
	//메시 로드 및 색상 편집
	cSkinnedMesh* pSkinMesh;
	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/DefaultPlayer/", "Hair.X");
	pSkinMesh->SetTextureColor("hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f));

	pSkinMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Chareter/DefaultPlayer/", "lisaAniTest.X");
	pSkinMesh->SetTextureColor("uni_shoes01_c.dds", &D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.2f));
	pSkinMesh->SetTextureColor("hair09.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pSkinMesh->SetTextureColor("bodymap01.dds", &D3DXCOLOR(1.0f, 0.53f, 0.53f, 0.2f));
	pSkinMesh->SetTextureColor("uni_newbie03_c.dds", &D3DXCOLOR(0.8f, 0.2f, 0.8f, 0.2f));
	pSkinMesh->SetTextureColor("uni_3rd_premium_c.dds", &D3DXCOLOR(0.5f, 0.0f, 0.1f, 0.2f));
	pSkinMesh->SetTextureColor("male_pumpkin_pants_c.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));
	//플레이어 생성
	m_pPlayer = cPlayer::Create();
	m_pPlayer->Setup();
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "Hair.X");
	m_pPlayer->ChangeMeshPart(cPlayer::MESH_BODY, "Chareter/DefaultPlayer/", "lisaAniTest.X");
	//카메라 연결
	m_pMainCamera = m_pPlayer->GetCamera();
	m_pMainCamera->Setup();
	//애니메이션 등록
	LPD3DXANIMATIONSET pAnimationSet;
	g_pAllocateHierarchy->GetAnimationSet(0, &pAnimationSet, "./Chareter/DefaultPlayer/aniTest/ani_female_stand_leftahead.X");
	m_pPlayer->RegisterAnimation(cPlayer::ANIMATION_5, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);
	//애니메이션 변형
	m_pPlayer->SetAnimation(cPlayer::ANIMATION_5);

	//커마 창 머리
	m_pCustomImageHead = cUIImageView::Create();
	m_pCustomImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomImageHead->SetPosition(20, 20);
	m_pCustomImageHead->m_Alpha = 200;
	m_pCustomUi = m_pCustomImageHead;
	//커마 창
	m_pCustomImage = cUIImageView::Create();
	m_pCustomImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomImage->SetPosition(2, 48);
	m_pCustomImage->m_Alpha = 180;
	m_pCustomUi->AddChild(m_pCustomImage);
	//선택버튼
	//머리 선택
	m_pCustomButtonHair = cUIButton::Create();
	m_pCustomButtonHair->SetTexture("Texture/Ui/buttonHairUp.png",
		"Texture/Ui/buttonHairUp.png",
		"Texture/Ui/buttonHairUp.png");
	m_pCustomButtonHair->SetPosition(10, 60);
	m_pCustomButtonHair->SetDelegate(this);
	m_pCustomButtonHair->SetTag(E_CUSTOM_BUTTON_HAIR);
	m_pCustomUi->AddChild(m_pCustomButtonHair);
	//눈 선택
	m_pCustomButtonEye = cUIButton::Create();
	m_pCustomButtonEye->SetTexture("Texture/Ui/buttonEyeUp.png",
		"Texture/Ui/buttonEyeUp.png",
		"Texture/Ui/buttonEyeUp.png");
	m_pCustomButtonEye->SetPosition(52, 60);
	m_pCustomButtonEye->SetDelegate(this);
	m_pCustomButtonEye->SetTag(E_CUSTOM_BUTTON_EYE);
	m_pCustomUi->AddChild(m_pCustomButtonEye);
	//입 선택
	m_pCustomButtonMouth = cUIButton::Create();
	m_pCustomButtonMouth->SetTexture("Texture/Ui/buttonMouseUp.png",
		"Texture/Ui/buttonMouseUp.png",
		"Texture/Ui/buttonMouseUp.png");
	m_pCustomButtonMouth->SetPosition(94, 60);
	m_pCustomButtonMouth->SetDelegate(this);
	m_pCustomButtonMouth->SetTag(E_CUSTOM_BUTTON_MOUTH);
	m_pCustomUi->AddChild(m_pCustomButtonMouth);



	return D3D_OK;
}

void cUiCustomizingScene::Reset(void)
{
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_mUiTest);

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

	SAFE_RELEASE(m_pServerSulastUi);
	SAFE_RELEASE(m_pCustomUi);
}

void cUiCustomizingScene::Update(void)
{
//	if (m_pServerSulastUi) m_pServerSulastUi->Update();
	if (m_eCustomizingTab == E_CUSTOM_HAIR)
	{
		m_pCustomButtonHair->SetTexture("Texture/Ui/buttonHairDown.png",
			"Texture/Ui/buttonHairDown.png",
			"Texture/Ui/buttonHairDown.png");
	}
	else
	{
		m_pCustomButtonHair->SetTexture("Texture/Ui/buttonHairUp.png",
			"Texture/Ui/buttonHairUp.png",
			"Texture/Ui/buttonHairUp.png");
	}
	if (m_eCustomizingTab == E_CUSTOM_EYE)
	{
		m_pCustomButtonEye->SetTexture("Texture/Ui/buttonEyeDown.png",
			"Texture/Ui/buttonEyeDown.png",
			"Texture/Ui/buttonEyeDown.png");
	}
	else
	{
		m_pCustomButtonEye->SetTexture("Texture/Ui/buttonEyeUp.png",
			"Texture/Ui/buttonEyeUp.png",
			"Texture/Ui/buttonEyeUp.png");
	}
	if (m_eCustomizingTab == E_CUSTOM_MOUTH)
	{
		m_pCustomButtonMouth->SetTexture("Texture/Ui/buttonMouseDown.png",
			"Texture/Ui/buttonMouseDown.png",
			"Texture/Ui/buttonMouseDown.png");
	}
	else
	{
		m_pCustomButtonMouth->SetTexture("Texture/Ui/buttonMouseUp.png",
			"Texture/Ui/buttonMouseUp.png",
			"Texture/Ui/buttonMouseUp.png");
	}

	SAFE_UPDATE(m_pPlayer);
	if (m_pMainCamera) m_pMainCamera->Update();
	
	if (m_pCustomUi) m_pCustomUi->Update();
	if (m_mUiTest) m_mUiTest->Update();
}

void cUiCustomizingScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	SAFE_RENDER(m_pPlayer);
//	if (m_pServerSulastUi) m_pServerSulastUi->Render(m_pSprite);
	if (m_pCustomUi) m_pCustomUi->Render(m_pSprite);
//	if (m_mUiTest) m_mUiTest->Render(m_pSprite);
}

void cUiCustomizingScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void cUiCustomizingScene::OnClick(cUIButton * pSender)
{
	//cUITextView* pTextView = (cUITextView*)m_pServerSulastUi->GetChildByTag(E_SERVER_TEXT_NEXT);
	// 0x8001 = 토글
	if (pSender->GetTag() == E_CUSTOM_BUTTON_HAIR)
	{
		m_eCustomizingTab = E_CUSTOM_HAIR;
	}
	else if (pSender->GetTag() == E_CUSTOM_BUTTON_EYE)
	{
		m_eCustomizingTab = E_CUSTOM_EYE;
	}
	else if (pSender->GetTag() == E_CUSTOM_BUTTON_MOUTH)
	{
		m_eCustomizingTab = E_CUSTOM_MOUTH;
	}
	
}