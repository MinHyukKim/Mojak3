#pragma once

struct ST_FRAME
{
	char magic[4];
	short version, bonesCount;
};

//struct ST_BONE
//{
//	float globalToLocal[16], localToGlobal[16], link[16];
//	char dummy;
//	char name[31];
//	char boneID, parentID;
//	short empty;
//	D3DXQUATERNION quat1, quat2;
//};

class cFrmReader
{
private:
	ST_FRAME m_pRoot;

public:
	char* m_name;
	std::vector<ST_BONE*> m_bones;

	bool Load(LPCSTR stream);
	
	static LPD3DXMATRIX FlipMatrix(OUT LPD3DXMATRIX pMatrix, IN float* pMatrix_f16);

	cFrmReader(void);
	virtual ~cFrmReader(void);
};

