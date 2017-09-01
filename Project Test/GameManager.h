#pragma once
#include "Singleton.h"
#include "Timer.h"
#include "BackBuffer.h"

#define GAME GameManager::GetSingleton()
#define TIMER GameManager::GetSingleton()->GetTimer()

#define GetMouse() GameManager::GetSingleton()->GetMousePoint();


class GameManager : public Singleton<GameManager>
{
public:
	typedef typename std::vector<PGNODE> VectorGameNode;
	typedef typename std::vector<PGNODE>::iterator VG_Iterator;

private:
	VectorGameNode _GameObject;

	BUFFER* _buffer;
	TIME* _timer;

public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	PGNODE GetNode(int id);

	inline LPBUFFER GetBuffer() { return _buffer; }
	inline LPTIME GetTimer() { return _timer; }

	LRESULT GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameManager(void);
	virtual ~GameManager(void);
};

