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


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "msimg32.lib")

// TODO: 매니저 헤더는 여기에서 참조합니다.
#include "cAutoReleasePool.h"
#include "cDeviceManager.h"
#include "cInputManager.h"

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
#define SAFE_DELETE(pointer) if(pointer) { delete (pointer); (pointer) = nullptr; }
#define SAFE_DELETE_ARRAY(pointer) if (pointer) {delete[] (pointer); (pointer) = nullptr;}
#define SAFE_SETUP(pointer) if (pointer) {(pointer)->Setup();}
#define SAFE_UPDATE(pointer) if (pointer) {(pointer)->Update();}
#define SAFE_RENDER(pointer) if (pointer) {(pointer)->Render();}

