#include "stdafx.h"
#include "cSceneManager.h"
#include "cSceneObject.h"	

//외부에서 초기화
cSceneObject* cSceneManager::m_pCurrentScene = NULL;
cSceneObject* cSceneManager::m_pLoadingScene = NULL;
cSceneObject* cSceneManager::m_pReadyScene = NULL;

cSceneManager::cSceneManager()
{
}

cSceneManager::~cSceneManager()
{
}

HRESULT cSceneManager::Setup(void)
{

	return D3D_OK;
}

//릴리즈 대용
void cSceneManager::Reset(void)
{
	mapSceneIter iter = m_mapSceneList.begin();

	while (iter != m_mapSceneList.end())
	{
		if (iter->second != NULL)
		{
			if (m_pCurrentScene == iter->second) iter->second->Release();
			SAFE_RELEASE(iter->second);
			iter = m_mapSceneList.erase(iter);
		}
		else ++iter;
	}

	m_pCurrentScene = NULL;
	m_mapSceneList.clear();
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
	mapSceneIter find = m_mapSceneList.find(sceneName);
	if (find == m_mapSceneList.end()) return E_FAIL;
	if (SUCCEEDED(find->second->Setup()))
	{
		if (m_pCurrentScene) m_pCurrentScene->Reset();
		m_pCurrentScene = find->second;

		return D3D_OK;
	}

	return E_FAIL;
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
