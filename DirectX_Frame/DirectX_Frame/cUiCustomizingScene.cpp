
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
	E_CUSTOM_BUTTON_MOUTH = 218,

	//헤어설랙트
	E_HAIR_SELECT_01 = 219,
	E_HAIR_SELECT_02 = 220,
	E_HAIR_SELECT_03 = 221,
	//눈 설랙트
	E_EYE_SELECT_01 = 222,
	E_EYE_SELECT_02 = 223,
	E_EYE_SELECT_03 = 224,
	//입 설랙트
	E_MOUTH_SELECT_01 = 222,
	E_MOUTH_SELECT_02 = 223,
	E_MOUTH_SELECT_03 = 224,
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

	, m_pCustomHairUi(NULL)
	, m_pCustomEyeUi(NULL)
	, m_pCustomMouthUi(NULL)
	, m_isLButtonDown(false)
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

//	//나중에 지울것
//	//서버 창 머리
//	m_pServerSulastHeadImage = cUIImageView::Create();
//	m_pServerSulastHeadImage->SetTexture("Texture/Ui/customUiBaseHead1.png"); 
//	m_pServerSulastHeadImage->SetPosition(20, 20);
//	m_pServerSulastHeadImage->m_Alpha = 200;
//	m_pServerSulastUi = m_pServerSulastHeadImage;
//	//서버 창
//	m_pServerSulastImage = cUIImageView::Create();
//	m_pServerSulastImage->SetTexture("Texture/Ui/customUiBase2.png");
//	m_pServerSulastImage->SetPosition(2, 48);
//	m_pServerSulastImage->m_Alpha = 180;
//	m_pServerSulastUi->AddChild(m_pServerSulastImage);
//	//버튼1(다음)
//	m_pServerSulastButton = cUIButton::Create();
//	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
//		"Texture/Ui/textButtonUp6024.png",
//		"Texture/Ui/textButtonDown6024.png");
//	m_pServerSulastButton->SetPosition(10, 370);
//	m_pServerSulastButton->SetDelegate(this);
//	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_NEXT);
//	m_pServerSulastUi->AddChild(m_pServerSulastButton);
//	//택스트
//	m_pServerTextNext = cUITextView::Create();
//	m_pServerTextNext->SetText("다음>>");
//	m_pServerTextNext->SetFontType(g_pFontManager->E_INBUTTON);
//	m_pServerTextNext->SetColor(D3DCOLOR_XRGB(255, 255, 255));
//	m_pServerTextNext->SetSize(ST_SIZE(50, 40));
//	m_pServerTextNext->SetPosition(10, 363);
//	m_pServerTextNext->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	m_pServerTextNext->SetTag(E_SERVER_TEXT_NEXT);
//	m_pServerSulastUi->AddChild(m_pServerTextNext);
//	//버튼2(취소)
//	m_pServerSulastButton = cUIButton::Create();
//	m_pServerSulastButton->SetTexture("Texture/Ui/textButtonUp6024.png",
//		"Texture/Ui/textButtonUp6024.png",
//		"Texture/Ui/textButtonUp6024.png");
//	m_pServerSulastButton->SetPosition(164, 370);
//	m_pServerSulastButton->SetDelegate(this);
//	m_pServerSulastButton->SetTag(E_SERVER_BUTTON_CANCEL);
//	m_pServerSulastUi->AddChild(m_pServerSulastButton);
//	//택스트
//	m_pServerTextCancel = cUITextView::Create();
//	m_pServerTextCancel->SetText("취소");
//	m_pServerTextCancel->SetFontType(g_pFontManager->E_INBUTTON);
//	m_pServerTextCancel->SetColor(D3DCOLOR_XRGB(180, 180, 180));
//	m_pServerTextCancel->SetSize(ST_SIZE(50, 40));
//	m_pServerTextCancel->SetPosition(169, 363);
//	m_pServerTextCancel->SetDtawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
//	m_pServerTextCancel->SetTag(E_SERVER_TEXT_CANCEL);
//	m_pServerSulastUi->AddChild(m_pServerTextCancel);

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
	//위치
	m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.6f, -1.1f));
//	m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.4f, -1.2f));
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

	//헤어 창(매시, 컬러)
	//헤어 머리
	m_pCustomHairImageHead = cUIImageView::Create();
	m_pCustomHairImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomHairImageHead->SetPosition(20, 20);
	m_pCustomHairImageHead->m_Alpha = 0;
	m_pCustomHairUi = m_pCustomHairImageHead;
	//헤어 창
	m_pCustomHairImage = cUIImageView::Create();
	m_pCustomHairImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomHairImage->SetPosition(2, 48);
	m_pCustomHairImage->m_Alpha = 0;
	m_pCustomHairUi->AddChild(m_pCustomHairImage);
	//헤어 버튼1
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(10, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_01);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//2
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(70, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_02);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);
	//3
	m_pCustomHairSulastButton = cUIButton::Create();
	m_pCustomHairSulastButton->SetTexture("Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2.png",
		"Texture/Ui/buttonBase2Down.png");
	m_pCustomHairSulastButton->SetPosition(130, 120);
	m_pCustomHairSulastButton->SetDelegate(this);
	m_pCustomHairSulastButton->SetTag(E_HAIR_SELECT_03);
	m_pCustomHairUi->AddChild(m_pCustomHairSulastButton);

	//눈 창(택스쳐)
	//눈 머리
	m_pCustomEyeImageHead = cUIImageView::Create();
	m_pCustomEyeImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomEyeImageHead->SetPosition(20, 20);
	m_pCustomEyeImageHead->m_Alpha = 0;
	m_pCustomEyeUi = m_pCustomEyeImageHead;
	//눈 창
	m_pCustomEyeImage = cUIImageView::Create();
	m_pCustomEyeImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomEyeImage->SetPosition(2, 48);
	m_pCustomEyeImage->m_Alpha = 0;
	m_pCustomEyeUi->AddChild(m_pCustomEyeImage);

	//입 창(택스쳐)
	m_pCustomMouthImageHead = cUIImageView::Create();
	m_pCustomMouthImageHead->SetTexture("Texture/Ui/customUiBaseHead1.png");
	m_pCustomMouthImageHead->SetPosition(20, 20);
	m_pCustomMouthImageHead->m_Alpha = 0;
	m_pCustomMouthUi = m_pCustomMouthImageHead;
	//눈 창
	m_pCustomMouthImage = cUIImageView::Create();
	m_pCustomMouthImage->SetTexture("Texture/Ui/customUiBase2.png");
	m_pCustomMouthImage->SetPosition(2, 48);
	m_pCustomMouthImage->m_Alpha = 0;
	m_pCustomMouthUi->AddChild(m_pCustomMouthImage);

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

	SAFE_RELEASE(m_pCustomHairUi);
	SAFE_RELEASE(m_pCustomEyeUi);
	SAFE_RELEASE(m_pCustomMouthUi);
}

void cUiCustomizingScene::Update(void)
{
//	if (m_pServerSulastUi) m_pServerSulastUi->Update();

	changeButtonColor();
	SAFE_UPDATE(m_pPlayer);
	if (m_pMainCamera) m_pMainCamera->Update();
	if (m_pCustomUi) m_pCustomUi->Update();
	if (m_mUiTest) m_mUiTest->Update();

//	if (m_eCustomizingTab == E_CUSTOM_HAIR) m_pCustomHairUi->Update();
//	else return;
//	if (m_eCustomizingTab == E_CUSTOM_EYE) m_pCustomEyeUi->Update();
//	else return;
//	if (m_eCustomizingTab == E_CUSTOM_MOUTH) m_pCustomMouthUi->Update();
//	else return;

	switch (m_eCustomizingTab)
	{
	case E_CUSTOM_HAIR:
	{
		m_pCustomHairUi->Update();
	}
	break;
	case E_CUSTOM_EYE:
	{
		m_pCustomEyeUi->Update();
	}
	break;
	case E_CUSTOM_MOUTH:
	{
		m_pCustomMouthUi->Update();
	}
	break;
	}
}

void cUiCustomizingScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	SAFE_RENDER(m_pPlayer);
//	if (m_pServerSulastUi) m_pServerSulastUi->Render(m_pSprite);
	if (m_pCustomUi) m_pCustomUi->Render(m_pSprite);
//	if (m_mUiTest) m_mUiTest->Render(m_pSprite);
//	if (m_eCustomizingTab == E_CUSTOM_HAIR) m_pCustomHairUi->Render(m_pSprite);
//	else return;
//	if (m_eCustomizingTab == E_CUSTOM_EYE) m_pCustomEyeUi->Render(m_pSprite);
//	else return;
//	if (m_eCustomizingTab == E_CUSTOM_MOUTH) m_pCustomMouthUi->Render(m_pSprite);
//	else return;

	switch (m_eCustomizingTab)
	{
		case E_CUSTOM_HAIR:
		{
			m_pCustomHairUi->Render(m_pSprite);
		}
		break;
		case E_CUSTOM_EYE:
		{
			m_pCustomEyeUi->Render(m_pSprite);
		}
		break;
		case E_CUSTOM_MOUTH:
		{
			m_pCustomMouthUi->Render(m_pSprite);
		}
		break;
	}
}

void cUiCustomizingScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);

		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);

			float fDeltaX = (ptCurrMouse.x - m_ptPrevMouse.x);
			float fDeltaY = (ptCurrMouse.y - m_ptPrevMouse.y);

	//		m_pPlayer->
	//		nMatX += fDeltaX;
	//		nMatY += fDeltaY;

			m_ptPrevMouse = ptCurrMouse;

		}
	}
	break;
	}
}

void cUiCustomizingScene::OnClick(cUIButton * pSender)
{
	//cUITextView* pTextView = (cUITextView*)m_pServerSulastUi->GetChildByTag(E_SERVER_TEXT_NEXT);
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

	if (m_eCustomizingTab == E_CUSTOM_HAIR)
	{
		if (pSender->GetTag() == E_HAIR_SELECT_01)
		{
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair01_t01.X");
		//	m_pPlayer->GetMeshPart(cPlayer::MESH_FACE, )
		}
		else if (pSender->GetTag() == E_HAIR_SELECT_02)
		{
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair02_t02.X");
		}
		else if (pSender->GetTag() == E_HAIR_SELECT_03)
		{
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair02_t02.X");
		}
	}
	
}


void cUiCustomizingScene::changeButtonColor()
{
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
}