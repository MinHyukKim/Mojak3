#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//�½�Ʈ
class cFont;
//Ui�½�Ʈ
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiTestScene : public cSceneObject, iButtonDelegate
{
private:
	//�̵� ���� �Ѹ����� �ɹ�������
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;
	//������ �Ѹ�
	cUIImageView* m_pMainRootImageView;
	cUiObject* m_pUiRoot;
	cUIButton* m_pMainMainButton;
	int m_nmainUiLocalY;

	//���� uiƲ ��ġ
	int mainUiLocalX = 300;			//���� Ʋ x
	int mainUiLocalY = 502;			//���� Ʋ y

	int mainButtonH = -25;			//���� ��ư�� ����
	int mainButtoninterval = 40;	//���� ��ư�� ���� ����(ũ��)
	int mainButtonSrart = 160;		//���� ��ư�� ���� ���� ��ġ


	//�Ⱦ�
	cUiObject* m_pUiTestRoot;
	//�г� �̹��� ũ�� �½�Ʈ��
	cUIImageView* m_pUiTesterSize;

	//Ŭ������?
	bool m_isClick;
	//���� â �ּ�ȭ ����
	bool m_isMainMin;

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;
//	virtual void Onclick(cUIButton* pSender) override;

	static cUiTestScene* Create(void);
protected:
	cUiTestScene(void);
	virtual ~cUiTestScene(void);

};