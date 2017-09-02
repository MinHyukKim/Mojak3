#include "stdafx.h"
#include "cMainGame.h"

//테스트용
#include "cFont.h"

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	//테스트용
	SAFE_RELEASE(m_pFont);

	g_pAutoRelasePool->Destroy();
	g_pDeviceManager->Destroy();
}


void cMainGame::Setup(void)
{
	//테스트용
	m_pFont = cFont::Create();
	m_pFont->Setup();
	m_pFont->DrawFont(100, 100, "출력 테스트 잘 출력됩니다.");
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	//제거가 필요한 객체 릴리즈

}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//그림을 그린다

	//테스트용
	SAFE_RENDER(m_pFont);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}