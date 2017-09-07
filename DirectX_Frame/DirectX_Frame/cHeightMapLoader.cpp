#include "stdafx.h"
#include "cHeightMapLoader.h"

cHeightMapLoader::cHeightMapLoader()
	: m_pMesh(NULL)
	, m_nTile(0)
{
}

cHeightMapLoader::~cHeightMapLoader()
{
	SAFE_RELEASE(m_pMesh);
}


void cHeightMapLoader::Load(char * szFolder, char * szFile,
	char * szTexture, DWORD dwBytesPerPixel)
{
	std::string sPath = std::string(szFolder) + std::string(szFile);
	m_sTexture = std::string(szFolder) + std::string(szTexture);

	//파일 읽기
	FILE* fp = 0;
	fopen_s(&fp, sPath.c_str(), "rb");
	//파일 커서를 이동하고 그 커서 이동한 만큼의 숫자를 센다
	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytesPerPixel;
	int nRow = (int)sqrt(nNumVertex + FLT_EPSILON);
	//정사각형이 아닐 경우 어센션
	if (nNumVertex != nRow * nRow)
	{
		fclose(fp);
		assert(false && "정사각형태의 RAW파일만 사용 가능합니다.");
	}
	fseek(fp, 0, SEEK_SET);

	//가로세로같음
	int nCol = nRow;
	m_nTile = nRow - 1;
	vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	m_vecVertex.resize(nNumVertex);

	for (int z = 0; z < nRow; ++z)
	{
		for (int x = 0; x < nCol; ++x)
		{
			unsigned char c = fgetc(fp);
			int i = z * nRow + x;
			vecVertex[i].p = D3DXVECTOR3(x, c / 10.0f, z);
			vecVertex[i].n = D3DXVECTOR3(0, 1, 0);
			vecVertex[i].t = D3DXVECTOR2(x / (float)m_nTile, z / (float)m_nTile);

			m_vecVertex[i] = vecVertex[i].p;

			if (dwBytesPerPixel > 1)
			{
				fseek(fp, dwBytesPerPixel - 1, SEEK_CUR);
			}
		}
	}
	fclose(fp);
	//  ---U---
	//  |\ |\ |
	//  | \| \|
	//  L--I--R
	//  |\ |\ |
	//  | \| \|
	//  ---D---
	for (int z = 1; z < nRow; ++z)
	{
		for (int x = 1; x < nCol - 1; ++x)
		{
			int l = (z + 0) * nCol + x - 1;
			int r = (z + 0) * nCol + x + 1;
			int u = (z + 1) * nCol + x + 0;
			int d = (z - 1) * nCol + x + 0;

			D3DXVECTOR3 lr = vecVertex[r].p - vecVertex[l].p;
			D3DXVECTOR3 du = vecVertex[u].p - vecVertex[d].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);

			vecVertex[z * nCol + x].n = n;
		}
	}
	//  1--3
	//  |\ |
	//  | \|
	//  0--2 
	vector<DWORD> vecIndex;
	vecIndex.reserve(m_nTile * m_nTile * 2 * 3);
	for (int z = 0; z < m_nTile; ++z)
	{
		for (int x = 0; x < m_nTile; ++x)
		{
			int _0 = (z + 0) * nCol + x + 0;
			int _1 = (z + 1) * nCol + x + 0;
			int _2 = (z + 0) * nCol + x + 1;
			int _3 = (z + 1) * nCol + x + 1;
			vecIndex.push_back(_0); vecIndex.push_back(_1); vecIndex.push_back(_2);
			vecIndex.push_back(_3); vecIndex.push_back(_2); vecIndex.push_back(_1);
		}
	}
	//마저 하기

}

bool cHeightMapLoader::GetHeight(IN float x, OUT float & y, IN float z)
{
	return false;
}

void cHeightMapLoader::Render()
{
}

