#include "stdafx.h"
#include "cMainGame.h"

//�׽�Ʈ��
#include "cFont.h"

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
	//�׽�Ʈ��
	SAFE_RELEASE(m_pFont);

	g_pAutoRelasePool->Destroy();
	g_pDeviceManager->Destroy();
}


void cMainGame::Setup(void)
{
	//�׽�Ʈ��
	m_pFont = cFont::Create();
	m_pFont->Setup();
	m_pFont->DrawFont(100, 100, "��� �׽�Ʈ �� ��µ˴ϴ�.");
}

void cMainGame::Update(void)
{
	g_pAutoRelasePool->AutoReleaseCheck();	//���Ű� �ʿ��� ��ü ������

}

void cMainGame::Render(void)
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//�׸��� �׸���

	//�׽�Ʈ��
	SAFE_RENDER(m_pFont);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}