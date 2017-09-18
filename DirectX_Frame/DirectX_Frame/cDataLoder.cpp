#include "stdafx.h"
#include "cDataLoder.h"


void cDataLoder::RegisterMesh(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_MESH, szFolder, szFilename, szKeyName));
}

void cDataLoder::RegisterAnimation(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{
	m_vecData.push_back(ST_DATA(cDataLoder::DATA_ANIMATION, szFolder, szFilename, szKeyName));
}

cDataLoder::cDataLoder()
{
}


cDataLoder::~cDataLoder()
{
}
