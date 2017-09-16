#pragma once
#include "cSceneObject.h"
#include "cUIButton.h"

//��Ʈ
class cFont;
//Ui����
class cUIImageView;
class cUIButton;
class cUITextView;
class iButtonDelegate;

class cUiCustomizingScene : public cSceneObject, iButtonDelegate
{
private:
	//�̵� ���� �Ѹ����� �ɹ�������
	cFont* m_pFont;
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTexture;

	//�г� �̹��� ũ�� �½�Ʈ��
	cUIImageView* m_pUiTesterSize;
	cUiObject* m_mUiTest;

	//���� ���� â
	cUIImageView* m_pServerSulastHeadImage;
	cUIImageView* m_pServerSulastImage;
	cUIButton* m_pServerSulastButton;
	cUITextView* m_pServerTextNext;
	cUITextView* m_pServerTextCancel;
	cUiObject* m_pServerSulastUi;

	//�̸� �Է� â
	cUIImageView* m_pNameImage;
	cUIButton* m_pNameButton;
	cUiObject* m_pNameUi;

	//����ī��(...)

	//���� ���� ����

	//Ŀ��...

	//Ȯ���˾�

public:
	virtual HRESULT Setup(void) override;
	virtual void Reset(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnClick(cUIButton* pSender) override;

	static cUiCustomizingScene* Create(void);
protected:
	cUiCustomizingScene(void);
	virtual ~cUiCustomizingScene(void);
};