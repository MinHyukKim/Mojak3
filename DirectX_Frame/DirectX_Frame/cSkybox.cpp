#pragma once
#include "stdafx.h"
#include "cSkybox.h"

HRESULT cSkybox::Setup(const char * top, const char * bottom, const char * left, const char * right, const char * front, const char * back)
{
	//상자 만들기
	// - texture UV까지 생각해보면 정점 24개가 필요하다.
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
	//박스 PNT설정
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
		//인덱스 버퍼
		if (FAILED(g_pD3DDevice->CreateIndexBuffer(sizeof(ST_INDEX) * 12, 
			0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndex[i], NULL))) return S_FALSE;
	}

	//인덱스 버퍼 초기화
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

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링은 양면
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z버퍼 끄기
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//조명 끄기

	//스카이 박스 이동.
	D3DXMATRIX matWorld;	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, vPos.x, vPos.y, vPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//텍스쳐 UV Address를 설정.
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	
	//스카이박스 드로우.
	for (int i = 0; i<6; i++)
	{
		g_pD3DDevice->SetTexture(0, (m_pTexture[i]) ? m_pTexture[i] : NULL);
		g_pD3DDevice->SetStreamSource(0, m_pVertex[i], 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->SetIndices(m_pIndex[i]);
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	//행렬 초기화.
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			//Z버퍼 켜기
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//조명 켜기
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//컬링 반시계방향
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
