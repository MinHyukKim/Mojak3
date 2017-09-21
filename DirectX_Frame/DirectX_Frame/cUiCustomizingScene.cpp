
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
	, m_pNameUi(NULL)
	, m_nX(20)
	, m_nY(20)

	, m_pCustomHairUi(NULL)
	, m_pCustomEyeUi(NULL)
	, m_pCustomMouthUi(NULL)
	, m_pCustomColorUi(NULL)
	, m_isLButtonDown(false)
	, m_pHairColor(&D3DXCOLOR(0.07f, 0.07f, 0.07f, 1.0f))
	, m_hairColor(1.0f, 0.0f, 0.0f, 1.0f)

	, m_eHairStyleTab(E_HAIR_01)
{
	//초기화되지 않은 변수들
//	m_pFont = nullptr;
//	m_pNameImageHead = nullptr;
//	m_pNameImage = nullptr;
//	m_pNameButton = nullptr;
//	m_pNameUi = nullptr;
//
//	 m_pCustomImageHead = nullptr;
//	 m_pCustomImage = nullptr;
//	 m_pCustomButtonFin = nullptr;
//	 m_pCustomButton = nullptr;
//	//커마 창 글씨
//	cUITextView* m_pCustomNameTest;
//	//헤어
//	eCustomizingHair m_eHairStyleTab;
//	cUIImageView* m_pCustomHairImageHead;
//	cUIImageView* m_pCustomHairImage;
//	cUIButton* m_pCustomHairSulastButton;
//	cUiObject* m_pCustomHairUi;
//	//색깔(헤어, 눈)
//	cUIImageView* m_pCustomColorImageHead;
//	cUIImageView* m_pCustomColorImage;
//	cUIButton* m_pCustomColorSulastButton;
//	cUiObject* m_pCustomColorUi;
//	LPD3DXCOLOR m_pHairColor;
//	D3DXCOLOR m_hairColor;
//	//눈
//	cUIImageView* m_pCustomEyeImageHead;
//	cUIImageView* m_pCustomEyeImage;
//	cUIButton* m_pCustomEyeSulastButton;
//	cUIButton* m_pCustomEyeColorSulastButton;
//	cUiObject* m_pCustomEyeUi;
//	//입
//	cUIImageView* m_pCustomMouthImageHead;
//	cUIImageView* m_pCustomMouthImage;
//	cUIButton* m_pCustomMouthSulastButton;
//	cUIButton* m_pCustomMouthColorSulastButton;
//	cUiObject* m_pCustomMouthUi;
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
	m_pUiTesterSize->SetTexture("Texture/Ui/buttonBase.png");
	m_pUiTesterSize->SetPosition(100, 20);
	m_mUiTest = m_pUiTesterSize;

	//플레이어 설정
	this->SetupPlayer();
	//전체적 선택 창
	this->SetupTotal();
	//헤어 스타일(매쉬 버튼)
	this->SetupHairStyle();
	//헤어, 눈 색상 변경 버튼
	this->SetupHairEyeColor();
	//눈 변경 버튼
	this->SetupEyeStyle();
	//입 변경 버튼
	this->SetupMouthStyle();

	return D3D_OK;
}

void cUiCustomizingScene::Reset(void)
{
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pMainCamera);
	SAFE_RELEASE(m_mUiTest);

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

	SAFE_RELEASE(m_pServerSulastUi);
	SAFE_RELEASE(m_pCustomUi);

	SAFE_RELEASE(m_pCustomHairUi);
	SAFE_RELEASE(m_pCustomEyeUi);
	SAFE_RELEASE(m_pCustomMouthUi);
	SAFE_RELEASE(m_pCustomColorUi);

	SAFE_RELEASE(m_pNameUi);
}

void cUiCustomizingScene::Update(void)
{
//	if (m_pServerSulastUi) m_pServerSulastUi->Update();

	this->changeButtonColor();
	SAFE_UPDATE(m_pPlayer);

	switch (m_eCustomizingTab)
	{
	case E_CUSTOM_HAIR:
	{
		if (m_pCustomHairUi) m_pCustomHairUi->Update();
		if (m_pCustomColorUi) m_pCustomColorUi->Update();
	//	m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.4f, -1.1f));
	}
	break;
	case E_CUSTOM_EYE:
	{
		if (m_pCustomEyeUi) m_pCustomEyeUi->Update();
		if (m_pCustomColorUi) m_pCustomColorUi->Update();
	//	m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.7f, -1.1f));
	}
	break;
	case E_CUSTOM_MOUTH:
	{
		if (m_pCustomMouthUi) m_pCustomMouthUi->Update();
	//	m_pMainCamera->SetPosition(&D3DXVECTOR3(50.0f, 0.7f, -1.1f));
	}
	break;
	}

	this->changeButtonColorHair();


	if (m_pMainCamera) m_pMainCamera->Update();
	if (m_mUiTest) m_mUiTest->Update();
	if (m_pCustomUi) m_pCustomUi->Update();
//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", m_pHairColor);

	if (g_pObjectManager->GetPlayer())
	{
		g_pSceneManager->ChangeScene("cMapToolScene");
		return;
	}
}

