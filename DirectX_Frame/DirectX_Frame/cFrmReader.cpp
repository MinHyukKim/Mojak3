#include "stdafx.h"
#include "cFrmReader.h"

cFrmReader::cFrmReader(void)
{
}

cFrmReader::~cFrmReader(void)
{
}

bool cFrmReader::Load(LPCSTR stream)
{
	CopyString(&m_name, stream);
//	for (UINT i = 0; i < length; i++)
//	{
//
//	}

	return false;
}

LPD3DXMATRIX cFrmReader::FlipMatrix(OUT LPD3DXMATRIX pMatrix, IN float* pMatrix_f16)
{
	//float[16] -> LPD3DXMATRIX 로 형변환
	if (pMatrix_f16)
	{
		memcpy(pMatrix->m, pMatrix_f16, 4 * sizeof(float));
		return pMatrix;
	}
	return nullptr;
}
