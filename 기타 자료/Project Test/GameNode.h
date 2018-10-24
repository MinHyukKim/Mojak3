#pragma once
#include "WinAPI.h"

typedef class GameNode
{
public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	GameNode(void);
	virtual ~GameNode(void);
}GNODE, *PGNODE, &LGNODE;

