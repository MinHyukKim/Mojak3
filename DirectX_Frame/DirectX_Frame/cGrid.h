#pragma once

class cPyramid;

class cGrid : public cObject
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<cPyramid*>		m_vecPyramid;

public:
	void Setup(int nNumLine = 30, float fInterval = 1.0f);
	void Render();

	static cGrid* Create(void);
protected:
	cGrid(void);
	virtual ~cGrid(void);
};

