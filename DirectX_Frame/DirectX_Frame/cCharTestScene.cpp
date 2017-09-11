#include "stdafx.h"
#include "cCharTestScene.h"

#include "cCamera.h"
//�׽�Ʈ��
#include "cGrid.h"


cCharTestScene::cCharTestScene(void)
	: m_pCamera(NULL)
{
}

cCharTestScene::~cCharTestScene(void)
{
}

HRESULT cCharTestScene::Setup(void)
{
	m_pCamera = cCamera::Create();
	m_pCamera->Setup();

	//�׽�Ʈ��
	m_pGrid = cGrid::Create();
	m_pGrid->Setup();

	return S_OK;

}

void cCharTestScene::Reset(void)
{
}

void cCharTestScene::Update(void)
{
}

void cCharTestScene::Render(void)
{
}

cCharTestScene* cCharTestScene::Create(void)
{
	cCharTestScene* newClass = new cCharTestScene;
	newClass->AddRef();
	return newClass;
}

