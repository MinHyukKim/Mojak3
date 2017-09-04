#include "stdafx.h"
#include "cSceneManager.h"
#include "cSceneObject.h"	

cSceneManager::cSceneManager()
{
	m_pCurrentScene = NULL;
	m_pLoadingScene = NULL;
	m_pReadyScene = NULL;
}


cSceneManager::~cSceneManager()
{
}

HRESULT cSceneManager::Setup(void)
{

	return D3D_OK;
}

void cSceneManager::Update(void)
{
	if (m_pCurrentScene) m_pCurrentScene->Update();
}

void cSceneManager::Render(void)
{
	if (m_pCurrentScene)m_pCurrentScene->Render();
}

cSceneObject * cSceneManager::AddScene(std::string sceneName, cSceneObject * scene)
{
	if (!scene) return NULL;
	m_mapSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

HRESULT cSceneManager::ChangScene(std::string sceneName)
{
	mapSceneLter find = m_mapSceneList.find(sceneName);
	if (find == m_mapSceneList.end()) return E_FAIL;
	if (SUCCEEDED(find->second->Setup()))
	{
		//현재 씬이 있다면 현재씬 제거 필요(미구현)
		m_pCurrentScene = find->second;

		return D3D_OK;
	}

	return E_FAIL;
}

DWORD CALLBACK LoadingThread(LPVOID prc)
{
	cSceneManager::m_pReadyScene->Setup();

	cSceneManager::m_pCurrentScene = cSceneManager::m_pReadyScene;

	//로딩씬 제거 필요(미구현)
	cSceneManager::m_pLoadingScene = NULL;
	cSceneManager::m_pReadyScene = NULL;

	return NULL;
}