void cUiCustomizingScene::Render(void)
{
	g_pD3DDevice->SetTexture(0, m_pTexture);
	SAFE_RENDER(m_pPlayer);
//	if (m_pServerSulastUi) m_pServerSulastUi->Render(m_pSprite);
	if (m_pCustomUi) m_pCustomUi->Render(m_pSprite);

	switch (m_eCustomizingTab)
	{
		case E_CUSTOM_HAIR:
		{
			if(m_pCustomHairUi) m_pCustomHairUi->Render(m_pSprite);
			if (m_pCustomColorUi) m_pCustomColorUi->Render(m_pSprite);
		}
		break;
		case E_CUSTOM_EYE:
		{
			if(m_pCustomEyeUi) m_pCustomEyeUi->Render(m_pSprite);
			if (m_pCustomColorUi) m_pCustomColorUi->Render(m_pSprite);
		}
		break;
		case E_CUSTOM_MOUTH:
		{
			if(m_pCustomMouthUi) m_pCustomMouthUi->Render(m_pSprite);
		}
		break;
	}
	//이미지 크기 태스트용
	//if (m_mUiTest) m_mUiTest->Render(m_pSprite);
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
	else if (pSender->GetTag() == E_CUSTOM_BUTTON_FIN)
	{
	//	g_pObjectManager->RegisterPlayer(m_pPlayer);
		g_pObjectManager->RegisterPlayer(m_pPlayer);
	}

	//머리 메뉴가 나올시
	if (m_eCustomizingTab == E_CUSTOM_HAIR)
	{
		//머리 스타일 변경
		if (pSender->GetTag() == E_HAIR_SELECT_01)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair02_t02.X");
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, g_pSkinnedMeshManager->GetSkinnedMesh("헤어00"));
			m_pPlayer->SetTextureHair("hair01.dds");
		//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		//	m_pPlayer->GetMeshPart(cPlayer::MESH_FACE, )
		}
		else if (pSender->GetTag() == E_HAIR_SELECT_02)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair01_t01.X");
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, g_pSkinnedMeshManager->GetSkinnedMesh("헤어01"));
			m_pPlayer->SetTextureHair("hair01.dds");
		//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (pSender->GetTag() == E_HAIR_SELECT_03)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, "Chareter/DefaultPlayer/", "hair_female_hair22_t22.X");
			m_pPlayer->ChangeMeshPart(cPlayer::MESH_HAIR, g_pSkinnedMeshManager->GetSkinnedMesh("헤어02"));
			m_pPlayer->SetTextureHair("hair01.dds");
		//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		}

		//머리 색 변경
		if (pSender->GetTag() == E_HAIR_COLOR_SELECT_BLACK)
		{
			//m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.07f, 0.07f, 0.07f, 1.0f));

		}
		else if (pSender->GetTag() == E_HAIR_COLOR_SELECT_MID_BLUE)
		{
		//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(0.0f, 0.08f, 0.2f, 1.0f));
		//	m_pPlayer->SetTextureHair("hair01.dds");
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.0f, 0.08f, 0.2f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_RED))
		{
			//m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.35f, 0.0f, 0.15f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BROWN))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.25f, 0.15f, 0.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BLONDE))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.89f, 0.85f, 0.53f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_ORANGE))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.93f, 0.57f, 0.32f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_DARKGREEN))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.0f, 0.12f, 0.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_WHITE))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.90f, 0.88f, 1.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_SKY))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.59f, 0.79f, 1.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BLUE))
		{
			m_pPlayer->SetTextureHairColor(&D3DXCOLOR(0.35f, 0.30f, 0.55f, 1.0f));
		}
	}

	//눈깔 변경
	if (m_eCustomizingTab == E_CUSTOM_EYE)
	{
		if (pSender->GetTag() == E_EYE_SELECT_01)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureEye("eye_0.dds");
		}
		else if (pSender->GetTag() == E_EYE_SELECT_02)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureEye("eye_1.dds");
		}
		else if (pSender->GetTag() == E_EYE_SELECT_03)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureEye("eye_2.dds");

		//	m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_HAIR, "hair01.dds", &D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}

		//눈 색 변경
		if (pSender->GetTag() == E_HAIR_COLOR_SELECT_BLACK)
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.07f, 0.07f, 0.07f, 1.0f));
		}
		else if (pSender->GetTag() == E_HAIR_COLOR_SELECT_MID_BLUE)
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.0f, 0.08f, 0.2f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_RED))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.35f, 0.0f, 0.15f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BROWN))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.25f, 0.15f, 0.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BLONDE))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.89f, 0.85f, 0.53f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_ORANGE))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.93f, 0.57f, 0.32f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_DARKGREEN))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.0f, 0.12f, 0.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_WHITE))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.90f, 0.88f, 1.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_SKY))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.59f, 0.79f, 1.0f, 1.0f));
		}
		else if ((pSender->GetTag() == E_HAIR_COLOR_SELECT_BLUE))
		{
			m_pPlayer->SetTextureEyeColor(&D3DXCOLOR(0.35f, 0.30f, 0.55f, 1.0f));
		}
	}

	//입 변경
	if (m_eCustomizingTab == E_CUSTOM_MOUTH)
	{
		if (pSender->GetTag() == E_MOUTH_SELECT_01)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureMouth("mouth_0.dds");
			m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_FACE, "mouth_0.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pSender->GetTag() == E_MOUTH_SELECT_02)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureMouth("mouth_1.dds");
			m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_FACE, "mouth_0.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pSender->GetTag() == E_MOUTH_SELECT_03)
		{
		//	m_pPlayer->ChangeMeshPart(cPlayer::MESH_FACE, "./Chareter/Female_Face/", "basicFace.X");
			m_pPlayer->SetTextureMouth("mouth_2.dds");
			m_pPlayer->ChangeMeshPartColor(cPlayer::MESH_FACE, "mouth_0.dds", &D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
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

void cUiCustomizingScene::changeButtonColorHair()
{

}
