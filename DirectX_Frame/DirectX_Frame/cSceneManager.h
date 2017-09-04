#pragma once

class cSceneObject;

class cSceneManager 
{
public:
	//�� ����Ʈ ������ ����, ���ͷ�����
	typedef std::map<std::string, cSceneObject*> mapSceneList;
	typedef std::map<std::string, cSceneObject*>::iterator mapSceneLter;

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

	cSceneObject* AddScene(std::string sceneName, cSceneObject* scene); //�� �߰�
	HRESULT ChangScene(std::string sceneName);							//�� ����
	friend DWORD CALLBACK LoadingThread(LPVOID prc);					//�ݹ� (�Ⱦ��� ���ɼ� ����)

	//�̱��� ����
	static cSceneManager* GetInstance() { static cSceneManager instance; return &instance; }

private:
	cSceneManager(void);
	virtual ~cSceneManager(void);
};

