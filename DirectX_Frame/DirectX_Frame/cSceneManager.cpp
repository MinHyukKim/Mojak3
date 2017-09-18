#include "stdafx.h"
#include "cSceneManager.h"
#include "cSceneObject.h"	

//외부에서 초기화
cSceneObject* cSceneManager::m_pCurrentScene = NULL;
cSceneObject* cSceneManager::m_pLoadingScene = NULL;
cSceneObject* cSceneManager::m_pReadyScene = NULL;

cSceneManager::cSceneManager(void)
{
}

cSceneManager::~cSceneManager(void)
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


cSceneObject * cSceneManager::AddScene(std::string& stringName, cSceneObject* pScene)
{
	return this->AddScene(stringName.c_str(), pScene);
}

cSceneObject * cSceneManager::AddScene(LPCSTR szSceneName, cSceneObject* pScene)
{
	if (!pScene) return NULL;
	m_mapSceneList.insert(make_pair(szSceneName, pScene));

	return pScene;
}

HRESULT cSceneManager::ChangeScene(std::string& sceneName)
{
	return this->ChangeScene(sceneName.c_str());
}

HRESULT cSceneManager::ChangeScene(LPCSTR szSceneName)
{
	mapSceneIter find = m_mapSceneList.find(szSceneName);
	if (find == m_mapSceneList.end()) return E_FAIL;
	if (SUCCEEDED(find->second->Setup()))
	{
		if (m_pCurrentScene) m_pCurrentScene->Reset();
		m_pCurrentScene = find->second;
		return D3D_OK;
	}
	return E_FAIL;
}

void cSceneManager::Destroy(void)
{
	for each(auto it in m_mapSceneList)
	{
		if (it.second)
		{
			it.second->Release();
		}
	}
	m_mapSceneList.clear();
	m_pCurrentScene = NULL;
	m_pLoadingScene = NULL;
	m_pReadyScene = NULL;
}

DWORD CALLBACK LoadingThread(LPVOID prc)
{
	cSceneManager::m_pReadyScene->Setup();

	cSceneManager::m_pCurrentScene = cSceneManager::m_pReadyScene;

	cSceneManager::m_pLoadingScene->Reset();
	cSceneManager::m_pLoadingScene = NULL;
	cSceneManager::m_pReadyScene = NULL;

	return NULL;
}
