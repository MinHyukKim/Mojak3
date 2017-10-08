// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
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
#include <bitset>
#include <thread>
#include <list>
#include "cCustomQueue.h"

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
#include "cSkinnedMeshManager.h"	//메시
#include "cTimer.h"	//타이머
#include "cFrustum.h"	//절두체 컬링
#include "cAllocateHierarchy.h"	//계층구조
#include "cAnimationManager.h"	//애니메이션
#include "cObjectManager.h"	//오브젝트
#include "cRay.h"	//마우스 피킹
#include "cMath.h"	//간단한 랜덤함수
#include "cMapObjectManager.h" //맵에 올라갈 오브젝트 관련 함수
#include "cMapManager.h"	//맵?
#include "cFontManager.h"

//콘솔 디버깅
#define CONSOLE_DEBUG_TEST

#ifdef CONSOLE_DEBUG_TEST
#ifdef CONSOLE_DEBUG_TEST
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include <iostream>
#include <fstream>
static int nHierachyCount = 0;
static std::ofstream BubugFile;
#define DEBUG_WRIT(text) { BubugFile << text; }
#define DEBUG_END() BubugFile.close()
#define DEBUG_START(text) {BubugFile.open(text), BubugFile.is_open();}
#define DEBUG_TEXT(text) {std::cout<< text << std::endl;} //콘솔 출력
#define DEBUG_TEXT_EX(text) {for(int DEBUG_i = 1; DEBUG_i < nHierachyCount; ++DEBUG_i){std::cout<<"│";} std::cout << "├" << text << std::endl;} //콘솔 출력
#define DEBUG_ADD_COUNT() ++nHierachyCount
#define DEBUG_SUB_COUNT() --nHierachyCount

#else // CONSOLE_DEBUG_TEST
#define DEBUG_WRIT(text) //출력안함
#define DEBUG_START()
#define DEBUG_TEXT_EX(text)
#define DEBUG_END()
#define DEBUG_TEXT(text) //출력안함
#define DEBUG_ADD_COUNT()
#define DEBUG_SUB_COUNT()
#endif // !CONSOLE_DEBUG_TEST
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

//인덱스 구조체
struct	ST_INDEX { WORD _0, _1, _2; };

//정점 구조체
struct ST_PC_VERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

	D3DXVECTOR3 position;
	D3DCOLOR color;

	ST_PC_VERTEX(D3DXVECTOR3 _position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255))
		: position(_position), color(_color) {
	}
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

//기본 프레임
struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
//	bool bUpdate;
//	bool bRender;


	ST_BONE(void) : D3DXFRAME({})/*, bUpdate(true), bRender(false)*/
	{
		D3DXMatrixIdentity(&TransformationMatrix);
		D3DXMatrixIdentity(&CombinedTransformationMatrix);
	}

	ST_BONE(ST_BONE* pOrigin) : ST_BONE(*pOrigin) {}
};

//기본 메시컨테이너
struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	//형상
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
//	LPD3DXMESH				pOrigMesh;

	LPD3DXMESH pWorkingMesh;
	//애니메이션
	D3DXMATRIXA16**			ppBoneMatrixPtrs;
	D3DXMATRIXA16*			pBoneOffsetMatrices;
	// 각 본의 계산된 월드매트릭스
//	D3DXMATRIX*				pCurrentBoneMatrices;
	//셰이더
	LPD3DXBUFFER			pBufBoneCombos;
	DWORD					dwNumPaletteEntries;
	DWORD					dwMaxNumFaceInfls;
	DWORD					dwNumAttrGroups;

	ST_BONE_MESH(void) : D3DXMESHCONTAINER({}), pWorkingMesh(nullptr), ppBoneMatrixPtrs(nullptr), pBoneOffsetMatrices(nullptr)
		, pBufBoneCombos(nullptr), dwNumPaletteEntries(0), dwMaxNumFaceInfls(0), dwNumAttrGroups(0)
	{
	}
	ST_BONE_MESH(ST_BONE_MESH* pBoneMesh) : ST_BONE_MESH(*pBoneMesh) {}
};

//데이터
struct ST_DATA
{
	DWORD dwType;
	std::string str1;
	std::string str2;
	std::string str3;
	D3DXMATRIXA16 mat1;
	D3DMATERIAL9 material;
	int nParam;

	ST_DATA(DWORD _dwType = 0, std::string _str1 = "", std::string _str2 = "", std::string _str3 = "", LPD3DXMATRIX _mat1 = nullptr, D3DMATERIAL9* _material = nullptr, int nParam = 0)
		: dwType(_dwType), str1(_str1), str2(_str2), str3(_str3), nParam(nParam)
	{
		if (_mat1) mat1 = *_mat1;
		if (_material) material = *_material;
	}
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

inline bool SetMatrial(OUT D3DMATERIAL9* stMtl, IN D3DXCOLOR& stColor = IN D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f), IN DWORD dwPower = 20.0f)
{
	ZeroMemory(stMtl, sizeof(D3DMATERIAL9));
	stMtl->Ambient = stColor;
	stMtl->Diffuse = stColor;
	stMtl->Specular = stColor;
//	stMtl->Emissive = dwColor;
	stMtl->Power = dwPower;
	return true;
}

// 문자열의 포인터(LPSTR*)에 문자열(LPSTR) 깊은복사한다.
inline bool CopyString(OUT LPSTR* ppTextCopy, IN LPCSTR pTextOrigin)
{
	if (pTextOrigin && ppTextCopy)
	{
		SAFE_DELETE_ARRAY(*ppTextCopy);
		int nLength = lstrlen(pTextOrigin) + 1;
		(*ppTextCopy) = new char[nLength];
		memcpy(*ppTextCopy, pTextOrigin, nLength * sizeof(char));
		return true;
	}
	return false;
}


//신디사이저 생성
#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }