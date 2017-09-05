#pragma once

#define	g_pSceneManager cSceneManager::GetInstance()

class cSceneObject;

class cSceneManager 
{
public:
	//�� ����Ʈ ������ ����, ���ͷ�����
	typedef std::map<std::string, cSceneObject*> mapSceneList;
	typedef std::map<std::string, cSceneObject*>::iterator mapSceneIter;

private:
	static cSceneObject* m_pCurrentScene;		//���� ��
	static cSceneObject* m_pLoadingScene;		//�ε� ��
	static cSceneObject* m_pReadyScene;			//�غ� ��

	mapSceneList	m_mapSceneList;				//�� ����Ʈ
	DWORD			m_dLoadThreadID;			//������ (�Ⱦ��� ���ɼ� ����)

public:
	virtual HRESULT Setup(void);
	virtual void Reset(void);		//������ ���
	virtual void Update(void);	
	virtual void Render(void);

	cSceneObject* AddScene(std::string& szSceneName, cSceneObject* pScene);		//�� �߰�
	cSceneObject* AddScene(LPCSTR szSceneName, cSceneObject* pScene);			//���ڿ� ���縦 ���̱� ���� �߰���

	HRESULT ChangScene(std::string& szSceneName);								//�� ����
	HRESULT ChangScene(LPCSTR szSceneName);										//���ڿ� ���縦 ���̱� ���� �߰���

	friend DWORD CALLBACK LoadingThread(LPVOID prc);							//�ݹ� (�Ⱦ��� ���ɼ� ����)

	void Destroy(void);

	//�̱��� ����
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }
private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

