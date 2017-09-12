// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//�ܼ� �����
#define CONSOLE_DEBUG_TEST

#ifdef CONSOLE_DEBUG_TEST
#ifdef ��Ƽ����Ʈ ������̳�?
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif
#include <iostream>
#define DEBUG_TEXT(text) std::cout<< text << std::endl //�ܼ� ���
#else // CONSOLE_DEBUG_TEST
#define DEBUG_TEXT(text) //��¾���
#endif // !CONSOLE_DEBUG_TEST

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>
#include <bitset>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "msimg32.lib")
// TODO: �Ŵ��� ����� ���⿡�� �����մϴ�.
#include "cAutoReleasePool.h"
#include "cDeviceManager.h"
#include "cInputManager.h"
#include "cTextureManager.h"
#include "cSceneManager.h"
#include "cUIManager.h"
#include "cSoundManager.h"
#include "cUiFontManager.h"
#include "cSkinnedMeshManager.h"
#include "cTimer.h"

// ���� �Լ�
extern HWND g_hWnd;

//�ݹ� �Լ�
typedef void(*CallbackFunctionParamer)(void*);
typedef void(*CallbackFunction)(void);

//����� �̸�����
using namespace std;

//�����ι�
#define SAFE_ADDREF(pointer) if(pointer) { (pointer)->AddRef(); }
#define SAFE_RELEASE(pointer) if(pointer) { (pointer)->Release(); (pointer) = nullptr; }
#define SAFE_RESET(pointer) if(pointer) { (pointer)->Reset(); (pointer) = nullptr; }
#define SAFE_DELETE(pointer) if(pointer) { delete (pointer); (pointer) = nullptr; }
#define SAFE_DELETE_ARRAY(pointer) if (pointer) {delete[] (pointer); (pointer) = nullptr;}
#define SAFE_SETUP(pointer) if (pointer) {(pointer)->Setup();}
#define SAFE_UPDATE(pointer) if (pointer) {(pointer)->Update();}
#define SAFE_RENDER(pointer) if (pointer) {(pointer)->Render();}

//���� ����ü
struct ST_PC_VERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

	D3DXVECTOR3 position;
	D3DCOLOR color;

	ST_PC_VERTEX(D3DXVECTOR3 _position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255))
		: position(_position), color(_color) {}
};

struct ST_PN_VERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };

	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;

	ST_PN_VERTEX(D3DXVECTOR3 _position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 _normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		: position(_position), normal(_normal) {}
};

struct ST_PNT_VERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };

	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	ST_PNT_VERTEX(
		D3DXVECTOR3 _p = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 _n = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR2 _t = D3DXVECTOR2(0, 0)
	)
		: p(_p), n(_n), t(_t)
	{
	}
};

//ST_SIZE
struct ST_SIZE
{
	float			fWidth;
	float			fHeight;

	ST_SIZE() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZE(float _w, float _h) : fWidth(_w), fHeight(_h) {}
};

//���� ����
inline void SetDirectional(int index, D3DXVECTOR3& direction, D3DXCOLOR& lightColor)
{
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = light.Diffuse = light.Specular = lightColor;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &direction);
	g_pD3DDevice->SetLight(index, &light);
}

inline bool SetMatrial(OUT D3DMATERIAL9* stMtl, IN D3DXCOLOR& stColor = IN D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f), IN DWORD dwPower = 1000.0f)
{
	ZeroMemory(stMtl, sizeof(D3DMATERIAL9));
	stMtl->Ambient = stColor;
	stMtl->Diffuse = stColor;
	stMtl->Specular = stColor;
//	stMtl->Emissive = dwColor;
	stMtl->Power = dwPower;
	return true;
}

//�ŵ������ ����
#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }