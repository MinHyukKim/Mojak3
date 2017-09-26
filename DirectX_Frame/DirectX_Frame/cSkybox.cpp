#pragma once
#include "stdafx.h"
#include "cSkybox.h"

HRESULT cSkybox::Setup(const char * top, const char * bottom, const char * left, const char * right, const char * front, const char * back)
{
	//���� �����
	// - texture UV���� �����غ��� ���� 24���� �ʿ��ϴ�.
	m_pTexture[0] = g_pTexture->GetTexture(top);
	m_pTexture[1] = g_pTexture->GetTexture(bottom);
	m_pTexture[2] = g_pTexture->GetTexture(left);
	m_pTexture[3] = g_pTexture->GetTexture(right);
	m_pTexture[4] = g_pTexture->GetTexture(front);
	m_pTexture[5] = g_pTexture->GetTexture(back);

	ST_PNT_VERTEX* pv;

	for (int i = 0; i<6; i++)
	{
		if (FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(ST_PNT_VERTEX) * 4, 0,
			ST_PNT_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVertex[i], NULL))) return S_FALSE;
	}
	//�ڽ� PNT����
	//top
	if (FAILED(m_pVertex[0]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(1.f, 1.f, -1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 1);

	pv[1].p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 1);
	
	pv[2].p = D3DXVECTOR3(1.f, 1.f, 1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(1, 1);

	pv[3].p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 0);

	m_pVertex[0]->Unlock();

	//bottom
	if (FAILED(m_pVertex[1]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(1.f, -1.f, 1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 0);

	pv[1].p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 0);

	pv[2].p = D3DXVECTOR3(1.f, -1.f, -1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(0, 1);

	pv[3].p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 1);

	m_pVertex[1]->Unlock();
	//left
	if (FAILED(m_pVertex[2]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 0);

	pv[1].p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 0);

	pv[2].p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(0, 1);

	pv[3].p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 1);

	m_pVertex[2]->Unlock();
	//right
	if (FAILED(m_pVertex[3]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(1.f, 1.f, -1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 0);

	pv[1].p = D3DXVECTOR3(1.f, 1.f, 1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 0);

	pv[2].p = D3DXVECTOR3(1.f, -1.f, -1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(0, 1);

	pv[3].p = D3DXVECTOR3(1.f, -1.f, 1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 1);
	m_pVertex[3]->Unlock();
	//front
	if (FAILED(m_pVertex[4]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(1.f, 1.f, -1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 0);

	pv[1].p = D3DXVECTOR3(1.f, 1.f, 1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 0);

	pv[2].p = D3DXVECTOR3(1.f, -1.f, -1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(0, 1);

	pv[3].p = D3DXVECTOR3(1.f, -1.f, 1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 1);

	m_pVertex[4]->Unlock();
	//back
	if (FAILED(m_pVertex[5]->Lock(0, 0, (void**)&pv, 0))) return S_FALSE;
	pv[0].p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pv[0].n = D3DXVECTOR3(1, 1, 1);
	pv[0].t = D3DXVECTOR2(0, 0);

	pv[1].p = D3DXVECTOR3(1.f, 1.f, -1.f);
	pv[1].n = D3DXVECTOR3(1, 1, 1);
	pv[1].t = D3DXVECTOR2(1, 0);

	pv[2].p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pv[2].n = D3DXVECTOR3(1, 1, 1);
	pv[2].t = D3DXVECTOR2(0, 1);

	pv[3].p = D3DXVECTOR3(1.f, -1.f, -1.f);
	pv[3].n = D3DXVECTOR3(1, 1, 1);
	pv[3].t = D3DXVECTOR2(1, 1);

	m_pVertex[5]->Unlock();

	for (int i = 0; i<6; i++)
	{
		//�ε��� ����
		if (FAILED(g_pD3DDevice->CreateIndexBuffer(sizeof(ST_INDEX) * 12, 
			0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndex[i], NULL))) return S_FALSE;
	}

	//�ε��� ���� �ʱ�ȭ
	ST_INDEX* iv;
	for (int i = 0; i<6; i++)
	{
		if (FAILED(m_pIndex[i]->Lock(0, 0, (void**)&iv, 0))) return S_FALSE;
		iv[0]._0 = 0; iv[0]._1 = 1; iv[0]._2 = 2;
		iv[1]._0 = 2; iv[1]._1 = 1; iv[1]._2 = 3;
		m_pIndex[i]->Unlock();
	}

	return S_OK;

}

void cSkybox::Update(D3DXVECTOR3 cameraPt)
{
	vPos = cameraPt;
}

void cSkybox::Render(void)
{

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�ø��� ���
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z���� ����
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//���� ����

	//��ī�� �ڽ� �̵�.
	D3DXMATRIX matWorld;	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, vPos.x, vPos.y, vPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//�ؽ��� UV Address�� ����.
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	
	//��ī�̹ڽ� ��ο�.
	for (int i = 0; i<6; i++)
	{
		g_pD3DDevice->SetTexture(0, (m_pTexture[i]) ? m_pTexture[i] : NULL);
		g_pD3DDevice->SetStreamSource(0, m_pVertex[i], 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->SetIndices(m_pIndex[i]);
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	//��� �ʱ�ȭ.
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			//Z���� �ѱ�
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���� �ѱ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�ø� �ݽð����
}

cSkybox * cSkybox::Create(void)
{
	cSkybox* newClass = new cSkybox;
	newClass->AddRef();
	return newClass;
}

cSkybox::cSkybox(void)
	:vPos(0, 0 ,0)
{
}

cSkybox::~cSkybox(void)
{
	for (int i = 0; i<6; i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
		SAFE_RELEASE(m_pVertex[i]);
		SAFE_RELEASE(m_pIndex[i]);
	}

}
