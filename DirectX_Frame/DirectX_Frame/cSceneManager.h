#pragma once

#define	g_pSceneManager cSceneManager::GetInstance()

class cSceneObject;

class cSceneManager 
{
public:
	//씬 리스트 맵으로 저장, 이터레이터
	typedef std::map<std::string, cSceneObject*> mapSceneList;
	typedef std::map<std::string, cSceneObject*>::iterator mapSceneIter;

private:
	static cSceneObject* m_pCurrentScene;		//현재 씬
	static cSceneObject* m_pLoadingScene;		//로딩 씬
	static cSceneObject* m_pReadyScene;			//준비 씬

	mapSceneList	m_mapSceneList;				//씬 리스트
	DWORD			m_dLoadThreadID;			//쓰레드 (안쓰일 가능성 높음)

public:
	virtual HRESULT Setup(void);
	virtual void Reset(void);		//릴리증 대용
	virtual void Update(void);	
	virtual void Render(void);

	cSceneObject* AddScene(std::string& szSceneName, cSceneObject* pScene);		//씬 추가
	cSceneObject* AddScene(LPCSTR szSceneName, cSceneObject* pScene);			//문자열 복사를 줄이기 위해 추가함

	HRESULT ChangScene(std::string& szSceneName);								//씬 변경
	HRESULT ChangScene(LPCSTR szSceneName);										//문자열 복사를 줄이기 위해 추가함

	friend DWORD CALLBACK LoadingThread(LPVOID prc);							//콜백 (안쓰일 가능성 높음)

	void Destroy(void);

	//싱글톤 생성
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }
private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

