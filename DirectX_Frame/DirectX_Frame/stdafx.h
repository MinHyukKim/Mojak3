// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//콘솔 디버깅
#define CONSOLE_DEBUG_TEST

#ifdef CONSOLE_DEBUG_TEST
#ifdef 멀티바이트 사용중이냐?
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif
#include <iostream>
#define DEBUG_TEXT(text) std::cout<< text << std::endl //콘솔 출력
#else // CONSOLE_DEBUG_TEST
#define DEBUG_TEXT(text) //출력안함
#endif // !CONSOLE_DEBUG_TEST

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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
// TODO: 매니저 헤더는 여기에서 참조합니다.
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

// 전역 함수
extern HWND g_hWnd;

//콜백 함수
typedef void(*CallbackFunctionParamer)(void*);
typedef void(*CallbackFunction)(void);

//사용할 이름공간
using namespace std;

//디파인문
#define SAFE_ADDREF(pointer) if(pointer) { (pointer)->AddRef(); }
#define SAFE_RELEASE(pointer) if(pointer) { (pointer)->Release(); (pointer) = nullptr; }
#define SAFE_RESET(pointer) if(pointer) { (pointer)->Reset(); (pointer) = nullptr; }
#define SAFE_DELETE(pointer) if(pointer) { delete (pointer); (pointer) = nullptr; }
#define SAFE_DELETE_ARRAY(pointer) if (pointer) {delete[] (pointer); (pointer) = nullptr;}
#define SAFE_SETUP(pointer) if (pointer) {(pointer)->Setup();}
#define SAFE_UPDATE(pointer) if (pointer) {(pointer)->Update();}
#define SAFE_RENDER(pointer) if (pointer) {(pointer)->Render();}

//정점 구조체
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

//광원 설정
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

//신디사이저 생성
#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }