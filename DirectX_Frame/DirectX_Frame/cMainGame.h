#pragma once
//�׽�Ʈ��
class cFont;

class cMainGame
{
private:
	LPDIRECT3D9 mpD3D;
	LPDIRECT3DDEVICE9 mpD3DD;

	//�׽�Ʈ�� 
	cFont* m_pFont;

public:

	void Setup();
	void Update();
	void Render();

	cMainGame();
	~cMainGame();
};

