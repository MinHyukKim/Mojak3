#pragma once
//테스트용
class cFont;

class cMainGame
{
private:
	LPDIRECT3D9 mpD3D;
	LPDIRECT3DDEVICE9 mpD3DD;

	//테스트용 
	cFont* m_pFont;

public:

	void Setup();
	void Update();
	void Render();

	cMainGame();
	~cMainGame();
};

