#include "GameManager.h"



GameManager::GameManager(void)
{
	//Ǫ�� 2�� �õ�
	//Ǫ�� 3�� �õ�
}

GameManager::~GameManager(void)
{

}

HRESULT GameManager::Init(void)
{
	// �̹���
//	_buffer = new BUFFER;
//	_GameObject.push_back(_buffer);

	// Ÿ�̸�
	_timer = new _Timer;
	_GameObject.push_back(_timer);


	//�Ŵ����� �ʱ�ȭ
	for (VG_Iterator it = _GameObject.begin(); it != _GameObject.end(); it++)
	{
		if (FAILED((*it)->Init())) return E_FAIL;
	}

	//�Ŵ��� ����
	_timer->SetLockFPS(60.0f);

	return S_OK;
}

void GameManager::Release(void)
{
	//�Ŵ����� ����
	for (VG_Iterator it = _GameObject.begin(); it != _GameObject.end(); it++)
	{
		(*it)->Release();
		SAFE_DELETE(*it);
	}
	_GameObject.clear();
}

void GameManager::Update(void)
{
	//�Ŵ����� ����
	for (VG_Iterator it = _GameObject.begin(); it != _GameObject.end(); it++)
	{
		(*it)->Update();
	}
}

void GameManager::Render(void)
{
//	_buffer->Render();
}



GameNode* GameManager::GetNode(int id)
{
	if (_GameObject.size() > id)
	{
		return _GameObject[id];
	}

	return NULL;
}



LRESULT GameManager::GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_KEYDOWN:
		if (wParam) PostMessage(hWnd, WM_DESTROY, 0, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
